/*
 * Minimal Limine boot entry for the x86_64 port.
 *
 * The V7 kernel's main() cannot run yet: it expects the PDP-11 MMU
 * plumbing (mch.s) that this port has not rebuilt.  Until the IDT,
 * clock and page tables exist this entry proves the boot path with a
 * systemd-style status log on the framebuffer console (console.c
 * mirrors to COM1 for headless/qemu debugging) and halts.
 *
 * Boot output deliberately stays in English: the console's CJK font
 * support is for kernel/userland text, not the boot screens.
 */

/*
 * freestanding: no <stdint.h> in the V7 include tree
 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;
typedef unsigned long  uintptr_t;

/* Limine framebuffer response layout (see limine/limine.h). */
struct limine_fb {
	uint64_t address;
	uint64_t width;
	uint64_t height;
	uint64_t pitch;
	uint16_t bpp;
	uint8_t  memory_model;
	uint8_t  red_mask_size;
	uint8_t  red_mask_shift;
	uint8_t  green_mask_size;
	uint8_t  green_mask_shift;
	uint8_t  blue_mask_size;
	uint8_t  blue_mask_shift;
	uint8_t  _pad[7];
	uint64_t edid_size;
	uint64_t *edid;
};

struct limine_fb_response {
	uint64_t revision;
	uint64_t framebuffer_count;
	struct limine_fb **framebuffers;
};

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

/* response slots inside limine.S's requests */
extern void *limine_fb_response;
extern void *limine_memmap_response;
extern void *limine_hhdm_response;
extern uint64_t limine_base_revision[3];

/* filled in limine_start, consumed by pmm.c et al: every physical
 * address maps at hhdm_offset + paddr */
uint64_t hhdm_offset;

/* console.c */
void console_init(struct limine_fb *fb);
void console_puts(const char *s);
void console_write(const char *s, unsigned long n);
void console_serial_write(const char *s, unsigned long n);
void console_setfg(unsigned char r, unsigned char g, unsigned char b);
int  console_fb_ok(void);

/* intr.c / pit.c / keyboard.c */
void intr_init(void);
void sti(void);
void cli(void);
void pit_init(int hz);
void kbd_init(void);
int  kbd_getchar(void);
void pmm_init(void);
uint64_t pmm_total(void);
uint64_t pmm_free(void);
extern volatile uint64_t jiffies;

#define MEMTYPE_USABLE			0
#define MEMTYPE_RESERVED		1
#define MEMTYPE_ACPI_RECLAIMABLE	2
#define MEMTYPE_ACPI_NVS		3
#define MEMTYPE_BAD_MEMORY		4
#define MEMTYPE_BOOTLOADER_RECLAIMABLE	5
#define MEMTYPE_KERNEL_AND_MODULES	6
#define MEMTYPE_FRAMEBUFFER		7

static const char *
memtype_name(uint64_t t)
{
	switch (t) {
	case MEMTYPE_USABLE:			return "usable";
	case MEMTYPE_RESERVED:			return "reserved";
	case MEMTYPE_ACPI_RECLAIMABLE:		return "acpi reclaim";
	case MEMTYPE_ACPI_NVS:			return "acpi nvs";
	case MEMTYPE_BAD_MEMORY:		return "bad";
	case MEMTYPE_BOOTLOADER_RECLAIMABLE:	return "bootloader";
	case MEMTYPE_KERNEL_AND_MODULES:	return "kernel/modules";
	case MEMTYPE_FRAMEBUFFER:		return "framebuffer";
	default:				return "?";
	}
}

/* serial-only shortcut (ANSI escapes must not reach the fb renderer) */
#define SW(s)	console_serial_write(s, sizeof(s) - 1)

void
putdec(uint64_t v)
{
	char buf[20];
	int i = 0;

	if (v == 0) {
		console_puts("0");
		return;
	}
	while (v) {
		buf[i++] = '0' + v % 10;
		v /= 10;
	}
	while (i--)
		console_write(&buf[i], 1);
}

void
puthex(uint64_t v)
{
	static const char digits[] = "0123456789abcdef";
	int i;

	for (i = 60; i >= 0; i -= 4)
		console_write(&digits[(v >> i) & 0xf], 1);
}

/* ------------------------------------------------ systemd-style status log */

static void
ok_prefix(void)
{
	SW("\x1b[0;32m");
	console_setfg(0, 220, 0);
	console_puts("[  OK  ] ");
	console_setfg(255, 255, 255);
}

static void
fail_prefix(void)
{
	SW("\x1b[0;31m");
	console_setfg(255, 80, 80);
	console_puts("[FAILED] ");
	console_setfg(255, 255, 255);
}

static void
line_end(void)
{
	SW("\x1b[0m");
	console_puts("\r\n");
}

static void
ok(const char *msg)
{
	ok_prefix();
	console_puts(msg);
	line_end();
}

/* dim/diagnostic line, not a status item */
static void
detail_prefix(void)
{
	SW("\x1b[0;90m");
	console_setfg(150, 150, 150);
}

static void
detail_end(void)
{
	SW("\x1b[0m");
	console_setfg(255, 255, 255);
}

/*
 * CPU brand string via CPUID 0x80000002..0x80000004; empty on old CPUs,
 * distinguishes real hardware from qemu ("QEMU Virtual CPU version ...")
 * at a glance on first boot.
 */
static void
cpu_brand(char out[49])
{
	uint32_t regs[12];
	uint32_t i, j;
	uint32_t maxext;

	__asm__ volatile("cpuid"
	    : "=a"(maxext)
	    : "a"(0x80000000u)
	    : "ebx", "ecx", "edx");

	if (maxext < 0x80000004u) {
		out[0] = 0;
		return;
	}
	for (i = 0; i < 3; i++)
		__asm__ volatile("cpuid"
		    : "=a"(regs[i * 4]), "=b"(regs[i * 4 + 1]),
		      "=c"(regs[i * 4 + 2]), "=d"(regs[i * 4 + 3])
		    : "a"(0x80000002u + i)
		    :);

	for (i = 0; i < 12; i++)
		for (j = 0; j < 4; j++)
			out[i * 4 + j] = (char)((regs[i] >> (j * 8)) & 0xff);
	out[48] = 0;
}

void
limine_start(void)
{
	struct limine_fb_response *fb =
	    (struct limine_fb_response *)limine_fb_response;
	struct limine_fb *f = 0;
	struct limine_memmap_response *mm =
	    (struct limine_memmap_response *)limine_memmap_response;
	char brand[49];
	uint64_t usable = 0;
	uint64_t i, nusable = 0;

	/* HHDM window: rev 1 responses carry the offset; fall back to
	 * the rev 0 fixed base if the loader granted revision 0 */
	{
		struct {
			uint64_t revision;
			uint64_t offset;
		} *hh = limine_hhdm_response;

		if (hh != 0)
			hhdm_offset = hh->offset;
		else if (limine_base_revision[1] == 0)
			hhdm_offset = 0xffffffff80000000ul;
		else
			hhdm_offset = 0xffff800000000000ul;
	}

	console_init(fb != 0 && fb->framebuffer_count > 0
	    ? fb->framebuffers[0] : 0);

	SW("\x1b[1m");
	console_puts("\r\nVodyaOS 0.1.0 (x86_64)\r\n");
	console_puts("Unix Seventh Edition lineage, booted via Limine\r\n");
	SW("\x1b[0m");
	console_puts("\r\n");

	if (fb != 0 && fb->framebuffer_count > 0)
		f = fb->framebuffers[0];
	if (f != 0) {
		if (console_fb_ok()) {
			ok_prefix();
			console_puts("Initialized framebuffer text console (");
			putdec(f->width);
			console_puts("x");
			putdec(f->height);
			console_puts("x");
			putdec(f->bpp);
			console_puts(")");
			line_end();
		} else {
			fail_prefix();
			console_puts("Framebuffer unusable, console is "
			    "serial-only");
			line_end();
		}
	}

	cpu_brand(brand);
	if (brand[0]) {
		ok_prefix();
		console_puts("Detected CPU: ");
		console_puts(brand);
		line_end();
	}

	if (mm != 0 && mm->entry_count > 0) {
		for (i = 0; i < mm->entry_count; i++) {
			struct limine_memmap_entry *e = mm->entries[i];

			if (e->type == MEMTYPE_USABLE) {
				usable += e->length;
				nusable++;
			}
		}
		ok_prefix();
		console_puts("Enumerated memory map: ");
		putdec(mm->entry_count);
		console_puts(" entries, ");
		putdec(usable / 1024 / 1024);
		console_puts(" MiB usable");
		line_end();

		detail_prefix();
		for (i = 0; i < mm->entry_count; i++) {
			struct limine_memmap_entry *e = mm->entries[i];

			console_puts("  ");
			puthex(e->base);
			console_puts("-");
			puthex(e->base + e->length);
			console_puts(" ");
			console_puts(memtype_name(e->type));
			console_puts("\r\n");
		}
		detail_end();
	}

	ok("Reached target Early Boot.");

	/* ---- interrupt + device infrastructure (HANDOFF.md 8.5) ---- */
	intr_init();
	ok("Initialized IDT and exception handlers.");

	pit_init(100);				/* 100 Hz heartbeat */
	ok("Initialized PIT timer (100 Hz).");

	sti();					/* interrupts live from here */

	kbd_init();
	ok("Initialized PS/2 keyboard driver.");

	pmm_init();
	ok_prefix();
	console_puts("Initialized physical memory allocator: ");
	putdec(pmm_free());
	console_puts(" free / ");
	putdec(pmm_total());
	console_puts(" 4KiB pages");
	line_end();
	detail_prefix();
	console_puts("  base rev granted: ");
	puthex(limine_base_revision[1]);
	console_puts(", hhdm offset: ");
	puthex(hhdm_offset);
	console_puts("\r\n");
	detail_end();

	/* ---- interactive input demo: type, see it echoed ---- */
	{
		char line[160];
		int n = 0;

		console_puts("\r\nKeyboard input is live - type a line, "
		    "Enter to confirm, 'halt' quits.\r\n");
		for (;;) {
			int c;

			console_puts("vodya> ");
			n = 0;
			for (;;) {
				c = kbd_getchar();
				if (c < 0)
					continue;
				if (c == '\n')
					break;
				if (c == '\b') {
					if (n > 0)
						n--;
					continue;
				}
				if (n < (int)sizeof(line) - 1)
					line[n++] = (char)c;
			}
			line[n] = 0;
			if (line[0] == 0)
				continue;
			if (line[0] == 'h' && line[1] == 'a' &&
			    line[2] == 'l' && line[3] == 't' && line[4] == 0)
				break;
			console_puts("you typed: ");
			console_puts(line);
			console_puts("\r\n");
		}
	}

	detail_prefix();
	console_puts("V7 main() pending: userland exec, btrfs rootfs "
	    "(HANDOFF.md 8.5)\r\n");
	detail_end();

	/* V7 main() comes back here once paging/IDT/clock exist (HANDOFF 8.5).
	 * main(); */
	console_puts("halted.\r\n");
	for (;;)
		__asm__ volatile("cli; hlt");
}
