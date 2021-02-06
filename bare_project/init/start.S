
.text
.align 2
.global _start

_start:

	bl system_clock_init
	bl mem_ctrl_asm_init_r1 

	bl app_entry

step:
	b step
