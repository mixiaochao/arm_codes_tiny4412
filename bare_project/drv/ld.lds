OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
	      "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x43e00000;
	
	.text : {
		start.o(.text);
		*(.text);
	}

	. = ALIGN(4);

	.data : {
		*(.data);
	}

	. = ALIGN(4);

	millet_start = .;
	.millet : {
		*(.millet)
	}
	millet_end = .;

	. = ALIGN(4);

	milletbss_start = .;	
	.bss : {
		*(.bss);
	}
	milletbss_end = .;	
}
