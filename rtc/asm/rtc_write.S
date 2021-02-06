#define RTCBASE 0x10070000
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

	
	ldr r0, =RTCBASE

	ldrb r1, [r0, #RTCCON]
	orr r1, #0x1
	strb r1, [r0, #RTCCON]

	mov r1, #0x17
	strb r1, [r0, #BCDYEAR]
	
	mov r1, #0x6
	strb r1, [r0, #BCDMON]

	mov r1, #0x7
	strb r1, [r0, #BCDDAY]

	mov r1, #0x10
	strb r1, [r0, #BCDHOUR]

	mov r1, #0x30 
	strb r1, [r0, #BCDMIN]

	mov r1, #0x0
	strb r1, [r0, #BCDSEC]

	ldrb r1, [r0, #RTCCON]
	bic r1, #0x1
	strb r1, [r0, #RTCCON]

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}
