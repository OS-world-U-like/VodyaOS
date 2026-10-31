/*
 * ATA PIO disk driver (primary master, 28-bit LBA, polling).
 * Just enough to read the boot image's partitions from qemu/real
 * hardware; interrupts are not used.
 *
 * NOTE: this only works where the legacy IDE ports (0x1f0..) exist:
 * `-M pc` (PIIX3) and real legacy hardware.  On `-M q35` the ICH9
 * exposes AHCI only -- 0x1f7 reads back 0xFF (floating bus) and every
 * wait times out.  An AHCI driver is the eventual fix for q35/real
 * SATA machines.
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

#define ATA_DATA	0x1f0
#define ATA_ERR		0x1f1
#define ATA_SECCNT	0x1f2
#define ATA_LBA0	0x1f3
#define ATA_LBA1	0x1f4
#define ATA_LBA2	0x1f5
#define ATA_DRIVE	0x1f6
#define ATA_STATUS	0x1f7
#define ATA_CMD		0x1f7
#define ATA_CONTROL	0x3f6

#define ST_BSY		0x80
#define ST_DRQ		0x08
#define ST_ERR		0x01

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

static inline uint16_t
inw(uint16_t port)
{
	uint16_t v;

	__asm__ volatile("inw %1, %0" : "=a"(v) : "Nd"(port));
	return v;
}

static int
ata_wait(void)
{
	int n;

	for (n = 0; n < 10000000; n++) {
		uint8_t st = inb(ATA_STATUS);

		if (!(st & ST_BSY)) {
			if (st & ST_ERR)
				return -1;
			if (st & ST_DRQ)
				return 0;
			if ((st & 0xf9) == 0)
				return -1;	/* no drive */
		}
	}
	return -1;
}

int
ata_ready(void)
{
	outb(ATA_DRIVE, 0xe0);
	(void)inb(ATA_STATUS);
	return ata_wait() == 0;
}

/* read `count` sectors (1..128) starting at lba into buf */
int
ata_read_sectors(uint64_t lba, uint32_t count, uint8_t *buf)
{
	uint32_t s, i;

	if (count == 0 || count > 128 || lba > 0x0fffffffu - count)
		return -1;
	outb(ATA_DRIVE, (uint8_t)(0xe0 | ((lba >> 24) & 0x0f)));
	outb(ATA_SECCNT, (uint8_t)count);
	outb(ATA_LBA0, (uint8_t)(lba & 0xff));
	outb(ATA_LBA1, (uint8_t)((lba >> 8) & 0xff));
	outb(ATA_LBA2, (uint8_t)((lba >> 16) & 0xff));
	outb(ATA_CMD, 0x20);			/* read sectors, PIO */

	for (s = 0; s < count; s++) {
		if (ata_wait() != 0) {
			extern void console_puts(const char *);
			extern void putdec(unsigned long long);

			console_puts("DBG ata fail lba=");
			putdec(lba + s);
			console_puts(" st=");
			putdec(inb(ATA_STATUS));
			console_puts("\r\n");
			return -1;
		}
		for (i = 0; i < 256; i++) {
			uint16_t w = inw(ATA_DATA);

			buf[i * 2] = (uint8_t)(w & 0xff);
			buf[i * 2 + 1] = (uint8_t)(w >> 8);
		}
		buf += 512;
	}
	(void)inb(ATA_STATUS);			/* drain */
	return 0;
}

/* read one sector into buf (512 bytes) */
int
ata_read_sector(uint64_t lba, uint8_t *buf)
{
	return ata_read_sectors(lba, 1, buf);
}
