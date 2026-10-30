/*
 * Interrupt plumbing for the x86_64 port: IDT, 8259A PIC, exception
 * reporting and a small per-IRQ dispatch table.
 *
 * Vectors 0..31 are CPU exceptions (any hit is a kernel panic with a
 * register dump), 32..47 are the remapped PIC IRQ lines, everything
 * above is spurious and masked out.  Handlers are registered with
 * irq_register() and called with the trapframe pointer; each handler
 * must issue its own EOI via pic_eoi().
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

/* ------------------------------------------------------------- registers */

#define R15	0x00
#define R14	0x08
#define R13	0x10
#define R12	0x18
#define R11	0x20
#define R10	0x28
#define R9	0x30
#define R8	0x38
#define RBP	0x40
#define RSI	0x48
#define RDI	0x50
#define RDX	0x58
#define RCX	0x60
#define RBX	0x68
#define RAX	0x70
#define TF_VECTOR 0x78
#define TF_ERR	0x80
#define TF_RIP	0x88
#define TF_CS	0x90
#define TF_RFLAGS 0x98
#define TF_RSP	0xa0
#define TF_SS	0xa8

/* ------------------------------------------------------------------ I/O */

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

static inline void
io_wait(void)
{
	outb(0x80, 0);
}

/* ------------------------------------------------------------ IDT gates */

struct idt_entry {
	uint16_t off_lo;
	uint16_t sel;
	uint8_t	 ist;
	uint8_t	 flags;			/* present|DPL|type: 0x8e = int32 ring0 */
	uint16_t off_mid;
	uint32_t off_hi;
	uint32_t zero;
} __attribute__((packed));

struct idt_ptr {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr idtp;

extern char intr_stub0[], intr_stub1[], intr_stub2[], intr_stub3[],
    intr_stub4[], intr_stub5[], intr_stub6[], intr_stub7[], intr_stub8[],
    intr_stub9[], intr_stub10[], intr_stub11[], intr_stub12[],
    intr_stub13[], intr_stub14[], intr_stub15[], intr_stub16[],
    intr_stub17[], intr_stub18[], intr_stub19[], intr_stub20[],
    intr_stub21[], intr_stub22[], intr_stub23[], intr_stub24[],
    intr_stub25[], intr_stub26[], intr_stub27[], intr_stub28[],
    intr_stub29[], intr_stub30[], intr_stub31[], intr_stub32[],
    intr_stub33[], intr_stub34[], intr_stub35[], intr_stub36[],
    intr_stub37[], intr_stub38[], intr_stub39[], intr_stub40[],
    intr_stub41[], intr_stub42[], intr_stub43[], intr_stub44[],
    intr_stub45[], intr_stub46[], intr_stub47[], intr_stub48[],
    intr_stub49[], intr_stub50[], intr_stub51[], intr_stub52[],
    intr_stub53[], intr_stub54[], intr_stub55[], intr_stub56[],
    intr_stub57[], intr_stub58[], intr_stub59[], intr_stub60[],
    intr_stub61[], intr_stub62[], intr_stub63[], intr_stub64[],
    intr_stub65[], intr_stub66[], intr_stub67[], intr_stub68[],
    intr_stub69[], intr_stub70[], intr_stub71[], intr_stub72[],
    intr_stub73[], intr_stub74[], intr_stub75[], intr_stub76[],
    intr_stub77[], intr_stub78[], intr_stub79[], intr_stub80[],
    intr_stub81[], intr_stub82[], intr_stub83[], intr_stub84[],
    intr_stub85[], intr_stub86[], intr_stub87[], intr_stub88[],
    intr_stub89[], intr_stub90[], intr_stub91[], intr_stub92[],
    intr_stub93[], intr_stub94[], intr_stub95[], intr_stub96[],
    intr_stub97[], intr_stub98[], intr_stub99[], intr_stub100[],
    intr_stub101[], intr_stub102[], intr_stub103[], intr_stub104[],
    intr_stub105[], intr_stub106[], intr_stub107[], intr_stub108[],
    intr_stub109[], intr_stub110[], intr_stub111[], intr_stub112[],
    intr_stub113[], intr_stub114[], intr_stub115[], intr_stub116[],
    intr_stub117[], intr_stub118[], intr_stub119[], intr_stub120[],
    intr_stub121[], intr_stub122[], intr_stub123[], intr_stub124[],
    intr_stub125[], intr_stub126[], intr_stub127[], intr_stub128[],
    intr_stub129[], intr_stub130[], intr_stub131[], intr_stub132[],
    intr_stub133[], intr_stub134[], intr_stub135[], intr_stub136[],
    intr_stub137[], intr_stub138[], intr_stub139[], intr_stub140[],
    intr_stub141[], intr_stub142[], intr_stub143[], intr_stub144[],
    intr_stub145[], intr_stub146[], intr_stub147[], intr_stub148[],
    intr_stub149[], intr_stub150[], intr_stub151[], intr_stub152[],
    intr_stub153[], intr_stub154[], intr_stub155[], intr_stub156[],
    intr_stub157[], intr_stub158[], intr_stub159[], intr_stub160[],
    intr_stub161[], intr_stub162[], intr_stub163[], intr_stub164[],
    intr_stub165[], intr_stub166[], intr_stub167[], intr_stub168[],
    intr_stub169[], intr_stub170[], intr_stub171[], intr_stub172[],
    intr_stub173[], intr_stub174[], intr_stub175[], intr_stub176[],
    intr_stub177[], intr_stub178[], intr_stub179[], intr_stub180[],
    intr_stub181[], intr_stub182[], intr_stub183[], intr_stub184[],
    intr_stub185[], intr_stub186[], intr_stub187[], intr_stub188[],
    intr_stub189[], intr_stub190[], intr_stub191[], intr_stub192[],
    intr_stub193[], intr_stub194[], intr_stub195[], intr_stub196[],
    intr_stub197[], intr_stub198[], intr_stub199[], intr_stub200[],
    intr_stub201[], intr_stub202[], intr_stub203[], intr_stub204[],
    intr_stub205[], intr_stub206[], intr_stub207[], intr_stub208[],
    intr_stub209[], intr_stub210[], intr_stub211[], intr_stub212[],
    intr_stub213[], intr_stub214[], intr_stub215[], intr_stub216[],
    intr_stub217[], intr_stub218[], intr_stub219[], intr_stub220[],
    intr_stub221[], intr_stub222[], intr_stub223[], intr_stub224[],
    intr_stub225[], intr_stub226[], intr_stub227[], intr_stub228[],
    intr_stub229[], intr_stub230[], intr_stub231[], intr_stub232[],
    intr_stub233[], intr_stub234[], intr_stub235[], intr_stub236[],
    intr_stub237[], intr_stub238[], intr_stub239[], intr_stub240[],
    intr_stub241[], intr_stub242[], intr_stub243[], intr_stub244[],
    intr_stub245[], intr_stub246[], intr_stub247[], intr_stub248[],
    intr_stub249[], intr_stub250[], intr_stub251[], intr_stub252[],
    intr_stub253[], intr_stub254[], intr_stub255[];

static char *intr_stubtab[256] = {
	intr_stub0, intr_stub1, intr_stub2, intr_stub3,
	intr_stub4, intr_stub5, intr_stub6, intr_stub7,
	intr_stub8, intr_stub9, intr_stub10, intr_stub11,
	intr_stub12, intr_stub13, intr_stub14, intr_stub15,
	intr_stub16, intr_stub17, intr_stub18, intr_stub19,
	intr_stub20, intr_stub21, intr_stub22, intr_stub23,
	intr_stub24, intr_stub25, intr_stub26, intr_stub27,
	intr_stub28, intr_stub29, intr_stub30, intr_stub31,
	intr_stub32, intr_stub33, intr_stub34, intr_stub35,
	intr_stub36, intr_stub37, intr_stub38, intr_stub39,
	intr_stub40, intr_stub41, intr_stub42, intr_stub43,
	intr_stub44, intr_stub45, intr_stub46, intr_stub47,
	intr_stub48, intr_stub49, intr_stub50, intr_stub51,
	intr_stub52, intr_stub53, intr_stub54, intr_stub55,
	intr_stub56, intr_stub57, intr_stub58, intr_stub59,
	intr_stub60, intr_stub61, intr_stub62, intr_stub63,
	intr_stub64, intr_stub65, intr_stub66, intr_stub67,
	intr_stub68, intr_stub69, intr_stub70, intr_stub71,
	intr_stub72, intr_stub73, intr_stub74, intr_stub75,
	intr_stub76, intr_stub77, intr_stub78, intr_stub79,
	intr_stub80, intr_stub81, intr_stub82, intr_stub83,
	intr_stub84, intr_stub85, intr_stub86, intr_stub87,
	intr_stub88, intr_stub89, intr_stub90, intr_stub91,
	intr_stub92, intr_stub93, intr_stub94, intr_stub95,
	intr_stub96, intr_stub97, intr_stub98, intr_stub99,
	intr_stub100, intr_stub101, intr_stub102, intr_stub103,
	intr_stub104, intr_stub105, intr_stub106, intr_stub107,
	intr_stub108, intr_stub109, intr_stub110, intr_stub111,
	intr_stub112, intr_stub113, intr_stub114, intr_stub115,
	intr_stub116, intr_stub117, intr_stub118, intr_stub119,
	intr_stub120, intr_stub121, intr_stub122, intr_stub123,
	intr_stub124, intr_stub125, intr_stub126, intr_stub127,
	intr_stub128, intr_stub129, intr_stub130, intr_stub131,
	intr_stub132, intr_stub133, intr_stub134, intr_stub135,
	intr_stub136, intr_stub137, intr_stub138, intr_stub139,
	intr_stub140, intr_stub141, intr_stub142, intr_stub143,
	intr_stub144, intr_stub145, intr_stub146, intr_stub147,
	intr_stub148, intr_stub149, intr_stub150, intr_stub151,
	intr_stub152, intr_stub153, intr_stub154, intr_stub155,
	intr_stub156, intr_stub157, intr_stub158, intr_stub159,
	intr_stub160, intr_stub161, intr_stub162, intr_stub163,
	intr_stub164, intr_stub165, intr_stub166, intr_stub167,
	intr_stub168, intr_stub169, intr_stub170, intr_stub171,
	intr_stub172, intr_stub173, intr_stub174, intr_stub175,
	intr_stub176, intr_stub177, intr_stub178, intr_stub179,
	intr_stub180, intr_stub181, intr_stub182, intr_stub183,
	intr_stub184, intr_stub185, intr_stub186, intr_stub187,
	intr_stub188, intr_stub189, intr_stub190, intr_stub191,
	intr_stub192, intr_stub193, intr_stub194, intr_stub195,
	intr_stub196, intr_stub197, intr_stub198, intr_stub199,
	intr_stub200, intr_stub201, intr_stub202, intr_stub203,
	intr_stub204, intr_stub205, intr_stub206, intr_stub207,
	intr_stub208, intr_stub209, intr_stub210, intr_stub211,
	intr_stub212, intr_stub213, intr_stub214, intr_stub215,
	intr_stub216, intr_stub217, intr_stub218, intr_stub219,
	intr_stub220, intr_stub221, intr_stub222, intr_stub223,
	intr_stub224, intr_stub225, intr_stub226, intr_stub227,
	intr_stub228, intr_stub229, intr_stub230, intr_stub231,
	intr_stub232, intr_stub233, intr_stub234, intr_stub235,
	intr_stub236, intr_stub237, intr_stub238, intr_stub239,
	intr_stub240, intr_stub241, intr_stub242, intr_stub243,
	intr_stub244, intr_stub245, intr_stub246, intr_stub247,
	intr_stub248, intr_stub249, intr_stub250, intr_stub251,
	intr_stub252, intr_stub253, intr_stub254, intr_stub255,
};

/* from limine.c: console output */
void console_puts(const char *s);
void console_write(const char *s, unsigned long n);
static void puthex(uint64_t v);
static void putdec(uint64_t v);

static void
idt_set(int n, char *handler)
{
	uint64_t off = (uint64_t)handler;

	idt[n].off_lo = off & 0xffff;
	idt[n].sel = 0x28;	/* Limine's 64-bit kernel code selector */
	idt[n].ist = 0;
	idt[n].flags = 0x8e;
	idt[n].off_mid = (off >> 16) & 0xffff;
	idt[n].off_hi = (uint32_t)(off >> 32);
	idt[n].zero = 0;
}

/* ----------------------------------------------------------- exceptions */

static const char *exc_name[32] = {
	"#DE divide", "#DB debug", "NMI", "#BP breakpoint", "#OF overflow",
	"#BR bound", "#UD invalid opcode", "#NM no FPU", "#DF double fault",
	"Coproc seg", "#TS invalid TSS", "#NP segment", "#SS stack",
	"#GP general protection", "#PF page fault", "reserved",
	"#MF x87", "#AC alignment", "#MC machine check", "#XM SIMD",
	"#VE virtualization", "#CP control protection", "reserved",
	"reserved", "reserved", "reserved", "reserved", "reserved",
	"reserved", "reserved", "#SX security", "reserved"
};

static void
panic_dump(uint64_t *f)
{
	__asm__ volatile("cli");

	console_puts("\r\nKERNEL PANIC: ");
	if (f[TF_VECTOR / 8] < 32) {
		console_puts(exc_name[f[TF_VECTOR / 8]]);
		console_puts(" (vector ");
		putdec(f[TF_VECTOR / 8]);
		console_puts(")");
	} else {
		console_puts("unexpected vector ");
		putdec(f[TF_VECTOR / 8]);
	}
	console_puts("\r\n");
	console_puts("  error code: ");
	puthex(f[TF_ERR / 8]);
	console_puts("  rip: ");
	puthex(f[TF_RIP / 8]);
	console_puts("\r\n  cs: ");
	puthex(f[TF_CS / 8]);
	console_puts("  rflags: ");
	puthex(f[TF_RFLAGS / 8]);
	console_puts("  rsp: ");
	puthex(f[TF_RSP / 8]);
	console_puts("\r\n");
	if (f[TF_VECTOR / 8] == 14) {		/* #PF: faulting address */
		uint64_t cr2;

		__asm__ volatile("movq %%cr2, %0" : "=r"(cr2));
		console_puts("  cr2 (fault addr): ");
		puthex(cr2);
		console_puts("\r\n");
	}
	console_puts("System halted.\r\n");
	for (;;)
		__asm__ volatile("cli; hlt");
}

/* ------------------------------------------------------------ PIC 8259A */

#define PIC1_CMD	0x20
#define PIC1_DATA	0x21
#define PIC2_CMD	0xa0
#define PIC2_DATA	0xa1
#define PIC_EOI_ACK	0x20

/* IRQ lines left unmasked: timer + keyboard. */
static uint16_t irq_mask = 0xfffb;	/* all set except bit 1 (IRQ1) */

static void
pic_remask(void)
{
	outb(PIC1_DATA, irq_mask & 0xff);
	outb(PIC2_DATA, (irq_mask >> 8) & 0xff);
}

static void
pic_init(void)
{
	outb(PIC1_CMD, 0x11);		/* ICW1: init + ICW4 */
	io_wait();
	outb(PIC2_CMD, 0x11);
	io_wait();
	outb(PIC1_DATA, 0x20);		/* ICW2: vectors 0x20.. */
	io_wait();
	outb(PIC2_DATA, 0x28);		/* ICW2: vectors 0x28.. */
	io_wait();
	outb(PIC1_DATA, 0x04);		/* ICW3: slave on IRQ2 */
	io_wait();
	outb(PIC2_DATA, 0x02);
	io_wait();
	outb(PIC1_DATA, 0x01);		/* ICW4: 8086 mode */
	io_wait();
	outb(PIC2_DATA, 0x01);
	io_wait();
	outb(PIC1_DATA, 0xff);		/* mask everything first */
	outb(PIC2_DATA, 0xff);
	pic_remask();			/* then apply irq_mask */
}

static void
pic_eoi(int irq)
{
	if (irq >= 8)
		outb(PIC2_CMD, PIC_EOI_ACK);
	outb(PIC1_CMD, PIC_EOI_ACK);
}

/* ------------------------------------------------------- IRQ dispatch */

typedef void (*irq_fn)(uint64_t *frame);

static irq_fn irq_handlers[16];

void
irq_register(int irq, irq_fn fn)
{
	irq_handlers[irq] = fn;
	irq_mask &= ~(1u << irq);
	pic_remask();
}

void
intr_dispatch(uint64_t *f)
{
	unsigned vec = (unsigned)f[TF_VECTOR / 8];

	if (vec < 32) {
		panic_dump(f);
		return;				/* not reached */
	}
	if (vec < 48) {
		int irq = vec - 32;
		irq_fn fn = irq_handlers[irq];

		if (fn)
			fn(f);
		pic_eoi(irq);
		return;
	}
	pic_eoi(7);				/* spurious: EOI and go on */
}

/* ------------------------------------------------------------- public */

void
intr_init(void)
{
	int i;

	for (i = 0; i < 256; i++)
		idt_set(i, intr_stubtab[i]);
	idtp.limit = sizeof(idt) - 1;
	idtp.base = (uint64_t)idt;
	__asm__ volatile("lidt %0" : : "m"(idtp));
	pic_init();
}

void
sti(void)
{
	__asm__ volatile("sti");
}

void
cli(void)
{
	__asm__ volatile("cli");
}

/* ------------------------------------------------------ number output */

static void
puthex(uint64_t v)
{
	static const char digits[] = "0123456789abcdef";
	int i;

	for (i = 60; i >= 0; i -= 4)
		console_write(&digits[(v >> i) & 0xf], 1);
}

static void
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
