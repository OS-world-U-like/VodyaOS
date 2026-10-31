/*
 * Read-only Btrfs for the VodyaOS executive.
 *
 * Supports the on-disk shapes btrfs-progs produces for a plain
 * single-device filesystem (default profile "single", no
 * compression): superblock at 64 KiB, chunk tree for logical ->
 * physical mapping (bootstrapped from the sys_chunk_array), root
 * tree -> fs tree, directory items (crc32c name hash), inode items
 * and regular/inline file extents.  Metadata checksums are parsed
 * but not verified; zlib/lzo/zstd extents are rejected.
 *
 * All block addresses in btrfs are LOGICAL; btrfs_map() turns them
 * into physical offsets inside partition 2 via the chunk tree.
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

int ata_read_sector(uint64_t lba, uint8_t *buf);
void console_puts(const char *s);
void console_write(const char *s, unsigned long n);
void putdec(uint64_t v);
void puthex(uint64_t v);

#define BTRFS_MAGIC	0x4d5f53665248425full	/* "_BHRfS_M" */
/*
 * The btrfs superblock sits 64 KiB into the *volume* (= partition 2);
 * all chunk physical offsets are volume-relative too, so every disk
 * read goes through part_base (the partition-2 start LBA, passed in
 * by the caller -- 1050624 for the image mkimage.sh builds).
 */
#define BTRFS_SB_LBA	128			/* 64 KiB / 512B */
static uint64_t part_base;			/* partition start, in LBAs */
#define BTRFS_SUPER_MIRROR_OFFSET (64 * 1024)

/* key types */
/* a 16 KiB leaf holds at most ~650 items; item arrays must cover a
 * whole leaf or searches for later keys silently miss */
#define MAX_NODE_ITEMS	1024

#define KT_INODE_ITEM	1
#define KT_ROOT_ITEM	132			/* BTRFS_ROOT_ITEM_KEY */
#define KT_DIR_ITEM	84
#define KT_DIR_INDEX	96
#define KT_EXTENT_DATA	108
#define KT_DEV_ITEM	216
#define KT_CHUNK_ITEM	228

#define FS_TREE_ID	5ull

/* ---------------------------------------------------------------- crc32c */

static uint32_t crc32c_tab[256];

static void
crc32c_init(void)
{
	uint32_t i, j, c;

	for (i = 0; i < 256; i++) {
		c = i;
		for (j = 0; j < 8; j++)
			c = (c & 1) ? (0x82f63b78u ^ (c >> 1)) : (c >> 1);
		crc32c_tab[i] = c;
	}
}

static uint32_t
crc32c(uint32_t seed, const uint8_t *p, uint32_t n)
{
	uint32_t c = seed;

	while (n--)
		c = crc32c_tab[(c ^ *p++) & 0xff] ^ (c >> 8);
	return c;
}

/* ------------------------------------------------------------- superblock */

static uint8_t sb_block[4096];

struct btrfs_sb {
	uint32_t sectorsize;
	uint32_t nodesize;
	uint64_t root;			/* root tree logical */
	uint64_t chunk_root;		/* chunk tree logical */
};

static struct btrfs_sb sb;

static int
sb_parse(void)
{
	uint64_t magic;
	int i;

	for (i = 0; i < 8; i++)
		if (ata_read_sector(part_base + BTRFS_SB_LBA + i,
		    sb_block + i * 512) != 0)
			return -1;

	magic = 0;
	for (i = 0; i < 8; i++)
		magic |= ((uint64_t)sb_block[64 + i]) << (8 * i);
	if (magic != BTRFS_MAGIC)
		return -1;

	sb.sectorsize = sb_block[144] | (sb_block[145] << 8) |
	    (sb_block[146] << 16) | (sb_block[147] << 24);
	sb.nodesize = sb_block[148] | (sb_block[149] << 8) |
	    (sb_block[150] << 16) | (sb_block[151] << 24);
	sb.root = 0;
	sb.chunk_root = 0;
	for (i = 0; i < 8; i++) {
		sb.root |= ((uint64_t)sb_block[80 + i]) << (8 * i);
		sb.chunk_root |= ((uint64_t)sb_block[88 + i]) << (8 * i);
	}
	if (sb.sectorsize != 4096 && sb.sectorsize != 512)
		return -1;
	if (sb.nodesize < 4096 || sb.nodesize > 65536 ||
	    (sb.nodesize & (sb.nodesize - 1)))
		return -1;
	return 0;
}

/* ------------------------------------------------------------ chunk map */

struct chunkmap {
	uint64_t logical;		/* start (key offset) */
	uint64_t length;
	uint64_t physical;		/* stripe 0 offset */
};

#define MAX_CHUNKS	128
static struct chunkmap chunks[MAX_CHUNKS];
static int nchunks;

static void
chunk_add(uint64_t logical, uint64_t length, uint64_t physical)
{
	int i;

	for (i = 0; i < nchunks; i++)
		if (chunks[i].logical == logical)
			return;
	if (nchunks >= MAX_CHUNKS)
		return;
	chunks[nchunks].logical = logical;
	chunks[nchunks].length = length;
	chunks[nchunks].physical = physical;
	nchunks++;
}

/*
 * The superblock's sys_chunk_array carries key+chunk pairs for the
 * SYSTEM chunks: enough to read the chunk tree itself.
 */
static int
parse_sys_chunk_array(void)
{
	uint32_t arr_size = sb_block[160] | (sb_block[161] << 8) |
	    (sb_block[162] << 16) | (sb_block[163] << 24);
	/* btrfs_super_block.sys_chunk_array is at 0x32b (823+...):
	 * csum 0x00, fsid 0x20, ..., sys_chunk_array_size 0xa0, then
	 * the dev_item/label/... padding up to 0x32b.  Each entry is a
	 * 17-byte disk_key (objectid u64, type u8, offset u64) followed
	 * by a btrfs_chunk (48 bytes) and 32 bytes per stripe. */
	const uint8_t *p = sb_block + 0x32b;
	const uint8_t *end = p + arr_size;

	while (p + 17 + 48 <= end) {
		uint64_t logical = 0, length = 0, physical = 0;
		uint8_t type = p[8];
		const uint8_t *chunk = p + 17;
		uint32_t num_stripes;
		int i;

		if (type != KT_CHUNK_ITEM)
			break;
		for (i = 0; i < 8; i++) {
			logical |= ((uint64_t)p[9 + i]) << (8 * i);
			length |= ((uint64_t)chunk[i]) << (8 * i);
			physical |= ((uint64_t)chunk[48 + 8 + i]) << (8 * i);
		}
		num_stripes = chunk[44] | (chunk[45] << 8) |
		    (chunk[46] << 16) | (chunk[47] << 24);
		if (num_stripes < 1)		/* raid0/5/6: unsupported */
			return -1;
		/* DUP keeps both stripes at the same physical offset, so
		 * stripe 0 is always a valid source. */
		chunk_add(logical, length, physical);
		p += 17 + 48 + 32 * num_stripes;
	}
	return 0;
}

static int
btrfs_map(uint64_t logical, uint64_t *physical, uint64_t *maxlen)
{
	int i;

	for (i = 0; i < nchunks; i++) {
		if (logical >= chunks[i].logical &&
		    logical < chunks[i].logical + chunks[i].length) {
			*physical = chunks[i].physical +
			    (logical - chunks[i].logical);
			*maxlen = chunks[i].logical + chunks[i].length -
			    logical;
			return 0;
		}
	}
	return -1;
}

/* read `bytes` at logical address into buf (sector-bounce: always
 * correct, fast enough for metadata and file reads) */
static int
btrfs_read(uint64_t logical, uint32_t bytes, uint8_t *buf)
{
	static uint8_t tmp[512];

	while (bytes) {
		uint64_t phys, avail, n;
		uint64_t lba;
		uint32_t off, take, i;

		if (btrfs_map(logical, &phys, &avail) != 0)
			return -1;
		n = (avail < bytes) ? avail : bytes;
		lba = part_base + (phys >> 9);
		off = (uint32_t)(phys & 511);
		while (n) {
			take = 512 - off;
			if (take > n)
				take = (uint32_t)n;
			if (ata_read_sector(lba, tmp) != 0)
				return -1;
			for (i = 0; i < take; i++)
				buf[i] = tmp[off + i];
			buf += take;
			n -= take;
			bytes -= take;
			logical += take;
			lba++;
			off = 0;
		}
	}
	return 0;
}

/* --------------------------------------------------------- tree walking */

struct bkey {
	uint64_t objectid;
	uint8_t type;
	uint64_t offset;
};

static uint8_t nodebuf[65536];		/* max nodesize */

/* parse a key from on-disk little-endian bytes */
static void
key_get(const uint8_t *p, struct bkey *k)
{
	int i;

	k->objectid = 0;
	k->offset = 0;
	for (i = 0; i < 8; i++) {
		k->objectid |= ((uint64_t)p[i]) << (8 * i);
		k->offset |= ((uint64_t)p[9 + i]) << (8 * i);
	}
	k->type = p[8];
}

static int
key_cmp(const struct bkey *a, const struct bkey *b)
{
	if (a->objectid != b->objectid)
		return a->objectid < b->objectid ? -1 : 1;
	if (a->type != b->type)
		return a->type < b->type ? -1 : 1;
	if (a->offset != b->offset)
		return a->offset < b->offset ? -1 : 1;
	return 0;
}

/*
 * Read a tree block by logical address and return its item count;
 * items' data pointers are stored into item_data[] (absolute).
 */
struct titem {
	struct bkey key;
	const uint8_t *data;
	uint32_t size;
};

static int
read_node(uint64_t logical, struct titem *items, int maxitems, int *level)
{
	uint32_t nodesize = sb.nodesize;
	uint32_t nritems;
	uint8_t hdr_level;
	int i;

	if (sb.nodesize > sizeof(nodebuf))
		return -1;
	if (btrfs_read(logical, nodesize, nodebuf) != 0) {
		return -1;
	}

	nritems = nodebuf[96] | (nodebuf[97] << 8) |
	    (nodebuf[98] << 16) | (nodebuf[99] << 24);
	if (nritems > (uint32_t)maxitems)
		nritems = (uint32_t)maxitems;
	hdr_level = nodebuf[100];
	*level = hdr_level;

	if (hdr_level > 0) {
		/* internal: items are key_ptr (key 17 + bytenr 8 + gen 8) */
		for (i = 0; i < (int)nritems && i < maxitems; i++) {
			const uint8_t *kp = nodebuf + 101 + 33 * i;
			uint64_t child = 0;
			int k;

			key_get(kp, &items[i].key);
			for (k = 0; k < 8; k++)
				child |= ((uint64_t)kp[17 + k]) << (8 * k);
			items[i].data = (const uint8_t *)(unsigned long)child;
			items[i].size = 0;
		}
		return nritems;
	}

	for (i = 0; i < (int)nritems && i < maxitems; i++) {
		const uint8_t *it = nodebuf + 101 + 25 * i;
		uint32_t off, size;

		key_get(it, &items[i].key);
		off = it[17] | (it[18] << 8) | (it[19] << 16) |
		    (it[20] << 24);
		size = it[21] | (it[22] << 8) | (it[23] << 16) |
		    (it[24] << 24);
		/* leaf data area starts right after the header; item
		 * offsets count from there and grow toward the end */
		items[i].data = nodebuf + 101 + off;
		items[i].size = size;
	}
	return nritems;
}

/*
 * Search a tree for the first item >= key.  Returns 0 and fills
 * `out` (data pointer only valid until the next read_node), -1 if
 * absent.  `root_logical` is the tree's root block.
 */
static int
tree_search(uint64_t root_logical, const struct bkey *want, struct titem *out)
{
	static struct titem items[MAX_NODE_ITEMS];
	uint64_t block = root_logical;
	int level, n, i;

	for (;;) {
		n = read_node(block, items, MAX_NODE_ITEMS, &level);
		if (n <= 0)
			return -1;
		if (level > 0) {
			/*
			 * Internal keys are the FIRST key of each child.
			 * The child that can hold `want` is the last one
			 * whose first key is <= want -- picking the first
			 * key >= want lands in the following leaf and
			 * every exact search misses (that is what made
			 * all btrfs path lookups fail).
			 */
			int pick = 0;

			for (i = 0; i < n; i++) {
				if (key_cmp(&items[i].key, want) <= 0)
					pick = i;
				else
					break;
			}
			block = (uint64_t)(unsigned long)items[pick].data;
			continue;
		}
		for (i = 0; i < n; i++) {
			if (key_cmp(&items[i].key, want) >= 0) {
				if (key_cmp(&items[i].key, want) != 0)
					return -1;
				*out = items[i];
				return 0;
			}
		}
		return -1;
	}
}

/*
 * Search a tree for the first item >= key, without requiring equality.
 * Used to walk a directory's DIR_INDEX items in order.
 */
static int
tree_search_ge(uint64_t root_logical, const struct bkey *want,
    struct titem *out)
{
	static struct titem items[MAX_NODE_ITEMS];
	uint64_t block = root_logical;
	int level, n, i;

	for (;;) {
		n = read_node(block, items, MAX_NODE_ITEMS, &level);
		if (n <= 0)
			return -1;
		if (level > 0) {
			int pick = -1;

			for (i = 0; i < n; i++) {
				if (key_cmp(&items[i].key, want) <= 0)
					pick = i;
				else
					break;
			}
			if (pick < 0)
				pick = 0;
			block = (uint64_t)(unsigned long)items[pick].data;
			continue;
		}
		for (i = 0; i < n; i++) {
			if (key_cmp(&items[i].key, want) >= 0) {
				*out = items[i];
				return 0;
			}
		}
		return -1;
	}
}

/* find the LAST item <= key (for extent lookup by file offset) */
static int
tree_search_le(uint64_t root_logical, const struct bkey *want,
    struct titem *out)
{
	static struct titem items[MAX_NODE_ITEMS];
	uint64_t block = root_logical;
	int level, n, i;

	for (;;) {
		n = read_node(block, items, MAX_NODE_ITEMS, &level);
		if (n <= 0)
			return -1;
		if (level > 0) {
			int pick = -1;

			for (i = 0; i < n; i++) {
				if (key_cmp(&items[i].key, want) <= 0)
					pick = i;
				else
					break;
			}
			if (pick < 0)
				return -1;
			block = (uint64_t)(unsigned long)items[pick].data;
			continue;
		}
		{
			int pick = -1;

			for (i = 0; i < n; i++) {
				if (key_cmp(&items[i].key, want) <= 0)
					pick = i;
				else
					break;
			}
			if (pick < 0)
				return -1;
			*out = items[pick];
			return 0;
		}
	}
}

/* ------------------------------------------------------------- root tree */

static uint64_t fs_tree_root;

static int
find_fs_tree(void)
{
	struct bkey want;
	struct titem it;

	want.objectid = FS_TREE_ID;
	want.type = KT_ROOT_ITEM;
	want.offset = 0;
	if (tree_search(sb.root, &want, &it) != 0)
		return -1;
	if (it.key.objectid != FS_TREE_ID || it.key.type != KT_ROOT_ITEM)
		return -1;
	/* btrfs_root_item.bytenr at offset 176 */
	{
		const uint8_t *r = it.data + 176;
		uint64_t bytenr = 0;
		int i;

		for (i = 0; i < 8; i++)
			bytenr |= ((uint64_t)r[i]) << (8 * i);
		fs_tree_root = bytenr;
	}
	return fs_tree_root ? 0 : -1;
}

/* ------------------------------------------------------- chunk tree walk */

/* parse one CHUNK_ITEM payload (item->data) into the chunk map */
static void
add_chunk_item(const struct titem *it)
{
	const uint8_t *c = it->data;
	uint64_t length = 0, phys = 0;
	uint32_t nstripes;
	int k;

	for (k = 0; k < 8; k++) {
		length |= ((uint64_t)c[k]) << (8 * k);
		phys |= ((uint64_t)c[48 + 8 + k]) << (8 * k);
	}
	nstripes = c[44] | (c[45] << 8) | (c[46] << 16) | (c[47] << 24);
	/* DUP repeats the same physical stripe twice; stripe 0 is
	 * always a valid source.  RAID0/5/6 would need striping. */
	if (nstripes >= 1)
		chunk_add(it->key.offset, length, phys);
}

/*
 * Recursive walk of the chunk tree.  mkfs.btrfs makes it a single
 * leaf on a small filesystem (sb.chunk_root_level == 0), where the
 * old "descend to level 1, then scan the children" logic never
 * looked at the root block itself and silently added no DATA or
 * METADATA chunks -- every later tree read then had no mapping.
 * Copy child pointers out first: read_node() reuses nodebuf.
 */
static int
scan_chunk_node(uint64_t block, int depth)
{
	static struct titem items[MAX_NODE_ITEMS];
	uint64_t kids[64];
	int level, n, i;

	if (depth > 8)
		return 0;
	n = read_node(block, items, MAX_NODE_ITEMS, &level);
	if (n > 64)
		n = 64;
	if (n <= 0)
		return -1;
	if (n > 64)
		n = 64;
	if (level == 0) {
		for (i = 0; i < n; i++)
			if (items[i].key.type == KT_CHUNK_ITEM)
				add_chunk_item(&items[i]);
		return 0;
	}
	for (i = 0; i < n; i++)
		kids[i] = (uint64_t)(unsigned long)items[i].data;
	for (i = 0; i < n; i++)
		if (scan_chunk_node(kids[i], depth + 1) != 0)
			return -1;
	return 0;
}

static int
load_chunk_tree(void)
{
	return scan_chunk_node(sb.chunk_root, 0);
}

/* ------------------------------------------------------------ path lookup */

static uint64_t cur_dirid;		/* resolved inode */
static uint64_t cur_size;
static uint16_t cur_mode;

static int
inode_get(uint64_t ino)
{
	struct bkey want;
	struct titem it;

	want.objectid = ino;
	want.type = KT_INODE_ITEM;
	want.offset = 0;
	if (tree_search(fs_tree_root, &want, &it) != 0)
		return -1;
	cur_size = 0;
	cur_mode = 0;
	{
		/* btrfs_inode_item: generation 0, transid 8, size 16,
		 * nbytes 24, block_group 32, nlink 40, uid 44, gid 48,
		 * mode 52 ... */
		int i;

		for (i = 0; i < 8; i++)
			cur_size |= ((uint64_t)it.data[16 + i]) << (8 * i);
		cur_mode = it.data[52] | (it.data[53] << 8);
	}
	return 0;
}

static int
dir_lookup(uint64_t dirid, const char *name, uint64_t *child)
{
	uint32_t h, hx, tries;
	struct bkey want;
	struct titem it;
	uint32_t nlen = 0;
	const char *q;

	for (q = name; *q; q++)
		nlen++;
	if (nlen == 0 || nlen > 200)
		return -1;

	/*
	 * btrfs_name_hash() is crc32c(~1, name, len) -- note the seed:
	 * ~1 (0xfffffffe), not the conventional 0xffffffff.  A wrong
	 * seed made every directory lookup miss, so the kernel silently
	 * fell back to the FAT bootstrap partition for every file.
	 */
	h = crc32c(0xfffffffeu, (const uint8_t *)name, nlen);
	for (tries = 0; tries < 1; tries++) {
		hx = h;
		want.objectid = dirid;
		want.type = KT_DIR_ITEM;
		want.offset = hx;
		if (tree_search(fs_tree_root, &want, &it) != 0)
			continue;
		/* dir items can share the hash slot: verify the name */
		{
			const uint8_t *d = it.data;
			uint32_t name_len = d[27] | (d[28] << 8);
			uint8_t dtype = d[29];
			uint64_t c;
			uint32_t i;
			int match = 1;

			if (it.key.offset != hx)
				continue;
			if (name_len != nlen)
				continue;
			for (i = 0; i < nlen; i++)
				if (d[30 + i] != name[i]) {
					match = 0;
					break;
				}
			if (!match)
				continue;
			(void)dtype;		/* 1=file, 2=dir, ... */
			c = 0;
			for (i = 0; i < 8; i++)
				c |= ((uint64_t)d[i]) << (8 * i);
			*child = c;
			return 0;
		}
	}
	return -1;
}

int
btrfs_lookup(const char *path, uint64_t *ino, uint64_t *size, uint16_t *mode)
{
	uint64_t dirid = 256;			/* root dir inode */
	const char *p = path;

	if (!fs_tree_root)
		return -1;
	while (*p == '/')
		p++;
	while (*p) {
		char comp[128];
		int ci = 0;
		uint64_t child;

		while (*p && *p != '/' && ci < 127)
			comp[ci++] = *p++;
		comp[ci] = 0;
		while (*p == '/')
			p++;

		if (dir_lookup(dirid, comp, &child) != 0)
			return -1;
		if (inode_get(child) != 0)
			return -1;
		dirid = child;
		*ino = child;
	}
	*ino = dirid;
	*size = cur_size;
	*mode = cur_mode;
	return 0;
}

/*
 * Sequential reads (exec loads an ELF one page at a time) would do a
 * full tree search per page.  Remember the last regular extent and
 * serve reads that stay inside it straight from the disk mapping.
 */
static int	xc_valid;
static uint64_t	xc_ino, xc_off, xc_len, xc_disk;

/* a 16 KiB leaf holds at most ~650 items; item arrays must cover a
 * whole leaf or searches for later keys silently miss */
/* file: read len at off via extent items */
uint32_t
btrfs_read_file(uint64_t ino, uint64_t off, uint32_t len, uint8_t *buf)
{
	uint32_t done = 0;

	while (done < len) {
		struct bkey want;
		struct titem it;
		uint64_t fileoff, ram;
		const uint8_t *d;
		uint8_t type, comp;
		uint32_t take, i;
		uint64_t disk_bytenr;

		if (xc_valid && xc_ino == ino &&
		    off + done >= xc_off && off + done < xc_off + xc_len) {
			uint64_t rel = off + done - xc_off;
			uint32_t avail = (uint32_t)(xc_len - rel);
			uint32_t take = (avail < len - done) ? avail :
			    len - done;

			if (btrfs_read(xc_disk + rel, take, buf + done) != 0)
				break;
			done += take;
			continue;
		}

		want.objectid = ino;
		want.type = KT_EXTENT_DATA;
		want.offset = off + done;
		if (tree_search_le(fs_tree_root, &want, &it) != 0)
			break;
		if (it.key.type != KT_EXTENT_DATA ||
		    it.key.objectid != ino)
			break;
		d = it.data;
		fileoff = it.key.offset;
		ram = 0;
		for (i = 0; i < 8; i++)
			ram |= ((uint64_t)d[8 + i]) << (8 * i);
		comp = d[16];
		type = d[20];
		if (comp != 0)
			break;			/* compressed: unsupported */
		if (fileoff > off + done)
			break;			/* hole without item */

		if (type == 0) {
			/* inline extent: data after 21-byte header */
			uint64_t rel = off + done - fileoff;
			uint32_t avail = (uint32_t)(ram - rel);

			if (rel >= ram)
				break;
			take = (avail < len - done) ? avail : len - done;
			for (i = 0; i < take; i++)
				buf[done + i] = d[21 + rel + i];
			done += take;
			continue;
		}
		if (type != 1)
			break;			/* prealloc/other */
		disk_bytenr = 0;
		for (i = 0; i < 8; i++)
			disk_bytenr |= ((uint64_t)d[21 + i]) << (8 * i);
		if (disk_bytenr == 0)
			break;			/* hole */
		{
			uint64_t rel = off + done - fileoff;
			uint32_t avail, take;

			if (rel >= ram)
				break;
			avail = (uint32_t)(ram - rel);
			take = (avail < len - done) ? avail : len - done;
			if (btrfs_read(disk_bytenr + rel, take,
			    buf + done) != 0)
				break;
			xc_valid = 1;
			xc_ino = ino;
			xc_off = fileoff;
			xc_len = ram;
			xc_disk = disk_bytenr;
			done += take;
		}
	}
	return done;
}

int
btrfs_init(uint64_t base_lba)
{
	part_base = base_lba;
	nchunks = 0;
	fs_tree_root = 0;
	crc32c_init();
	if (sb_parse() != 0) {
		console_puts("DBG btrfs: sb_parse failed\r\n");
		return -1;
	}
	if (parse_sys_chunk_array() != 0) {
		console_puts("DBG btrfs: sys_chunk_array failed\r\n");
		return -1;
	}
	if (load_chunk_tree() != 0) {
		console_puts("DBG btrfs: chunk tree failed\r\n");
		return -1;
	}
	if (find_fs_tree() != 0) {
		console_puts("DBG btrfs: fs tree failed\r\n");
		return -1;
	}
	return 0;
}

/*
 * Read one DIR_INDEX entry of `dirid` at or after `index`.  Fills the
 * entry name, the child inode, the btrfs dtype (1 reg, 2 dir, ...) and
 * the index to pass next time.  Returns 0, or -1 when the directory is
 * exhausted.
 */
int
btrfs_readdir(uint64_t dirid, uint32_t index, uint32_t *next,
    char *name, uint64_t *child, uint8_t *dtype)
{
	struct bkey want;
	struct titem it;
	const uint8_t *d;
	uint32_t name_len, i;

	if (!fs_tree_root)
		return -1;
	want.objectid = dirid;
	want.type = KT_DIR_INDEX;
	want.offset = index;
	if (tree_search_ge(fs_tree_root, &want, &it) != 0)
		return -1;
	if (it.key.objectid != dirid || it.key.type != KT_DIR_INDEX)
		return -1;
	d = it.data;
	if (it.size < 30)
		return -1;
	name_len = d[27] | (d[28] << 8);
	if (name_len > 200 || it.size < 30 + name_len)
		return -1;
	{
		uint64_t c = 0;

		for (i = 0; i < 8; i++)
			c |= ((uint64_t)d[i]) << (8 * i);
		*child = c;
	}
	for (i = 0; i < name_len; i++)
		name[i] = (char)d[30 + i];
	name[name_len] = 0;
	*dtype = d[29];
	*next = (uint32_t)it.key.offset + 1;
	return 0;
}
