/*
 * Minimal read-only FAT32 for the ESP.
 *
 * The boot image is GPT: p1 = FAT32 ESP (bash, tools live there
 * until btrfs rootfs takes over), so the kernel's first filesystem
 * consumer is this driver.  Supports: 8.3 + LFN directory entries,
 * cluster chains, absolute paths with '/' separators, and
 * positional reads.
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

int ata_read_sector(uint64_t lba, uint8_t *buf);
void console_puts(const char *s);

#define SEC	512

static uint32_t part_start;		/* LBA of the FAT32 volume */
static uint32_t fat_start;
static uint32_t data_start;		/* first cluster's LBA */
static uint32_t sectors_per_clus;
static uint32_t root_clus;
static int fat_ok;
static uint8_t secbuf[SEC];

struct fatent {
	uint32_t cluster;
	uint32_t size;
};

static int
read_sec(uint32_t lba)
{
	return ata_read_sector(lba, secbuf);
}

int
fat_init(uint32_t lba)
{
	uint32_t fat_size, nfats, reserved;

	part_start = lba;
	if (read_sec(part_start) != 0)
		return -1;
	if (secbuf[510] != 0x55 || secbuf[511] != 0xaa)
		return -1;
	if (secbuf[82] != 'F' || secbuf[83] != 'A' || secbuf[84] != 'T')
		return -1;			/* not FAT32 */

	sectors_per_clus = secbuf[13];
	reserved = secbuf[14] | (secbuf[15] << 8);
	nfats = secbuf[16];
	fat_size = secbuf[36] | (secbuf[37] << 8) |
	    (secbuf[38] << 16) | (secbuf[39] << 24);
	root_clus = secbuf[44] | (secbuf[45] << 8) |
	    (secbuf[46] << 16) | (secbuf[47] << 24);

	fat_start = part_start + reserved;
	data_start = fat_start + nfats * fat_size;
	fat_ok = 1;
	return 0;
}

static uint32_t
fat_next(uint32_t clus)
{
	static uint8_t fatbuf[SEC];
	static uint32_t fatbuf_lba = 0xffffffffu;
	uint32_t fat_off = clus * 4;
	uint32_t sec = fat_start + fat_off / SEC;
	uint32_t idx = fat_off % SEC;
	uint32_t v;

	/* one-sector cache: a cluster walk sticks to a single FAT sector
	 * for 128 entries, so this removes almost all FAT traffic */
	if (sec != fatbuf_lba) {
		if (ata_read_sector(sec, fatbuf) != 0)
			return 0xfffffffl;	/* EOC on error */
		fatbuf_lba = sec;
	}
	v = fatbuf[idx] | (fatbuf[idx + 1] << 8) |
	    (fatbuf[idx + 2] << 16) | (fatbuf[idx + 3] << 24);
	return v & 0x0fffffffu;
}

static uint32_t
clus_lba(uint32_t clus)
{
	return data_start + (clus - 2) * sectors_per_clus;
}

/* read the whole cluster chain starting at clus into buf (<= max),
 * returns bytes read */
static uint32_t
chain_read(uint32_t clus, uint8_t *buf, uint32_t max)
{
	uint32_t got = 0;
	uint32_t clus_bytes = sectors_per_clus * SEC;
	int guard = 0;

	while (clus >= 2 && clus < 0x0ffffff8 && got < max) {
		uint32_t i;
		uint32_t n = (max - got < clus_bytes) ?
		    max - got : clus_bytes;

		for (i = 0; i < sectors_per_clus && i * SEC < n; i++) {
			if (ata_read_sector(clus_lba(clus) + i,
			    buf + got + i * SEC) != 0)
				return got;
		}
		got += n;
		clus = fat_next(clus);
		if (++guard > 200000)
			break;
	}
	return got;
}

/* one directory cluster-chain scan; name is '/'-free */
static int
dir_lookup(uint32_t dir_clus, const char *name, struct fatent *out)
{
	static uint8_t dbuf[64 * 1024];
	uint32_t n, i;
	char lfn[264];
	int lfn_len = 0;

	n = chain_read(dir_clus, dbuf, sizeof(dbuf));
	lfn[0] = 0;
	for (i = 0; i + 32 <= n; i += 32) {
		uint8_t *d = dbuf + i;
		uint8_t attr = d[11];

		if (d[0] == 0)
			break;			/* end of directory */
		if (d[0] == 0xe5) {
			lfn_len = 0;		/* deleted */
			continue;
		}
		if (attr == 0x0f) {		/* LFN fragment */
			int seq = d[0] & 0x1f;
			int k, p;
			uint16_t wc;

			if (seq > 20)
				continue;
			p = (seq - 1) * 13;
			for (k = 0; k < 13 && p + k < 260; k++) {
				if (k < 5)
					wc = d[1 + k * 2] |
					    (d[2 + k * 2] << 8);
				else if (k < 11)
					wc = d[14 + (k - 5) * 2] |
					    (d[15 + (k - 5) * 2] << 8);
				else
					wc = d[28 + (k - 11) * 2] |
					    (d[29 + (k - 11) * 2] << 8);
				lfn[p + k] = wc ? (char)wc : 0;
				if (!wc)
					break;
			}
			if (p + 13 > lfn_len)
				lfn_len = p + 13;
			lfn[lfn_len] = 0;
			continue;
		}
		if (attr & 0x08) {		/* volume label */
			lfn_len = 0;
			continue;
		}
		/* 8.3 entry */
		{
			char shortname[13];
			int j, k = 0;
			uint32_t clus, size;

			for (j = 0; j < 8 && d[j] != ' '; j++)
				shortname[k++] = d[j];
			if (d[8] != ' ') {
				shortname[k++] = '.';
				for (j = 8; j < 11 && d[j] != ' '; j++)
					shortname[k++] = d[j];
			}
			shortname[k] = 0;

			clus = (d[20] << 8) | (d[21] << 16) |
			    d[26] | (d[27] << 8);
			size = d[28] | (d[29] << 8) |
			    (d[30] << 16) | ((uint32_t)d[31] << 24);

			/* case-insensitive compare: LFN first, then 8.3 */
			{
				const char *cand = (lfn_len > 0) ? lfn : 0;
				int match = 0, m;

				if (cand) {
					for (m = 0; ; m++) {
						char a = cand[m], b = name[m];

						if (a >= 'A' && a <= 'Z')
							a += 32;
						if (b >= 'A' && b <= 'Z')
							b += 32;
						if (a != b)
							break;
						if (!a) {
							match = 1;
							break;
						}
					}
				}
				if (!match) {
					for (m = 0; ; m++) {
						char a = shortname[m];
						char b = name[m];

						if (a >= 'A' && a <= 'Z')
							a += 32;
						if (b >= 'A' && b <= 'Z')
							b += 32;
						if (a != b)
							break;
						if (!a) {
							match = 1;
							break;
						}
					}
				}
				if (match) {
					out->cluster = clus;
					out->size = size;
					return 0;
				}
			}
			lfn_len = 0;
		}
	}
	return -1;
}

/* walk a path like /gnu/bin/bash from the root */
int
fat_lookup(const char *path, struct fatent *out)
{
	char comp[64];
	uint32_t clus = root_clus;
	const char *p = path;
	int ci = 0;
	struct fatent e;

	if (!fat_ok)
		return -1;

	for (;;) {
		if (*p == '/') {
			p++;
			continue;
		}
		if (*p == 0)
			break;
		ci = 0;
		while (*p && *p != '/' && ci < 63)
			comp[ci++] = *p++;
		comp[ci] = 0;

		if (dir_lookup(clus, comp, &e) != 0)
			return -1;
		if (e.size == 0 && *p) {
			/* directory entry with size 0: descend */
		}
		clus = e.cluster;
		out->cluster = e.cluster;
		out->size = e.size;
	}
	return (out->cluster >= 2) ? 0 : -1;
}

uint32_t
fat_size(const struct fatent *e)
{
	return e->size;
}

/* positional read */
uint32_t
fat_read_at(const struct fatent *e, uint32_t off, uint32_t len, uint8_t *buf)
{
	static uint8_t cbuf[64 * 1024];
	/*
	 * Sequential-read cursor.  Callers (the ELF loader) read files
	 * front to back, but every call used to restart the walk from
	 * the first cluster: O(n^2) FAT traffic for a multi-megabyte
	 * binary (bash is 2.5 MiB -- hundreds of thousands of sector
	 * reads, minutes under TCG).  Remembering the last (cluster,
	 * byte offset) makes the fast path O(n).
	 */
	static uint32_t cur_first;	/* e->cluster the cursor is for */
	static uint32_t cur_clus;	/* next cluster */
	static uint32_t cur_pos;	/* byte offset of cur_clus */
	uint32_t clus_bytes;
	uint32_t clus = e->cluster;
	uint32_t pos = 0;
	uint32_t want = len;
	int guard = 0;

	if (off >= e->size)
		return 0;
	if (off + len > e->size)
		len = e->size - off;
	clus_bytes = sectors_per_clus * SEC;
	if (sizeof(cbuf) < clus_bytes)
		return 0;

	if (e->cluster == cur_first && off >= cur_pos) {
		clus = cur_clus;
		pos = cur_pos;
	}

	while (clus >= 2 && clus < 0x0ffffff8 && want > 0) {
		if (off < pos + clus_bytes) {
			uint32_t in = off - pos;
			uint32_t n = clus_bytes - in;

			if (n > want)
				n = want;
			chain_read(clus, cbuf, clus_bytes);
			{
				uint32_t k;

				for (k = 0; k < n; k++)
					buf[k] = cbuf[in + k];
			}
			buf += n;
			off += n;
			want -= n;
			if (want == 0) {
				/* next call resumes right here */
				cur_first = e->cluster;
				cur_clus = fat_next(clus);
				cur_pos = pos + clus_bytes;
				return len;
			}
		}
		pos += clus_bytes;
		clus = fat_next(clus);
		if (++guard > 200000)
			break;
	}
	cur_first = e->cluster;
	cur_clus = clus;
	cur_pos = pos;
	return len - want;
}
