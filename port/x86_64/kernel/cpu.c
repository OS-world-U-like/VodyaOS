/*
 * CPU bring-up for userland: our own GDT (the syscall/sysret fast
 * path needs a known selector layout), a TSS for ring3->ring0 stack
 * switching on interrupts, and the SYSCALL MSRs (EFER.SCE, STAR,
 * LSTAR, SFMASK, kernel GS base).
 *
 * Selector layout (matches STAR below):
 *   0x08 kernel code   0x10 kernel data
 *   0x20 user data     0x28 user code        (SYSRET: CS=0x2b, SS=0x23)
 *   0x30 TSS
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

void console_puts(const char *s);

/* sys.S */
extern char syscall_entry[];
/* proc.c */
void wrmsr(uint32_t msr, uint64_t val);

/* ------------------------------------------------------------- GDT/TSS */

static uint64_t gdt[] = {
	0x0000000000000000ull,			/* 0x00 null */
	0x00af9a000000ffffull,			/* 0x08 kernel code 64 */
	0x00cf92000000ffffull,			/* 0x10 kernel data */
	0x0000000000000000ull,			/* 0x18 (STAR user base) */
	0x00cff2000000ffffull,			/* 0x20 user data */
	0x00affa000000ffffull,			/* 0x28 user code 64 */
	0, 0,					/* 0x30 TSS (two slots) */
};
/*
 * 64-bit TSS, laid out exactly as the CPU reads it: RSP0 lives at
 * offset 4 (the leading "reserved" is 32 bits, not a padding u64).
 * Without __packed the compiler aligns rsp0 to 8 and the CPU then
 * reads the low 32 bits of our rsp0 as the *whole* value -- a
 * physical address that is canonical but unmapped in the user CR3,
 * so the very first interrupt from ring 3 dies with #SS -> #DF.
 */
struct tss {
	uint32_t rsv0;				/* 0 */
	uint64_t rsp0;				/* 4  ring0 stack on int-from-user */
	uint64_t rsp1;				/* 12 */
	uint64_t rsp2;				/* 20 */
	uint64_t rsv1;				/* 28 */
	uint64_t ist[7];			/* 36 */
	uint32_t rsv2;				/* 92 */
	uint32_t rsv3;				/* 96 */
	uint16_t rsv4;				/* 100 */
	uint16_t iopb;				/* 102 */
} __attribute__((packed));

static struct tss tss;

static struct {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed)) gdtr;

/*
 * Install our GDT/TSS.  Exported and called early (before the IDT
 * is built): the IDT gates point at kernel CS 0x08, which is only a
 * valid 64-bit code segment once THIS GDT is loaded -- Limine's
 * 0x08 is a 16-bit code segment, and its 0x28 (the old kernel CS)
 * becomes user code here.  Interrupt delivery validates the gate's
 * target selector, so the GDT must be ours before any interrupt can
 * be delivered through the IDT.
 */
void
cpu_gdt_init(void)
{
	uint64_t tss_base = (uint64_t)&tss;

	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint64_t)gdt;

	tss.rsp0 = 0;				/* proc.c sets it */
	tss.iopb = sizeof(struct tss);

	/* 64-bit TSS descriptor: limit (20 bits), base (32 bits across
	 * both halves), type 0x9 available + present in byte 5. */
	{
		uint64_t base = tss_base;
		uint64_t limit = sizeof(struct tss) - 1;

		gdt[6] = (limit & 0xffffull)
		    | ((base & 0xffffffull) << 16)
		    | (0x89ull << 40)		/* P | 64-bit TSS available */
		    | (((limit >> 16) & 0xfull) << 48)
		    | (((base >> 24) & 0xffull) << 56);
		gdt[7] = base >> 32;
	}

	/*
	 * Save RFLAGS across the switch: when called early, interrupts
	 * are already off and must stay off; from cpu_init, IF is on
	 * and must be restored.  Between lgdt and the SS reload the
	 * old selectors (0x28/0x30) are invalid in the new GDT, and a
	 * tick landing in that window would iret back to SS=0x30 and
	 * #GP.
	 */
	__asm__ volatile(
	    "pushfq\n"
	    "cli\n"
	    "lgdt %0\n"
	    "pushq $0x08\n"
	    "leaq 1f(%%rip), %%rax\n"
	    "pushq %%rax\n"
	    "lretq\n"
	    "1:\n"
	    "movw $0x10, %%ax\n"
	    "movw %%ax, %%ds\n"
	    "movw %%ax, %%es\n"
	    "movw %%ax, %%ss\n"
	    "movw %%ax, %%fs\n"
	    "movw %%ax, %%gs\n"
	    "movw $0x30, %%ax\n"
	    "ltr %%ax\n"
	    "popfq\n"
	    : : "m"(gdtr) : "rax", "memory");
}

/* -------------------------------------------------------------- MSRs */

static inline uint64_t
rdmsr(uint32_t msr)
{
	uint32_t lo, hi;

	__asm__ volatile("rdmsr" : "=a"(lo), "=d"(hi) : "c"(msr));
	return ((uint64_t)hi << 32) | lo;
}

void
wrmsr(uint32_t msr, uint64_t val)
{
	__asm__ volatile("wrmsr"
	    : : "c"(msr), "a"((uint32_t)(val & 0xffffffffu)),
		"d"((uint32_t)(val >> 32)) : "memory");
}

/*
 * The syscall entry is assembly, so the current kernel stack top lives
 * in a plain global rather than a swapgs-reached per-CPU block: a
 * context switched in by schedule() can arrive from user mode (GS
 * already user) or kernel mode (GS kernel), and an unconditional
 * swapgs would be wrong in one of the two.
 */
extern uint64_t syscall_kstack;

uint64_t cpu_kstack_get(void)
{
	return syscall_kstack;
}

void
cpu_kstack_set(uint64_t top, uint64_t rsp0)
{
	syscall_kstack = top;
	tss.rsp0 = rsp0;
}

void
cpu_fsbase_set(uint64_t base)
{
	wrmsr(0xc0000100, base);		/* FS_BASE: glibc TLS */
}

void
cpu_init(void)
{
	uint64_t efer;

	cpu_gdt_init();

	/* EFER.SCE: enable syscall/sysret */
	efer = rdmsr(0xc0000080u);
	efer |= 1;
	wrmsr(0xc0000080u, efer);

	/* STAR: kernel CS 0x08/SS 0x10, user base 0x18
	 * (sysret: SS=(0x18+8)|3=0x23, CS=(0x18+16)|3=0x2b) */
	wrmsr(0xc0000081u,
	    ((uint64_t)0x18 << 48) | ((uint64_t)0x08 << 32));

	wrmsr(0xc0000082u, (uint64_t)syscall_entry);	/* LSTAR */

	/* SFMASK: IF|TF|DF|NT|AC cleared on syscall entry */
	wrmsr(0xc0000084u, 0x44700ull);	/* SFMASK: IF|TF|DF|NT|AC on entry */

	/*
	 * SSE: glibc's string/memory routines use SSE2 unconditionally
	 * on x86_64 (`movd`/`movdqu`) and #UD unless the OS has enabled
	 * the FXSAVE area and SSE exceptions.  CR0.EM must be clear and
	 * CR0.MP set (both already are in QEMU, but be explicit).
	 */
	{
		uint64_t cr0, cr4;

		__asm__ volatile("movq %%cr0, %0" : "=r"(cr0));
		cr0 &= ~(1ull << 2);		/* EM = 0: no x87 emulation */
		cr0 |= (1ull << 1);		/* MP = 1 */
		__asm__ volatile("movq %0, %%cr0" : : "r"(cr0) : "memory");

		__asm__ volatile("movq %%cr4, %0" : "=r"(cr4));
		cr4 |= (1ull << 9) | (1ull << 10);	/* OSFXSR | OSXMMEXCPT */
		__asm__ volatile("movq %0, %%cr4" : : "r"(cr4) : "memory");
		__asm__ volatile("fninit");
	}

	cpu_kstack_set(0, 0);
}
