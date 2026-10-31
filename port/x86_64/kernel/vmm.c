/*
 * Virtual memory for userland: fresh PML4s with the kernel half
 * cloned from the boot page tables, 4 KiB page mapping, lookup,
 * teardown and full-space copy (fork).
 *
 * Flags are raw PTE bits; the usual combos are:
 *   PTE_KERNEL_RW  P|W|NX      PTE_USER_RX   P|U
 *   PTE_USER_RW    P|W|U|NX    PTE_USER_RO   P|U|NX
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

#define PTE_P		0x001
#define PTE_W		0x002
#define PTE_U		0x004
#define PTE_NX		0x8000000000000000ull

/*
 * A PTE entry -> its physical address.  Attribute bits must be
 * stripped with this mask (not ~0xfff): a page carrying NX has bit 63
 * set, and using it as an address produces a non-canonical value.
 */
#define PTE_ADDR(e)	((uint64_t)(e) & 0x000ffffffffff000ull)

#define PTE_KERNEL_RW	(PTE_P | PTE_W | PTE_NX)
#define PTE_USER_RX	(PTE_P | PTE_U)
#define PTE_USER_RO	(PTE_P | PTE_U | PTE_NX)
#define PTE_USER_RW	(PTE_P | PTE_W | PTE_U | PTE_NX)

#define PAGE_SIZE	4096ul
#define ENTRIES		512

/* pmm.c */
uint64_t alloc_phys(void);
void free_phys(uint64_t p);
/* set by limine_start: physical -> virtual window */
extern uint64_t hhdm_offset;
#define phys2virt(p) ((void *)((uint64_t)(p) + hhdm_offset))

uint64_t
vmm_cr3(void)
{
	uint64_t v;

	__asm__ volatile("movq %%cr3, %0" : "=r"(v));
	return v;
}

void
vmm_switch(uint64_t cr3)
{
	__asm__ volatile("movq %0, %%cr3" : : "r"(cr3) : "memory");
}

static uint64_t *
pt_of(uint64_t pt_paddr, uint64_t idx)
{
	return (uint64_t *)phys2virt(PTE_ADDR(pt_paddr)) + idx;
}

/* fresh PML4 with the kernel half cloned from the boot tables */
uint64_t
vmm_new(void)
{
	uint64_t pml4 = alloc_phys();
	uint64_t *src, *dst;
	int i;

	if (pml4 == 0)
		return 0;
	dst = (uint64_t *)phys2virt(pml4);
	src = (uint64_t *)phys2virt(PTE_ADDR(vmm_cr3()));
	for (i = 0; i < ENTRIES; i++)
		dst[i] = (i >= 256) ? src[i] : 0;
	return pml4;
}

static uint64_t *
walk(uint64_t cr3, uint64_t va, int create)
{
	uint64_t *table = (uint64_t *)phys2virt(PTE_ADDR(cr3));
	int level;

	for (level = 3; level >= 1; level--) {
		uint64_t idx = (va >> (12 + 9 * level)) & 0x1ff;
		uint64_t e = table[idx];

		if (!(e & PTE_P)) {
			uint64_t np;

			if (!create)
				return 0;
			np = alloc_phys();
			if (np == 0)
				return 0;
			/* zero the new table */
			{
				uint64_t *z = (uint64_t *)phys2virt(np);
				int k;

				for (k = 0; k < ENTRIES; k++)
					z[k] = 0;
			}
			/* intermediate levels need U too: x86 grants a
			 * user access only if EVERY level has U set */
			table[idx] = np | PTE_P | PTE_W | PTE_U;
			e = table[idx];
		}
		table = (uint64_t *)phys2virt(PTE_ADDR(e));
	}
	/* the last level's index is the actual page entry -- without
	 * this every vmm_map()/vmm_phys() in a 2 MiB region landed on
	 * PT[0] (one physical page served a whole range) */
	return &table[(va >> 12) & 0x1ff];
}

int
vmm_map(uint64_t cr3, uint64_t va, uint64_t pa, uint64_t flags)
{
	uint64_t *pte = walk(cr3, va, 1);

	if (pte == 0)
		return -1;
	*pte = PTE_ADDR(pa) | flags;
	__asm__ volatile("invlpg (%0)" : : "r"(va) : "memory");
	return 0;
}

uint64_t
vmm_phys(uint64_t cr3, uint64_t va)
{
	uint64_t *pte = walk(cr3, va, 0);

	if (pte == 0 || !(*pte & PTE_P))
		return 0;
	/* strip attribute bits (NX et al), keep the physical address */
	return *pte & 0x000ffffffffff000ull;
}

/* raw entries along the walk: [0] PML4E [1] PDPTE [2] PDE [3] PTE */
void
vmm_walk_raw(uint64_t cr3, uint64_t va, uint64_t *out)
{
	uint64_t *table = (uint64_t *)phys2virt(PTE_ADDR(cr3));
	int level;

	out[0] = out[1] = out[2] = out[3] = 0;
	for (level = 3; level >= 1; level--) {
		uint64_t idx = (va >> (12 + 9 * level)) & 0x1ff;
		uint64_t e = table[idx];

		out[3 - level] = e;
		if (!(e & PTE_P))
			return;
		table = (uint64_t *)phys2virt(PTE_ADDR(e));
	}
	out[3] = table[(va >> 12) & 0x1ff];
}

/* free user pages and their tables below the given PML4 (user half
 * only: entries 0..255) */
void
vmm_destroy_user(uint64_t cr3)
{
	uint64_t *pml4 = (uint64_t *)phys2virt(PTE_ADDR(cr3));
	int i, j, k, l;

	for (i = 0; i < 256; i++) {
		uint64_t e4 = pml4[i];
		uint64_t *pdpt, *pd, *pt;

		if (!(e4 & PTE_P))
			continue;
		pdpt = (uint64_t *)phys2virt(PTE_ADDR(e4));
		for (j = 0; j < ENTRIES; j++) {
			uint64_t e3 = pdpt[j];

			if (!(e3 & PTE_P) || (e3 & 0x080))
				goto free3;
			pd = (uint64_t *)phys2virt(PTE_ADDR(e3));
			for (k = 0; k < ENTRIES; k++) {
				uint64_t e2 = pd[k];

				if (!(e2 & PTE_P) || (e2 & 0x080))
					goto free2;
				pt = (uint64_t *)phys2virt(PTE_ADDR(e2));
				for (l = 0; l < ENTRIES; l++) {
					uint64_t e1 = pt[l];

					if (e1 & PTE_P)
						free_phys(PTE_ADDR(e1));
				}
				free_phys(PTE_ADDR(e2));
free2:				;
			}
			free_phys(PTE_ADDR(e3));
free3:			;
		}
		free_phys(PTE_ADDR(e4));
		pml4[i] = 0;
	}
}

/* the attribute bits of a mapped page (0 if unmapped) */
uint64_t
vmm_flags(uint64_t cr3, uint64_t va)
{
	uint64_t *pte = walk(cr3, va, 0);

	if (pte == 0 || !(*pte & PTE_P))
		return 0;
	/* present/writable/user/accessed/dirty/global + NX */
	return *pte & 0x8000000000000fffull;
}

/* copy every mapped user page in [lo, hi) from src to dst */
void
vmm_copy_range(uint64_t src_cr3, uint64_t dst_cr3, uint64_t lo, uint64_t hi)
{
	uint64_t va;

	for (va = lo & ~0xfffull; va < hi; va += PAGE_SIZE) {
		uint64_t sp = vmm_phys(src_cr3, va);

		if (sp == 0)
			continue;
		{
			uint64_t dp = alloc_phys();

			if (dp == 0)
				return;
			{
				char *s = (char *)phys2virt(sp);
				char *d = (char *)phys2virt(dp);
				uint64_t k;

				for (k = 0; k < PAGE_SIZE; k++)
					d[k] = s[k];
			}
			/* keep the source permissions: fork's child must
			 * inherit executable text as executable (a blanket
			 * PTE_USER_RW marks bash's code NX and the child
			 * dies on its first instruction fetch) */
			vmm_map(dst_cr3, va, dp,
			    vmm_flags(src_cr3, va) | PTE_P);
		}
	}
}
