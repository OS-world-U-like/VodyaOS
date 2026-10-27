/*
 * VodyaOS x86_64 kernel link map.
 *
 * This is a flat higher-half-less image for now.  Once the kernel
 * has a real long-mode entry and page tables this will move to the
 * conventional -2GB kernel virtual address.
 */

ENTRY(_start)

SECTIONS
{
	. = 0x00100000;

	.text : ALIGN(16) {
		*(.text.entry)
		*(.text .text.*)
	}

	. = ALIGN(16);
	.rodata : {
		*(.rodata .rodata.*)
	}

	. = ALIGN(16);
	.data : {
		*(.data .data.*)
		_edata = .;
	}

	. = ALIGN(16);
	.bss : {
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
