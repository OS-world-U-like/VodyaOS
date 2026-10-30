/*
 * PS/2 (8042) keyboard driver, IRQ1, scancode set 1.
 *
 * Make/break pairs are translated to ASCII (shift + capslock aware)
 * and pushed into a small ring buffer that readers drain with
 * kbd_getchar().  Printable keys, backspace and enter are echoed on
 * the kernel console from within the interrupt handler, so the user
 * sees what they type before any userland exists.
 *
 * Control keys arrive as control characters (\b, \n, \t, 0x01..0x1a);
 * the console/line-discipline layers interpret them.
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

#define KBD_DATA	0x60
#define KBD_STAT	0x64
#define STAT_OBF	0x01		/* output buffer full */

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

/* console.c */
void console_putc(char c);

/* intr.c */
void irq_register(int irq, void (*fn)(uint64_t *frame));

/* --------------------------------------------------------- scancodes */

static const char sc_key[128] = {
	0,   0,   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u',
	'i', 'o', 'p', '[', ']', '\n', 0,   'a', 's', 'd', 'f', 'g',
	'h', 'j', 'k', 'l', ';', '\'', '`', 0,   '\\', 'z', 'x', 'c',
	'v', 'b', 'n', 'm', ',', '.', '/', 0,   '*', 0,   ' ', 0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   '7', '8', '9', '-', '4', '5', '6', '+', '1', '2',
	'3', '0', '.', 0,   0,   0,   0,   0
};

static const char sc_key_shift[128] = {
	0,   0,   '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
	'_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
	'I', 'O', 'P', '{', '}', '\n', 0,   'A', 'S', 'D', 'F', 'G',
	'H', 'J', 'K', 'L', ':', '"', '~', 0,   '|', 'Z', 'X', 'C',
	'V', 'B', 'N', 'M', '<', '>', '?', 0,   '*', 0,   ' ', 0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   '7', '8', '9', '-', '4', '5', '6', '+', '1', '2',
	'3', '0', '.', 0,   0,   0,   0,   0
};

/* ------------------------------------------------------------ buffers */

#define KBD_BUFLEN	256

static volatile unsigned kb_head, kb_tail;
static volatile char kb_buf[KBD_BUFLEN];

static int shift_l, shift_r, caps, ctrl;

static void
kb_push(char c)
{
	unsigned next = (kb_head + 1) % KBD_BUFLEN;

	if (next == kb_tail)
		return;				/* buffer full: drop */
	kb_buf[kb_head] = c;
	kb_head = next;
}

int
kbd_getchar(void)
{
	int c = -1;

	if (kb_tail != kb_head) {
		c = (unsigned char)kb_buf[kb_tail];
		kb_tail = (kb_tail + 1) % KBD_BUFLEN;
	}
	return c;
}

static void
kb_echo(char c)
{
	if (c >= 0x20 && c < 0x7f)
		console_putc(c);
	else if (c == '\n')
		console_putc('\n');
	else if (c == '\b') {
		console_putc('\b');
		console_putc(' ');
		console_putc('\b');
	} else if (c == '\t')
		console_putc('\t');
	/* other control chars: not echoed */
}

static void
kbd_intr(uint64_t *frame)
{
	for (;;) {
		uint8_t sc;
		int shift;
		char c;

		if (!(inb(KBD_STAT) & STAT_OBF))
			return;
		sc = inb(KBD_DATA);

		if (sc == 0xe0) {		/* extended: arrows etc: skip
						 * the follow-up byte */
			while (!(inb(KBD_STAT) & STAT_OBF))
				;
			inb(KBD_DATA);
			continue;
		}
		if (sc == 0xe1) {		/* pause key: 6-byte sequence */
			int n;

			for (n = 0; n < 5; n++) {
				while (!(inb(KBD_STAT) & STAT_OBF))
					;
				inb(KBD_DATA);
			}
			continue;
		}

		if (sc & 0x80) {		/* break (release) */
			sc &= 0x7f;
			if (sc == 0x2a) shift_l = 0;
			else if (sc == 0x36) shift_r = 0;
			else if (sc == 0x1d) ctrl = 0;
			continue;
		}

		switch (sc) {			/* make */
		case 0x2a: shift_l = 1; continue;
		case 0x36: shift_r = 1; continue;
		case 0x1d: ctrl = 1; continue;
		case 0x3a:			/* capslock toggle */
			caps = !caps;
			continue;
		}

		shift = shift_l || shift_r;
		c = shift ? sc_key_shift[sc] : sc_key[sc];
		if (c == 0)
			continue;
		if (!shift && caps) {
			if (c >= 'a' && c <= 'z')
				c = c - 'a' + 'A';
			else if (c >= 'A' && c <= 'Z')
				c = c - 'A' + 'a';
		}
		if (ctrl && c >= 'a' && c <= 'z')
			c = c - 'a' + 1;
		kb_push(c);
		kb_echo(c);
	}
}

void
kbd_init(void)
{
	unsigned i;

	/* drain stale output, then (re)enable the first PS/2 port
	 * (controller command 0xae) */
	while (inb(KBD_STAT) & STAT_OBF)
		inb(KBD_DATA);
	outb(KBD_STAT, 0xae);

	/* LEDs off: 0xed command byte + parameter, ack each time */
	for (i = 0; i < 2; i++) {
		unsigned n;

		outb(KBD_DATA, i == 0 ? 0xed : 0x00);
		for (n = 0; n < 100000; n++)
			if (inb(KBD_STAT) & STAT_OBF)
				break;
		(void)inb(KBD_DATA);
	}

	kb_head = kb_tail = 0;
	irq_register(1, kbd_intr);
}
