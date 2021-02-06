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

	@将GPM4DAT寄存器的低四位置都输出高电平, off
	ldrb r1, [r0, #GPM4DAT]	
	orr r1, #0xf
	strb r1, [r0, #GPM4DAT]

	mov r2, #0    @i = 0
	mov r3, #1
flash_loop:
	ldrb r1, [r0, #GPM4DAT]	
	orr r1, #0xf
	bic r1, r1, r3, lsl r2 
	strb r1, [r0, #GPM4DAT]

	add r2, #1
	cmp r2, #3
	movgt r2, #0

	bl delay	

	b flash_loop

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}


delay:
	ldr r1, =0x30000000
	
	for:
		sub r1, #1
		cmp r1, #0
	bne for

	mov pc, lr
