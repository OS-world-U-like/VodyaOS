/*
 * VodyaOS x86_64 kernel link map.
 *
 * Limine boot protocol requirement: the kernel must be linked in the
 * higher half, with virtual addresses offset from physical by
 * 0xffffffff80000000 (LIMINE_KERNEL_BASE).  Physical addresses start
 * at 1 MiB.  Limine enters the kernel at its ELF entry point (the
 * higher-half virtual address) with paging already enabled and the
 * kernel mapped there, so _start runs at its linked address directly.
 */

ENTRY(_start)

KERNEL_BASE = 0xffffffff80000000;
KERNEL_PHYS = 0x00100000;

SECTIONS
{
	. = KERNEL_BASE;

	__text_vma = .;
	.text : AT(__text_vma - KERNEL_BASE + KERNEL_PHYS) ALIGN(16) {
		*(.text.entry)
		*(.text .text.*)
	}

	. = ALIGN(0x1000);
	__limine_vma = .;
	.limine_requests : AT(__limine_vma - KERNEL_BASE + KERNEL_PHYS) {
		KEEP(*(.limine_requests))
	}

	. = ALIGN(0x1000);
	__rodata_vma = .;
	.rodata : AT(__rodata_vma - KERNEL_BASE + KERNEL_PHYS) {
		*(.rodata .rodata.*)
	}

	. = ALIGN(0x1000);
	__data_vma = .;
	.data : AT(__data_vma - KERNEL_BASE + KERNEL_PHYS) {
		*(.data .data.*)
		_edata = .;
	}

	. = ALIGN(16);
	.bss : AT(__data_vma - KERNEL_BASE + KERNEL_PHYS + SIZEOF(.data)) {
		*(COMMON)
		*(.bss .bss.*)
		*(.sbss .sbss.*)
	}

	. = ALIGN(16);
	_end = .;
	_etext = ADDR(.text) + SIZEOF(.text);

	/DISCARD/ : {
		*(.comment)
		*(.note .note.*)
		*(.eh_frame .eh_frame_hdr)
	}
}
