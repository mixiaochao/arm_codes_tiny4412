#define GPM4BASE 0x11000000
#define GPM4CON  0x2e0
#define GPM4DAT  0x2e4

.align 2
.text
.global _start

_start:
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

	mov r1, #0
flash_loop:

	push {r1}
	
	ldr r2, print
	ldr r0, =str
	blx r2

	pop {r1}

	add r1, #1
	cmp r1, #4
	moveq r1, #0

	bl delay	

	b flash_loop

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}


delay:
	ldr r3, =0x30000000
	
	for:
		sub r3, #1
		cmp r3, #0
	bne for

	mov pc, lr

print:
	.word 0x43e11a2c
str:	
	.asciz "led %d is on!\n"
