/*
 * Limine boot protocol request structures.
 *
 * These live in .limine_requests so the loader can scan them out of the
 * final ELF.  Magic values must match limine/limine.h (v8.x binary branch)
 * - bump both when upgrading Limine.
 *
 * Keep this file pure data: it is linked before the kernel's .bss exists.
 */

	.section .limine_requests, "a"
	.balign 8

	.globl	limine_requests_start_marker
limine_requests_start_marker:
	.quad	0xf6b8f4b39de7d1ae, 0xfab91a6940fcb9cf
	.quad	0x785c6ed015d3e316, 0x181e920a7852b9d9

	/* base revision 1 */
	.globl	limine_base_revision
limine_base_revision:
	.quad	0xf9562b2d5c95a6c8	/* LIMINE_BASE_REVISION magic */
	.quad	0x6a7b384944536bdc	/* overwritten with loaded revision */
	.quad	1			/* requested revision */

	/* HHDM request: { COMMON_MAGIC, 0x48dcf1cb8ad2b852,
	 *                 0x63984e959a98244b } */
	.balign 8
limine_hhdm_request:
	.quad	0xc7b1dd30df4c8b88, 0x0a82e883a194f07b
	.quad	0x48dcf1cb8ad2b852, 0x63984e959a98244b
	.quad	0			/* revision */
	.globl	limine_hhdm_response
limine_hhdm_response:
	.quad	0			/* response, filled by loader */

	/* framebuffer request: { COMMON_MAGIC, 0x9d5827dcd881dd75,
	 *                        0xa3148604f6fab11b }, rev, response */
	.balign 8
limine_fb_request:
	.quad	0xc7b1dd30df4c8b88, 0x0a82e883a194f07b
	.quad	0x9d5827dcd881dd75, 0xa3148604f6fab11b
	.quad	0			/* revision */
	.globl	limine_fb_response
limine_fb_response:
	.quad	0			/* response, filled by loader */

	/* memory map request: { COMMON_MAGIC, 0x67cf3d9d378a806f,
	 *                        0xe304acdfc50c3c62 }, rev, response */
	.balign 8
limine_memmap_request:
	.quad	0xc7b1dd30df4c8b88, 0x0a82e883a194f07b
	.quad	0x67cf3d9d378a806f, 0xe304acdfc50c3c62
	.quad	0			/* revision */
	.globl	limine_memmap_response
limine_memmap_response:
	.quad	0			/* response, filled by loader */

	.globl	limine_requests_end_marker
limine_requests_end_marker:
	.quad	0xadc0e0531bb10d03, 0x9572709f31764c62
