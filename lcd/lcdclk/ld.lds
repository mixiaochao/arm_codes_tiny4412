OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x50008000;

	.text : 
	{
		*(.text)
	}
	.align = 4;

	.data : 
	{
		*(.data)
	}
	.align = 4;

	.bss : 
	{
		*(.bss)
	}
	. = ALIGN(4);
}
