/*
 * Physical page allocator for the x86_64 port.
 *
 * Limine hands us the firmware memory map; every USABLE /
 * BOOTLOADER_RECLAIMABLE / ACPI_RECLAIMABLE region above 1 MiB (and
 * away from the framebuffer/kernel) is carved into 4 KiB pages
 * tracked by a simple freelist.  alloc_phys()/free_phys() are the
 * whole interface: user pages, page tables and file caches all come
 * from here.
 *
 * The freelist is intrusive: each free 4K page stores the pointer to
 * the next one in its first 8 bytes (the page is, after all, free).
 * Limine maps all physical memory at HHDM_BASE + paddr, so freelist
 * access goes through that window - low physical addresses are NOT
 * identity-mapped under the Limine protocol.
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

/* set by limine_start before pmm_init: physical -> virtual window */
extern uint64_t hhdm_offset;

#define HHDM_BASE	hhdm_offset

static inline void *
phys2virt(uint64_t p)
{
	return (void *)(p + HHDM_BASE);
}

static inline uint64_t
virt2phys(void *v)
{
	return (uint64_t)v - HHDM_BASE;
}

#define PAGE_SIZE	4096ul
#define PAGE_SHIFT	12

#define MEMTYPE_USABLE			0
#define MEMTYPE_RESERVED		1
#define MEMTYPE_ACPI_RECLAIMABLE	2
#define MEMTYPE_ACPI_NVS		3
#define MEMTYPE_BAD_MEMORY		4
#define MEMTYPE_BOOTLOADER_RECLAIMABLE	5
#define MEMTYPE_KERNEL_AND_MODULES	6
#define MEMTYPE_FRAMEBUFFER		7

struct limine_memmap_entry {
	uint64_t base;
	uint64_t length;
	uint64_t type;
};

struct limine_memmap_response {
	uint64_t revision;
	uint64_t entry_count;
	struct limine_memmap_entry **entries;
};

extern void *limine_memmap_response;

/* limine.c console + number formatting */
void console_puts(const char *s);
void console_write(const char *s, unsigned long n);
void putdec(uint64_t v);
void puthex(uint64_t v);

static uint64_t free_head;		/* physical address of first free
					 * page, 0 = none */
static uint64_t free_count;
static uint64_t total_count;

/*
 * The kernel is loaded at physical 1 MiB by Limine; its first 2 MiB
 * are off-limits to the freelist (RX/R/RW mappings, boot structs).
 * Cheap to give up: the smallest machine this targets has far more.
 */
#define LOW_WATER	0x200000

static void
region_push(uint64_t base, uint64_t len)
{
	uint64_t start = (base + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	uint64_t end = (base + len) & ~(PAGE_SIZE - 1);
	uint64_t i;

	/*
	 * Push high-to-low so alloc_phys() pops ascending within the
	 * region: alloc_run() (kernel stacks) relies on consecutive
	 * pops being physically contiguous.  Regions themselves are
	 * walked in ascending memmap order, so the highest region is
	 * linked last and consumed first -- allocations still come
	 * from the high end, away from the kernel.
	 */
	for (i = end; i >= start + PAGE_SIZE; i -= PAGE_SIZE) {
		*(uint64_t *)phys2virt(i - PAGE_SIZE) = free_head;
		free_head = i - PAGE_SIZE;
		free_count++;
	}
}

uint64_t alloc_run(uint64_t npages, uint64_t *got);

#define STACK_RUN_PAGES		16
#define STACK_POOL_BYTES	(16ul * 1024 * 1024)

static uint64_t stack_pool_base, stack_pool_next, stack_pool_end;
static uint64_t stack_freelist;

static void pmm_stack_reserve(struct limine_memmap_response *mm);

void
pmm_init(void)
{
	struct limine_memmap_response *mm =
	    (struct limine_memmap_response *)limine_memmap_response;
	uint64_t i;

	free_head = 0;
	free_count = 0;
	total_count = 0;

	if (mm == 0)
		return;

	/*
	 * Walk the map twice: count first (for the report), then link.
	 * Linking must go low-to-high per region so that allocated
	 * pages tend to come from the high end; any order is correct,
	 * this one just keeps kernel-adjacent pages out of the way.
	 */
	for (i = 0; i < mm->entry_count; i++) {
		struct limine_memmap_entry *e = mm->entries[i];
		uint64_t base = e->base > LOW_WATER ? e->base : LOW_WATER;
		uint64_t len = e->length - (base - e->base);

		if (e->base + e->length <= LOW_WATER)
			continue;
		if (e->type != MEMTYPE_USABLE)
			continue;
		if (base + len > 0x100000000ul)
			continue;
		total_count += len / PAGE_SIZE;
	}
	pmm_stack_reserve(mm);

	for (i = 0; i < mm->entry_count; i++) {
		struct limine_memmap_entry *e = mm->entries[i];
		uint64_t base = e->base > LOW_WATER ? e->base : LOW_WATER;
		uint64_t len = e->length - (base - e->base);

		if (e->base + e->length <= LOW_WATER)
			continue;
		/*
		 * Only MEMTYPE_USABLE: bootloader-reclaimable still
		 * holds the boot structures we are iterating right now
		 * (the memory map response lives there), and ACPI
		 * reclaimable is wanted by S5.  Everything above 4 GiB
		 * waits for proper >4G support.
		 */
		if (e->type != MEMTYPE_USABLE)
			continue;
		if (base + len > 0x100000000ul)
			continue;
		if (stack_pool_end && base < stack_pool_end &&
		    base + len > stack_pool_base) {
			/* the pool lives at this region's low end */
			uint64_t nb = stack_pool_end > base ?
			    stack_pool_end : base;

			if (base + len > nb)
				region_push(nb, base + len - nb);
			continue;
		}
		region_push(base, len);
	}
}

uint64_t
pmm_total(void)
{
	return total_count;
}

uint64_t
pmm_free(void)
{
	return free_count;
}

uint64_t
alloc_phys(void)
{
	uint64_t p;

	if (free_head == 0)
		return 0;			/* out of memory */
	p = free_head;
	free_head = *(uint64_t *)phys2virt(p);
	free_count--;
	return p;
}

/*
 * Kernel stacks need KSTACK_PAGES physically contiguous pages, but the
 * general free list fragments as soon as processes exit (freed pages
 * are pushed onto the head in arbitrary order), so alloc_run() starts
 * failing after the first fork/exec round-trip.  Reserve one large
 * contiguous chunk at boot -- while the list is still pristine -- and
 * carve fixed-size stack slots out of it.
 */

/*
 * Reserve the pool while the memmap is still in hand: the lowest
 * STACK_POOL_BYTES of the largest usable region are simply not linked
 * into the free list, so they can never be handed out as single pages
 * and always stay physically contiguous.
 */
static void
pmm_stack_reserve(struct limine_memmap_response *mm)
{
	uint64_t i, best_len = 0, best_base = 0;

	stack_pool_base = stack_pool_next = stack_pool_end = 0;
	for (i = 0; i < mm->entry_count; i++) {
		struct limine_memmap_entry *e = mm->entries[i];
		uint64_t base = e->base > LOW_WATER ? e->base : LOW_WATER;
		uint64_t len = e->length - (base - e->base);

		if (e->base + e->length <= LOW_WATER)
			continue;
		if (e->type != MEMTYPE_USABLE)
			continue;
		if (base + len > 0x100000000ul)
			continue;
		if (len > best_len) {
			best_len = len;
			best_base = base;
		}
	}
	if (best_len < 2 * STACK_POOL_BYTES)
		return;
	stack_pool_base = (best_base + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	stack_pool_next = stack_pool_base;
	stack_pool_end = stack_pool_base + STACK_POOL_BYTES;
	if (stack_pool_end > best_base + best_len)
		stack_pool_end = (best_base + best_len) & ~(PAGE_SIZE - 1);
}

uint64_t
pmm_stack_alloc(void)
{
	uint64_t base;

	if (stack_freelist) {
		base = stack_freelist;
		stack_freelist = *(uint64_t *)phys2virt(base);
		return base;
	}
	if (stack_pool_next == 0 ||
	    stack_pool_next + STACK_RUN_PAGES * PAGE_SIZE > stack_pool_end)
		return 0;
	base = stack_pool_next;
	stack_pool_next += STACK_RUN_PAGES * PAGE_SIZE;
	return base;
}

void
pmm_stack_free(uint64_t base)
{
	if (base == 0)
		return;
	*(uint64_t *)phys2virt(base) = stack_freelist;
	stack_freelist = base;
}

void
free_phys(uint64_t p)
{
	if (p == 0 || (p & (PAGE_SIZE - 1)))
		return;				/* refuse garbage */
	*(uint64_t *)phys2virt(p) = free_head;
	free_head = p;
	free_count++;
}

/*
 * Contiguous run allocator for DMA-style consumers (btrfs metadata
 * buffers, user segments): keeps taking pages until it has a run.
 * Returns 0 on failure (caller frees what it got back via run).
 */
uint64_t
alloc_run(uint64_t npages, uint64_t *got)
{
	uint64_t first, last, n;

	*got = 0;
	if (npages == 0 || free_count < npages)
		return 0;
	first = alloc_phys();
	if (first == 0)
		return 0;
	*got = 1;
	last = first;
	while (*got < npages) {
		n = alloc_phys();
		if (n == 0 || n != last + PAGE_SIZE) {
			if (n)
				free_phys(n);
			/* unwind: caller may retry with a smaller run */
			return first;
		}
		last = n;
		(*got)++;
	}
	return first;
}
