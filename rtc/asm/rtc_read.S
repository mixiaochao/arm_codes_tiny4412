#define RTCBASE 0x10070000
#define INTP 		0x0030 
#define RTCCON 		0x0040 
#define TICCNT 		0x0044 
#define RTCALM 		0x0050 
#define ALMSEC 		0x0054 
#define ALMMIN 		0x0058 
#define ALMHOUR 	0x005C 
#define ALMDAY 		0x0060 
#define ALMMON 		0x0064 
#define ALMYEAR 	0x0068 
#define BCDSEC 		0x0070 
#define BCDMIN 		0x0074 
#define BCDHOUR 	0x0078 
#define BCDDAYWEEK 	0x007C 
#define BCDDAY 		0x0080 
#define BCDMON 		0x0084 
#define BCDYEAR 	0x0088 
#define CURTICCNT 	0x0090

.align 2
.text
.global _start

_start:
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

hour_loop:
	
	ldr r0, =RTCBASE

	ldrb r1, [r0, #BCDYEAR]
	ldrb r2, [r0, #BCDMON]
	ldrb r3, [r0, #BCDDAY]
	ldrb r4, [r0, #BCDHOUR]
	ldrb r5, [r0, #BCDMIN]
	ldrb r6, [r0, #BCDSEC]

	push {r4-r6}

	ldr r0, =str

	mov lr, pc
	ldr pc, =0x43e11a2c

	pop {r4-r6}


	bl delay

	b hour_loop

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}

delay:

	ldr r3, =0x1592ff00
	for:
		sub r3, #1
		cmp r3, #0
		bne for
	mov pc, lr
print:
	.word 0x43e11a2c
str:
	.string "20%02x-%02x-%02x %02x:%02x:%02x\r"
	.align 2
