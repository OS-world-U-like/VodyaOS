/*
 * Early kernel text console: Limine framebuffer + COM1 serial mirror.
 *
 * Real machines do not expose their display through a serial line, so the
 * kernel draws text on the boot framebuffer itself.  Text arrives as
 * UTF-8: ASCII renders with the 8x16 VGA font (font.h), other codepoints
 * are looked up in the GB2312 16x16 bitmap table (cjkfont.h) and drawn
 * double-width, which gives the console native Chinese output.  The same
 * bytes are mirrored to COM1 so qemu -serial and headless debugging keep
 * working.
 */

#include "font.h"
#include "cjkfont.h"

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;
typedef long           intptr_t;

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

static struct {
	uint32_t *base;
	uint64_t pitch;			/* bytes per scanline */
	int w, h, bpp;
	int rs, gs, bs;			/* channel shifts */
	int rm, gm, bm;			/* channel widths */
	int cols, rows;			/* in 8x16 cells */
	int cx, cy;			/* cursor cell */
} fb;

static int fb_ok;

/* ---------------------------------------------------------------- serial */

#ifdef CONSOLE_NO_SERIAL
/*
 * Host test build (no I/O ports in userspace); the kernel build never
 * defines this.
 */
static void
serial_init(void)
{
}

static void
serial_putc(char c)
{
	(void)c;
}
#else
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

/*
 * Serial-only output: for ANSI attribute codes and other bytes that must
 * not reach the framebuffer renderer.
 */
void
console_serial_write(const char *s, unsigned long n)
{
	while (n--)
		serial_putc(*s++);
}
#endif	/* CONSOLE_NO_SERIAL */

/* ------------------------------------------------------------ freestanding */

static void *
fb_memmove(void *dst, const void *src, uint64_t n)
{
	uint8_t *d = dst;
	const uint8_t *s = src;

	if (d < s) {
		while (n--)
			*d++ = *s++;
	} else {
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return dst;
}

/* ---------------------------------------------------------------- drawing */

static uint32_t
pixel_rgb(int r, int g, int b)
{
	return (((uint32_t)r & ((1 << fb.rm) - 1)) << fb.rs) |
	       (((uint32_t)g & ((1 << fb.gm) - 1)) << fb.gs) |
	       (((uint32_t)b & ((1 << fb.bm) - 1)) << fb.bs);
}

static void
fill_rect(int x, int y, int w, int h, uint32_t px)
{
	int i, j;

	for (j = y; j < y + h && j < fb.h; j++) {
		uint32_t *row = (uint32_t *)((uint8_t *)fb.base + j * fb.pitch);
		for (i = x; i < x + w && i < fb.w; i++)
			row[i] = px;
	}
}

static uint32_t fg_color = 0x00ffffff;	/* current glyph color (XRGB) */

void
console_setfg(unsigned char r, unsigned char g, unsigned char b)
{
	if (fb_ok)
		fg_color = pixel_rgb(r, g, b);
}

static void
glyph8(const unsigned char *g, int cx, int cy)
{
	uint32_t fg = fg_color;
	int row, bit;

	for (row = 0; row < FONT_HEIGHT; row++) {
		uint32_t *line = (uint32_t *)
		    ((uint8_t *)fb.base + (cy * FONT_HEIGHT + row) * fb.pitch);
		for (bit = 0; bit < 8; bit++)
			line[cx * 8 + bit] =
			    (g[row] & (0x80 >> bit)) ? fg : 0;
	}
}

static void
glyph16(const unsigned char *g, int cx, int cy)
{
	uint32_t fg = fg_color;
	int row, bit;

	for (row = 0; row < 16; row++) {
		uint32_t *line = (uint32_t *)
		    ((uint8_t *)fb.base + (cy * 16 + row) * fb.pitch);
		for (bit = 0; bit < 8; bit++) {
			line[cx * 8 + bit] =
			    (g[row * 2] & (0x80 >> bit)) ? fg : 0;
			line[cx * 8 + 8 + bit] =
			    (g[row * 2 + 1] & (0x80 >> bit)) ? fg : 0;
		}
	}
}

static int
cjk_find(uint16_t cp)
{
	int lo = 0, hi = (int)(sizeof(cjk_cp) / sizeof(cjk_cp[0])) - 1;

	while (lo <= hi) {
		int mid = (lo + hi) / 2;

		if (cjk_cp[mid] == cp)
			return mid;
		if (cjk_cp[mid] < cp)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return -1;
}

static void
fb_scroll(void)
{
	int h = fb.rows * FONT_HEIGHT;

	/* move everything but the first text row up one row */
	fb_memmove(fb.base,
	    (uint8_t *)fb.base + FONT_HEIGHT * fb.pitch,
	    (h - FONT_HEIGHT) * fb.pitch);
	fill_rect(0, h - FONT_HEIGHT, fb.w, FONT_HEIGHT, 0);
}

static void
fb_newline(void)
{
	fb.cx = 0;
	if (++fb.cy >= fb.rows) {
		fb.cy = fb.rows - 1;
		fb_scroll();
	}
}

/* draw one Unicode codepoint on the framebuffer */
static void
fb_putcp(uint32_t cp)
{
	int i;

	if (cp == '\n') {
		fb_newline();
		return;
	}
	if (cp == '\r') {
		fb.cx = 0;
		return;
	}
	if (cp == '\t') {
		for (i = 0; i < 4; i++)
			fb_putcp(' ');
		return;
	}

	if (cp < 0x80 && cp >= FONT_FIRST) {
		if (fb.cx + 1 > fb.cols)
			fb_newline();
		glyph8(font8x16[cp - FONT_FIRST], fb.cx, fb.cy);
		fb.cx++;
		return;
	}

	/* CJK / fullwidth: 16x16 double-width cell */
	{
		int g = (cp <= 0xffff) ? cjk_find((uint16_t)cp) : -1;

		if (fb.cx + 2 > fb.cols)
			fb_newline();
		if (g >= 0)
			glyph16(cjk_bits[g], fb.cx, fb.cy);
		else
			glyph16(cjk_bits[cjk_find(0xff1f)], fb.cx, fb.cy);
		fb.cx += 2;
	}
}

/* ------------------------------------------------------------------ utf-8 */

/*
 * Decode UTF-8 as bytes stream in, codepoints out (to fb) and raw bytes
 * out (to serial).  Minimal state machine: 1..3 byte sequences; overlong
 * or truncated input falls back to '?'.
 */
void
console_putc(char c)
{
	static uint32_t acc;
	static int need;

	serial_putc(c);			/* serial always sees raw bytes */

	if (!fb_ok)
		return;

	uint8_t b = (uint8_t)c;

	if (need == 0) {
		if (b < 0x80) {
			fb_putcp(b);
			return;
		}
		if ((b & 0xe0) == 0xc0) {
			acc = b & 0x1f;
			need = 1;
		} else if ((b & 0xf0) == 0xe0) {
			acc = b & 0x0f;
			need = 2;
		} else if ((b & 0xf8) == 0xf0) {
			acc = 0x1000000;	/* >0xffff marker: eat, render '?' */
			need = 3;
		} else {
			fb_putcp('?');
		}
		return;
	}
	if ((b & 0xc0) != 0x80) {
		need = 0;
		fb_putcp('?');
		if (b < 0x80)
			fb_putcp(b);	/* resync on ASCII */
		return;
	}
	acc = (acc << 6) | (b & 0x3f);
	if (--need == 0) {
		fb_putcp(acc);
		acc = 0;
	}
}

void
console_write(const char *s, unsigned long n)
{
	while (n--)
		console_putc(*s++);
}

void
console_puts(const char *s)
{
	while (*s)
		console_putc(*s++);
}

/* ------------------------------------------------------------------- init */

void
console_init(struct limine_fb *f)
{
	serial_init();

	if (f == 0 || f->bpp != 32 || f->memory_model != 1 /* RGB */) {
		fb_ok = 0;
		return;
	}
	fb.base = (uint32_t *)(unsigned long)f->address;
	fb.pitch = f->pitch;
	fb.w = (int)f->width;
	fb.h = (int)f->height;
	fb.bpp = f->bpp;
	fb.rm = f->red_mask_size;
	fb.rs = f->red_mask_shift;
	fb.gm = f->green_mask_size;
	fb.gs = f->green_mask_shift;
	fb.bm = f->blue_mask_size;
	fb.bs = f->blue_mask_shift;
	fb.cols = fb.w / 8;
	fb.rows = fb.h / FONT_HEIGHT;
	fb.cx = fb.cy = 0;
	fb_ok = 1;

	fill_rect(0, 0, fb.w, fb.h, 0);
}

int
console_fb_ok(void)
{
	return fb_ok;
}
