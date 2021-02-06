
.align 2
.text
.global _start

_start:
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

	bl main

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}
