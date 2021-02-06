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

	
	ldr r2, =GPM4BASE

	@设置GPM4[0:3]为输出功能
	ldr r3, [r2, #GPM4CON]
	bic r3, r3, #0xff
	bic r3, r3, #0xff00
	orr r3, #0x11
	orr r3, #0x1100
	str r3, [r2, #GPM4CON]

	@将GPM4DAT寄存器的低四位置都输出高电平, off
	ldrb r3, [r2, #GPM4DAT]	
	orr r3, #0xf
	strb r3, [r2, #GPM4DAT]

	mov r1, #0    @i = 0
	mov r4, #1

flash_loop:
	ldr r2, =GPM4BASE

	ldrb r3, [r2, #GPM4DAT]	
	orr r3, #0xf
	lsl r5, r4, r1
	bic r3, r3, r5
	strb r3, [r2, #GPM4DAT]

	push {r1}
	
	ldr r3, print
	ldr r0, =str
	mov lr, pc
	blx r3

	pop {r1}

	add r1, #1
	cmp r1, #4
	moveq r1, #0

	bl delay	

	b flash_loop

	pop {r4}
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
	.asciz "\rled %d is on!"
