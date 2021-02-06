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

	
	ldr r0, =GPM4BASE

	@设置GPM4[0:3]为输出功能
	ldr r1, [r0, #GPM4CON]
	bic r1, r1, #0xff
	bic r1, r1, #0xff00
	orr r1, #0x11
	orr r1, #0x1100
	str r1, [r0, #GPM4CON]

	
loop:
	@将GPM4DAT寄存器的低四位清零输出低电平, on
	ldrb r1, [r0, #GPM4DAT]	
	bic r1, r1, #0xf
	strb r1, [r0, #GPM4DAT]

	bl delay

	@将GPM4DAT寄存器的低四位置都输出高电平, off
	ldrb r1, [r0, #GPM4DAT]	
	orr r1, #0xf
	strb r1, [r0, #GPM4DAT]

	bl delay

	b loop

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}


delay:
	ldr r1, =0x38569527
	
	for:
		sub r1, #1
		cmp r1, #0
	bne for

	mov pc, lr
