/*
 * Minimal Limine boot entry for the x86_64 port.
 *
 * The V7 kernel's main() cannot run yet: it expects the PDP-11 MMU
 * plumbing (mch.s) that this port has not rebuilt.  Until the IDT,
 * clock and page tables exist this entry proves the boot path by
 * announcing itself on the COM1 serial line and halting.
 */

/*
 * freestanding: no <stdint.h> in the V7 include tree
 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint64_t;
typedef unsigned long  uintptr_t;

#define COM1		0x3f8

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

/* response slot inside limine.S's framebuffer request */
extern void *limine_fb_response;

static inline void
outb(uint16_t port, uint8_t val)
{
	__asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t
inb(uint16_t port)
{
	uint8_t v;

	__asm__ volatile("inb %1, %0" : "=a"(v) : "Nd"(port));
	return v;
}

static void
serial_init(void)
{
	outb(COM1 + 1, 0x00);	/* no interrupts */
	outb(COM1 + 3, 0x80);	/* DLAB on */
	outb(COM1 + 0, 0x01);	/* divisor 1 -> 115200 */
	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x03);	/* 8N1 */
	outb(COM1 + 2, 0xc7);	/* FIFO on, clear */
	outb(COM1 + 4, 0x0b);	/* DTR + RTS + OUT2 */
}

static void
serial_putc(char c)
{
	while ((inb(COM1 + 5) & 0x20) == 0)
		;
	outb(COM1 + 0, (uint8_t)c);
}

static void
puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}

static void
puthex(uint64_t v)
{
	static const char digits[] = "0123456789abcdef";
	int i;

	for (i = 60; i >= 0; i -= 4)
		serial_putc(digits[(v >> i) & 0xf]);
}

static void
putdec(uint64_t v)
{
	char buf[20];
	int i = 0;

	if (v == 0) {
		serial_putc('0');
		return;
	}
	while (v) {
		buf[i++] = '0' + v % 10;
		v /= 10;
	}
	while (i--)
		serial_putc(buf[i]);
}

void
limine_start(void)
{
	struct limine_fb_response *fb =
	    (struct limine_fb_response *)limine_fb_response;

	serial_init();

	puts("\r\nVodyaOS x86_64 kernel: booted via Limine\r\n");
	puts("framebuffer: ");
	if (fb != 0 && fb->framebuffer_count > 0) {
		struct limine_fb *f = fb->framebuffers[0];

		putdec(f->width);
		serial_putc('x');
		putdec(f->height);
		serial_putc('x');
		putdec(f->bpp);
		puts(" @ ");
		puthex((uint64_t)(uintptr_t)f->address);
	} else {
		puts("none");
	}
	puts("\r\n");

	/* V7 main() comes back here once paging/IDT/clock exist (HANDOFF 8.5).
	 * main(); */
	for (;;)
		__asm__ volatile("hlt");
}
