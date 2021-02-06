
.align 2
.text
.global _start

_start:
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

	bl clr_bss
	bl main

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}


__start_bss:
	.word _bss_start
__end_bss:
	.word _bss_end

clr_bss:
	ldr r0, __start_bss
	ldr r1, __end_bss

	mov r2, #0

	loop:
		cmp r0, r1
		bge end
		str r2, [r0], #4
		b loop
	end:
		
		mov pc, lr	
		
