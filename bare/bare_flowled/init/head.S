
.align 2
.text
.global _start

_start:
	ldr sp, =0x02027c00

	bl system_clock_init 
	bl mem_ctrl_asm_init_r1

	bl entry

step:
	b step

	
