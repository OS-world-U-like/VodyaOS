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

	for (i = start; i + PAGE_SIZE <= end; i += PAGE_SIZE) {
		*(uint64_t *)phys2virt(i) = free_head;
		free_head = i;
		free_count++;
	}
}

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
