#define GPX3BASE 0x11000000
#define GPX3CON  0xc60
#define GPX3DAT  0xc64

.align 2
.text
.global _start

_start:
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

	
	@将4个按键对应的GPIO引脚设置成输入功能
	ldr r2, =GPX3BASE

	ldr r3, [r2, #GPX3CON]
	bic r3, r3, #(0xff<<8)
	bic r3, r3, #(0xff<<16)
	str r3, [r2, #GPX3CON]

chek_ifdn:
#if 1
	ldr r2, =GPX3BASE
		
	ldrb r3, [r2, #GPX3DAT]
	lsr r3, r3, #2
	and r3, r3, #0xf

	cmp r3, #0xf
	beq chek_ifdn

	cmp r3, #0xe
	moveq r1, #1

	cmp r3, #0xd
	moveq r1, #2

	cmp r3, #0xb
	moveq r1, #3

	cmp r3, #0x7
	moveq r1, #4
	
	push {r1}

	ldr r0, =str1

	mov lr, pc
	ldr pc, print

chek_ifup:
	ldr r2, =GPX3BASE
		
	ldrb r3, [r2, #GPX3DAT]
	lsr r3, r3, #2
	and r3, r3, #0xf
	
	cmp r3, #0xf
	bne chek_ifup

	
	pop {r1}
	ldr r0, =str2

	mov lr, pc
	ldr pc, print

	b chek_ifdn

#endif

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
str1:
	.asciz "key %d is down!\n"
	.align 2
str2:
	.asciz "key %d is up!\n"
	.align 2
