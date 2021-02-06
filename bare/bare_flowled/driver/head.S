
.align 2
.text
.global _start

_start:
	ldr sp, =0x80000000
	bl  main

step:
	b step

	
