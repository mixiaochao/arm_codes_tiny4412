

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
	      "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
	. = 0x50000000;

	.text : 
	{
		*(.text);
	} 
	. = ALIGN(4);

	_misec_start = .;
	.misec : 
	{
		*(.misec)
	}
	_misec_end = .;
	. = ALIGN(4);

	.data :
	{
		*(.data);
	}
	. = ALIGN(4);

	_bss_start = .;
	.bss :
	{
		*(.bss);
	}
	. = ALIGN(4);	
	_bss_end = .;
}
