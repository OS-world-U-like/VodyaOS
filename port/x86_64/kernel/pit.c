/*
 * PIT (8253/8254) channel 0 timer: the kernel heartbeat.
 * Channel 0 is wired to IRQ0; we run it in square-wave mode and let
 * the handler count jiffies.  Later scheduling/vfs timeouts hang off
 * this counter.
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

#define PIT_FREQ	1193182		/* input clock Hz */

#define PIT_CH0		0x40
#define PIT_CMD		0x43

static inline void
outb(uint16_t port, uint8_t val)
{
	__asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void irq_register(int irq, void (*fn)(uint64_t *frame));

volatile uint64_t jiffies;

static void
pit_tick(uint64_t *frame)
{
	jiffies++;
}

void
pit_init(int hz)
{
	uint16_t div = (uint16_t)(PIT_FREQ / hz);

	outb(PIT_CMD, 0x36);		/* ch0, lobyte/hibyte, mode 3 */
	outb(PIT_CH0, div & 0xff);
	outb(PIT_CH0, div >> 8);
	irq_register(0, pit_tick);
}
