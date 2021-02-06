
arm:     file format elf32-littlearm


Disassembly of section .text:

50008000 <_start>:
50008000:	ea000005 	b	5000801c <reset>
50008004:	e1a00000 	nop			; (mov r0, r0)
50008008:	e1a00000 	nop			; (mov r0, r0)
5000800c:	e1a00000 	nop			; (mov r0, r0)
50008010:	e1a00000 	nop			; (mov r0, r0)
50008014:	e1a00000 	nop			; (mov r0, r0)
50008018:	ea000003 	b	5000802c <irq>

5000801c <reset>:
5000801c:	e92d5fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
50008020:	eb00000c 	bl	50008058 <_clr_bss>
50008024:	eb000012 	bl	50008074 <main>
50008028:	e8bd9fff 	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, pc}

5000802c <irq>:
5000802c:	e3a0d473 	mov	sp, #1929379840	; 0x73000000
50008030:	e24ee004 	sub	lr, lr, #4
50008034:	e92d5fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
50008038:	e1a0e00f 	mov	lr, pc
5000803c:	e59ff000 	ldr	pc, [pc, #0]	; 50008044 <_do_irq>
50008040:	e8fd9fff 	ldm	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, pc}^

50008044 <_do_irq>:
50008044:	50008300 	.word	0x50008300

50008048 <vectors_end>:
50008048:	50008048 	.word	0x50008048

5000804c <vectors_start>:
5000804c:	50008000 	.word	0x50008000

50008050 <__bss_start>:
50008050:	50008c74 	.word	0x50008c74

50008054 <__bss_end>:
50008054:	50008ef8 	.word	0x50008ef8

50008058 <_clr_bss>:
50008058:	e51f0010 	ldr	r0, [pc, #-16]	; 50008050 <__bss_start>
5000805c:	e51f1010 	ldr	r1, [pc, #-16]	; 50008054 <__bss_end>
50008060:	e3a02000 	mov	r2, #0

50008064 <_millet>:
50008064:	e4802004 	str	r2, [r0], #4
50008068:	e1500001 	cmp	r0, r1
5000806c:	bafffffc 	blt	50008064 <_millet>
50008070:	e1a0f00e 	mov	pc, lr

50008074 <main>:
50008074:	e92d4800 	push	{fp, lr}
50008078:	e28db004 	add	fp, sp, #4
5000807c:	eb000080 	bl	50008284 <build_vectors>
50008080:	eb000205 	bl	5000889c <key_init>
50008084:	eb000234 	bl	5000895c <lcd_init>
50008088:	eb0001dd 	bl	50008804 <image_rotat>
5000808c:	e3a03000 	mov	r3, #0
50008090:	e1a00003 	mov	r0, r3
50008094:	e8bd8800 	pop	{fp, pc}

50008098 <mmu_enable>:
50008098:	e92d4800 	push	{fp, lr}
5000809c:	e28db004 	add	fp, sp, #4
500080a0:	e24dd010 	sub	sp, sp, #16
500080a4:	e50b0010 	str	r0, [fp, #-16]
500080a8:	e51b0010 	ldr	r0, [fp, #-16]
500080ac:	eb00002b 	bl	50008160 <init_ttb>
500080b0:	e59f3028 	ldr	r3, [pc, #40]	; 500080e0 <mmu_enable+0x48>
500080b4:	e50b3008 	str	r3, [fp, #-8]
500080b8:	e51b3008 	ldr	r3, [fp, #-8]
500080bc:	e51b2010 	ldr	r2, [fp, #-16]
500080c0:	e3e00000 	mvn	r0, #0
500080c4:	ee030f10 	mcr	15, 0, r0, cr3, cr0, {0}
500080c8:	ee022f10 	mcr	15, 0, r2, cr2, cr0, {0}
500080cc:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
500080d0:	e1803003 	orr	r3, r0, r3
500080d4:	ee013f10 	mcr	15, 0, r3, cr1, cr0, {0}
500080d8:	e24bd004 	sub	sp, fp, #4
500080dc:	e8bd8800 	pop	{fp, pc}
500080e0:	10002809 	.word	0x10002809

500080e4 <section_map>:
500080e4:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
500080e8:	e28db000 	add	fp, sp, #0
500080ec:	e24dd014 	sub	sp, sp, #20
500080f0:	e50b0008 	str	r0, [fp, #-8]
500080f4:	e50b100c 	str	r1, [fp, #-12]
500080f8:	e50b2010 	str	r2, [fp, #-16]
500080fc:	e50b3014 	str	r3, [fp, #-20]
50008100:	ea00000f 	b	50008144 <section_map+0x60>
50008104:	e51b300c 	ldr	r3, [fp, #-12]
50008108:	e1a03a23 	lsr	r3, r3, #20
5000810c:	e1a03103 	lsl	r3, r3, #2
50008110:	e51b2008 	ldr	r2, [fp, #-8]
50008114:	e0822003 	add	r2, r2, r3
50008118:	e51b3014 	ldr	r3, [fp, #-20]
5000811c:	e1a03a23 	lsr	r3, r3, #20
50008120:	e1a03a03 	lsl	r3, r3, #20
50008124:	e3833002 	orr	r3, r3, #2
50008128:	e5823000 	str	r3, [r2]
5000812c:	e51b300c 	ldr	r3, [fp, #-12]
50008130:	e2833601 	add	r3, r3, #1048576	; 0x100000
50008134:	e50b300c 	str	r3, [fp, #-12]
50008138:	e51b3014 	ldr	r3, [fp, #-20]
5000813c:	e2833601 	add	r3, r3, #1048576	; 0x100000
50008140:	e50b3014 	str	r3, [fp, #-20]
50008144:	e51b200c 	ldr	r2, [fp, #-12]
50008148:	e51b3010 	ldr	r3, [fp, #-16]
5000814c:	e1520003 	cmp	r2, r3
50008150:	3affffeb 	bcc	50008104 <section_map+0x20>
50008154:	e28bd000 	add	sp, fp, #0
50008158:	e8bd0800 	pop	{fp}
5000815c:	e12fff1e 	bx	lr

50008160 <init_ttb>:
50008160:	e92d4800 	push	{fp, lr}
50008164:	e28db004 	add	fp, sp, #4
50008168:	e24dd008 	sub	sp, sp, #8
5000816c:	e50b0008 	str	r0, [fp, #-8]
50008170:	e51b0008 	ldr	r0, [fp, #-8]
50008174:	e3a01000 	mov	r1, #0
50008178:	e3a02201 	mov	r2, #268435456	; 0x10000000
5000817c:	e3a03000 	mov	r3, #0
50008180:	ebffffd7 	bl	500080e4 <section_map>
50008184:	e51b0008 	ldr	r0, [fp, #-8]
50008188:	e3a01201 	mov	r1, #268435456	; 0x10000000
5000818c:	e3a02305 	mov	r2, #335544320	; 0x14000000
50008190:	e3a03201 	mov	r3, #268435456	; 0x10000000
50008194:	ebffffd2 	bl	500080e4 <section_map>
50008198:	e51b0008 	ldr	r0, [fp, #-8]
5000819c:	e3a01101 	mov	r1, #1073741824	; 0x40000000
500081a0:	e3a02102 	mov	r2, #-2147483648	; 0x80000000
500081a4:	e3a03101 	mov	r3, #1073741824	; 0x40000000
500081a8:	ebffffcd 	bl	500080e4 <section_map>
500081ac:	e24bd004 	sub	sp, fp, #4
500081b0:	e8bd8800 	pop	{fp, pc}

500081b4 <memset>:
500081b4:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
500081b8:	e28db000 	add	fp, sp, #0
500081bc:	e24dd01c 	sub	sp, sp, #28
500081c0:	e50b0010 	str	r0, [fp, #-16]
500081c4:	e1a03001 	mov	r3, r1
500081c8:	e50b2018 	str	r2, [fp, #-24]
500081cc:	e54b3011 	strb	r3, [fp, #-17]
500081d0:	e3a03000 	mov	r3, #0
500081d4:	e50b3008 	str	r3, [fp, #-8]
500081d8:	ea000007 	b	500081fc <memset+0x48>
500081dc:	e51b3008 	ldr	r3, [fp, #-8]
500081e0:	e51b2010 	ldr	r2, [fp, #-16]
500081e4:	e0823003 	add	r3, r2, r3
500081e8:	e55b2011 	ldrb	r2, [fp, #-17]
500081ec:	e5c32000 	strb	r2, [r3]
500081f0:	e51b3008 	ldr	r3, [fp, #-8]
500081f4:	e2833001 	add	r3, r3, #1
500081f8:	e50b3008 	str	r3, [fp, #-8]
500081fc:	e51b2008 	ldr	r2, [fp, #-8]
50008200:	e51b3018 	ldr	r3, [fp, #-24]
50008204:	e1520003 	cmp	r2, r3
50008208:	3afffff3 	bcc	500081dc <memset+0x28>
5000820c:	e28bd000 	add	sp, fp, #0
50008210:	e8bd0800 	pop	{fp}
50008214:	e12fff1e 	bx	lr

50008218 <memcpy>:
50008218:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
5000821c:	e28db000 	add	fp, sp, #0
50008220:	e24dd01c 	sub	sp, sp, #28
50008224:	e50b0010 	str	r0, [fp, #-16]
50008228:	e50b1014 	str	r1, [fp, #-20]
5000822c:	e50b2018 	str	r2, [fp, #-24]
50008230:	e3a03000 	mov	r3, #0
50008234:	e50b3008 	str	r3, [fp, #-8]
50008238:	ea00000a 	b	50008268 <memcpy+0x50>
5000823c:	e51b3008 	ldr	r3, [fp, #-8]
50008240:	e51b2010 	ldr	r2, [fp, #-16]
50008244:	e0823003 	add	r3, r2, r3
50008248:	e51b2008 	ldr	r2, [fp, #-8]
5000824c:	e51b1014 	ldr	r1, [fp, #-20]
50008250:	e0812002 	add	r2, r1, r2
50008254:	e5d22000 	ldrb	r2, [r2]
50008258:	e5c32000 	strb	r2, [r3]
5000825c:	e51b3008 	ldr	r3, [fp, #-8]
50008260:	e2833001 	add	r3, r3, #1
50008264:	e50b3008 	str	r3, [fp, #-8]
50008268:	e51b2008 	ldr	r2, [fp, #-8]
5000826c:	e51b3018 	ldr	r3, [fp, #-24]
50008270:	e1520003 	cmp	r2, r3
50008274:	3afffff0 	bcc	5000823c <memcpy+0x24>
50008278:	e28bd000 	add	sp, fp, #0
5000827c:	e8bd0800 	pop	{fp}
50008280:	e12fff1e 	bx	lr

50008284 <build_vectors>:
50008284:	e92d4800 	push	{fp, lr}
50008288:	e28db004 	add	fp, sp, #4
5000828c:	e24dd008 	sub	sp, sp, #8
50008290:	e3a03473 	mov	r3, #1929379840	; 0x73000000
50008294:	e50b3008 	str	r3, [fp, #-8]
50008298:	e51b0008 	ldr	r0, [fp, #-8]
5000829c:	ebffffaf 	bl	50008160 <init_ttb>
500082a0:	e51b3008 	ldr	r3, [fp, #-8]
500082a4:	e2833dff 	add	r3, r3, #16320	; 0x3fc0
500082a8:	e283303c 	add	r3, r3, #60	; 0x3c
500082ac:	e3a02227 	mov	r2, #1879048194	; 0x70000002
500082b0:	e5832000 	str	r2, [r3]
500082b4:	e51b0008 	ldr	r0, [fp, #-8]
500082b8:	ebffff76 	bl	50008098 <mmu_enable>
500082bc:	e59f3030 	ldr	r3, [pc, #48]	; 500082f4 <build_vectors+0x70>
500082c0:	e5933000 	ldr	r3, [r3]
500082c4:	e1a02003 	mov	r2, r3
500082c8:	e59f3028 	ldr	r3, [pc, #40]	; 500082f8 <build_vectors+0x74>
500082cc:	e5931000 	ldr	r1, [r3]
500082d0:	e59f301c 	ldr	r3, [pc, #28]	; 500082f4 <build_vectors+0x70>
500082d4:	e5933000 	ldr	r3, [r3]
500082d8:	e0633001 	rsb	r3, r3, r1
500082dc:	e59f0018 	ldr	r0, [pc, #24]	; 500082fc <build_vectors+0x78>
500082e0:	e1a01002 	mov	r1, r2
500082e4:	e1a02003 	mov	r2, r3
500082e8:	ebffffca 	bl	50008218 <memcpy>
500082ec:	e24bd004 	sub	sp, fp, #4
500082f0:	e8bd8800 	pop	{fp, pc}
500082f4:	5000804c 	.word	0x5000804c
500082f8:	50008048 	.word	0x50008048
500082fc:	ffff0000 	.word	0xffff0000

50008300 <do_irq>:
50008300:	e92d4800 	push	{fp, lr}
50008304:	e28db004 	add	fp, sp, #4
50008308:	e24dd008 	sub	sp, sp, #8
5000830c:	e3a03000 	mov	r3, #0
50008310:	e50b3008 	str	r3, [fp, #-8]
50008314:	e59f3040 	ldr	r3, [pc, #64]	; 5000835c <do_irq+0x5c>
50008318:	e5933000 	ldr	r3, [r3]
5000831c:	e50b300c 	str	r3, [fp, #-12]
50008320:	e51b300c 	ldr	r3, [fp, #-12]
50008324:	e1a03b03 	lsl	r3, r3, #22
50008328:	e1a03b23 	lsr	r3, r3, #22
5000832c:	e59f202c 	ldr	r2, [pc, #44]	; 50008360 <do_irq+0x60>
50008330:	e7923103 	ldr	r3, [r2, r3, lsl #2]
50008334:	e50b3008 	str	r3, [fp, #-8]
50008338:	e51b3008 	ldr	r3, [fp, #-8]
5000833c:	e12fff33 	blx	r3
50008340:	e59f201c 	ldr	r2, [pc, #28]	; 50008364 <do_irq+0x64>
50008344:	e51b300c 	ldr	r3, [fp, #-12]
50008348:	e1a03b03 	lsl	r3, r3, #22
5000834c:	e1a03b23 	lsr	r3, r3, #22
50008350:	e5823000 	str	r3, [r2]
50008354:	e24bd004 	sub	sp, fp, #4
50008358:	e8bd8800 	pop	{fp, pc}
5000835c:	1048000c 	.word	0x1048000c
50008360:	50008c74 	.word	0x50008c74
50008364:	10480010 	.word	0x10480010

50008368 <irq_request_cpu0_>:
50008368:	e92d4800 	push	{fp, lr}
5000836c:	e28db004 	add	fp, sp, #4
50008370:	e24dd010 	sub	sp, sp, #16
50008374:	e50b0008 	str	r0, [fp, #-8]
50008378:	e50b100c 	str	r1, [fp, #-12]
5000837c:	e50b2010 	str	r2, [fp, #-16]
50008380:	e59f3274 	ldr	r3, [pc, #628]	; 500085fc <irq_request_cpu0_+0x294>
50008384:	e5933000 	ldr	r3, [r3]
50008388:	e3530000 	cmp	r3, #0
5000838c:	1a00000b 	bne	500083c0 <irq_request_cpu0_+0x58>
50008390:	e59f3268 	ldr	r3, [pc, #616]	; 50008600 <irq_request_cpu0_+0x298>
50008394:	e3a02001 	mov	r2, #1
50008398:	e5832000 	str	r2, [r3]
5000839c:	e59f3260 	ldr	r3, [pc, #608]	; 50008604 <irq_request_cpu0_+0x29c>
500083a0:	e3a020ff 	mov	r2, #255	; 0xff
500083a4:	e5832000 	str	r2, [r3]
500083a8:	e59f3258 	ldr	r3, [pc, #600]	; 50008608 <irq_request_cpu0_+0x2a0>
500083ac:	e3a02001 	mov	r2, #1
500083b0:	e5832000 	str	r2, [r3]
500083b4:	e59f3240 	ldr	r3, [pc, #576]	; 500085fc <irq_request_cpu0_+0x294>
500083b8:	e3a02001 	mov	r2, #1
500083bc:	e5832000 	str	r2, [r3]
500083c0:	e51b3008 	ldr	r3, [fp, #-8]
500083c4:	e3530000 	cmp	r3, #0
500083c8:	ba000086 	blt	500085e8 <irq_request_cpu0_+0x280>
500083cc:	e51b3008 	ldr	r3, [fp, #-8]
500083d0:	e353009f 	cmp	r3, #159	; 0x9f
500083d4:	ca000083 	bgt	500085e8 <irq_request_cpu0_+0x280>
500083d8:	e51b3008 	ldr	r3, [fp, #-8]
500083dc:	e2832003 	add	r2, r3, #3
500083e0:	e3530000 	cmp	r3, #0
500083e4:	b1a03002 	movlt	r3, r2
500083e8:	e1a03143 	asr	r3, r3, #2
500083ec:	e1a02003 	mov	r2, r3
500083f0:	e1a03002 	mov	r3, r2
500083f4:	e1a01103 	lsl	r1, r3, #2
500083f8:	e59f320c 	ldr	r3, [pc, #524]	; 5000860c <irq_request_cpu0_+0x2a4>
500083fc:	e0813003 	add	r3, r1, r3
50008400:	e1a01102 	lsl	r1, r2, #2
50008404:	e59f2200 	ldr	r2, [pc, #512]	; 5000860c <irq_request_cpu0_+0x2a4>
50008408:	e0812002 	add	r2, r1, r2
5000840c:	e5920000 	ldr	r0, [r2]
50008410:	e51b1008 	ldr	r1, [fp, #-8]
50008414:	e1a02fc1 	asr	r2, r1, #31
50008418:	e1a02f22 	lsr	r2, r2, #30
5000841c:	e0811002 	add	r1, r1, r2
50008420:	e2011003 	and	r1, r1, #3
50008424:	e0622001 	rsb	r2, r2, r1
50008428:	e1a02182 	lsl	r2, r2, #3
5000842c:	e3a010ff 	mov	r1, #255	; 0xff
50008430:	e1a02211 	lsl	r2, r1, r2
50008434:	e1e02002 	mvn	r2, r2
50008438:	e0002002 	and	r2, r0, r2
5000843c:	e5832000 	str	r2, [r3]
50008440:	e51b3008 	ldr	r3, [fp, #-8]
50008444:	e2832003 	add	r2, r3, #3
50008448:	e3530000 	cmp	r3, #0
5000844c:	b1a03002 	movlt	r3, r2
50008450:	e1a03143 	asr	r3, r3, #2
50008454:	e1a02003 	mov	r2, r3
50008458:	e1a03002 	mov	r3, r2
5000845c:	e1a01103 	lsl	r1, r3, #2
50008460:	e59f31a4 	ldr	r3, [pc, #420]	; 5000860c <irq_request_cpu0_+0x2a4>
50008464:	e0813003 	add	r3, r1, r3
50008468:	e1a01102 	lsl	r1, r2, #2
5000846c:	e59f2198 	ldr	r2, [pc, #408]	; 5000860c <irq_request_cpu0_+0x2a4>
50008470:	e0812002 	add	r2, r1, r2
50008474:	e5920000 	ldr	r0, [r2]
50008478:	e51b1008 	ldr	r1, [fp, #-8]
5000847c:	e1a02fc1 	asr	r2, r1, #31
50008480:	e1a02f22 	lsr	r2, r2, #30
50008484:	e0811002 	add	r1, r1, r2
50008488:	e2011003 	and	r1, r1, #3
5000848c:	e0622001 	rsb	r2, r2, r1
50008490:	e1a02182 	lsl	r2, r2, #3
50008494:	e51b1010 	ldr	r1, [fp, #-16]
50008498:	e1a02211 	lsl	r2, r1, r2
5000849c:	e1802002 	orr	r2, r0, r2
500084a0:	e5832000 	str	r2, [r3]
500084a4:	e51b3008 	ldr	r3, [fp, #-8]
500084a8:	e2832003 	add	r2, r3, #3
500084ac:	e3530000 	cmp	r3, #0
500084b0:	b1a03002 	movlt	r3, r2
500084b4:	e1a03143 	asr	r3, r3, #2
500084b8:	e1a02003 	mov	r2, r3
500084bc:	e1a03002 	mov	r3, r2
500084c0:	e1a01103 	lsl	r1, r3, #2
500084c4:	e59f3144 	ldr	r3, [pc, #324]	; 50008610 <irq_request_cpu0_+0x2a8>
500084c8:	e0813003 	add	r3, r1, r3
500084cc:	e1a01102 	lsl	r1, r2, #2
500084d0:	e59f2138 	ldr	r2, [pc, #312]	; 50008610 <irq_request_cpu0_+0x2a8>
500084d4:	e0812002 	add	r2, r1, r2
500084d8:	e5920000 	ldr	r0, [r2]
500084dc:	e51b1008 	ldr	r1, [fp, #-8]
500084e0:	e1a02fc1 	asr	r2, r1, #31
500084e4:	e1a02f22 	lsr	r2, r2, #30
500084e8:	e0811002 	add	r1, r1, r2
500084ec:	e2011003 	and	r1, r1, #3
500084f0:	e0622001 	rsb	r2, r2, r1
500084f4:	e1a02182 	lsl	r2, r2, #3
500084f8:	e3a010ff 	mov	r1, #255	; 0xff
500084fc:	e1a02211 	lsl	r2, r1, r2
50008500:	e1e02002 	mvn	r2, r2
50008504:	e0002002 	and	r2, r0, r2
50008508:	e5832000 	str	r2, [r3]
5000850c:	e51b3008 	ldr	r3, [fp, #-8]
50008510:	e2832003 	add	r2, r3, #3
50008514:	e3530000 	cmp	r3, #0
50008518:	b1a03002 	movlt	r3, r2
5000851c:	e1a03143 	asr	r3, r3, #2
50008520:	e1a02003 	mov	r2, r3
50008524:	e1a03002 	mov	r3, r2
50008528:	e1a01103 	lsl	r1, r3, #2
5000852c:	e59f30dc 	ldr	r3, [pc, #220]	; 50008610 <irq_request_cpu0_+0x2a8>
50008530:	e0813003 	add	r3, r1, r3
50008534:	e1a01102 	lsl	r1, r2, #2
50008538:	e59f20d0 	ldr	r2, [pc, #208]	; 50008610 <irq_request_cpu0_+0x2a8>
5000853c:	e0812002 	add	r2, r1, r2
50008540:	e5920000 	ldr	r0, [r2]
50008544:	e51b1008 	ldr	r1, [fp, #-8]
50008548:	e1a02fc1 	asr	r2, r1, #31
5000854c:	e1a02f22 	lsr	r2, r2, #30
50008550:	e0811002 	add	r1, r1, r2
50008554:	e2011003 	and	r1, r1, #3
50008558:	e0622001 	rsb	r2, r2, r1
5000855c:	e1a02182 	lsl	r2, r2, #3
50008560:	e3a01001 	mov	r1, #1
50008564:	e1a02211 	lsl	r2, r1, r2
50008568:	e1802002 	orr	r2, r0, r2
5000856c:	e5832000 	str	r2, [r3]
50008570:	e51b3008 	ldr	r3, [fp, #-8]
50008574:	e283201f 	add	r2, r3, #31
50008578:	e3530000 	cmp	r3, #0
5000857c:	b1a03002 	movlt	r3, r2
50008580:	e1a032c3 	asr	r3, r3, #5
50008584:	e1a02003 	mov	r2, r3
50008588:	e1a03002 	mov	r3, r2
5000858c:	e1a01103 	lsl	r1, r3, #2
50008590:	e59f307c 	ldr	r3, [pc, #124]	; 50008614 <irq_request_cpu0_+0x2ac>
50008594:	e0813003 	add	r3, r1, r3
50008598:	e1a01102 	lsl	r1, r2, #2
5000859c:	e59f2070 	ldr	r2, [pc, #112]	; 50008614 <irq_request_cpu0_+0x2ac>
500085a0:	e0812002 	add	r2, r1, r2
500085a4:	e5920000 	ldr	r0, [r2]
500085a8:	e51b1008 	ldr	r1, [fp, #-8]
500085ac:	e1a02fc1 	asr	r2, r1, #31
500085b0:	e1a02da2 	lsr	r2, r2, #27
500085b4:	e0811002 	add	r1, r1, r2
500085b8:	e201101f 	and	r1, r1, #31
500085bc:	e0622001 	rsb	r2, r2, r1
500085c0:	e3a01001 	mov	r1, #1
500085c4:	e1a02211 	lsl	r2, r1, r2
500085c8:	e1802002 	orr	r2, r0, r2
500085cc:	e5832000 	str	r2, [r3]
500085d0:	e59f3040 	ldr	r3, [pc, #64]	; 50008618 <irq_request_cpu0_+0x2b0>
500085d4:	e51b2008 	ldr	r2, [fp, #-8]
500085d8:	e51b100c 	ldr	r1, [fp, #-12]
500085dc:	e7831102 	str	r1, [r3, r2, lsl #2]
500085e0:	f1080080 	cpsie	i
500085e4:	ea000002 	b	500085f4 <irq_request_cpu0_+0x28c>
500085e8:	e59f302c 	ldr	r3, [pc, #44]	; 5000861c <irq_request_cpu0_+0x2b4>
500085ec:	e59f002c 	ldr	r0, [pc, #44]	; 50008620 <irq_request_cpu0_+0x2b8>
500085f0:	e12fff33 	blx	r3
500085f4:	e24bd004 	sub	sp, fp, #4
500085f8:	e8bd8800 	pop	{fp, pc}
500085fc:	50008ef4 	.word	0x50008ef4
50008600:	10480000 	.word	0x10480000
50008604:	10480004 	.word	0x10480004
50008608:	10490000 	.word	0x10490000
5000860c:	10490400 	.word	0x10490400
50008610:	10490800 	.word	0x10490800
50008614:	10490100 	.word	0x10490100
50008618:	50008c74 	.word	0x50008c74
5000861c:	43e11a2c 	.word	0x43e11a2c
50008620:	50008c0c 	.word	0x50008c0c

50008624 <do_key>:
50008624:	e92d4800 	push	{fp, lr}
50008628:	e28db004 	add	fp, sp, #4
5000862c:	e59f3110 	ldr	r3, [pc, #272]	; 50008744 <do_key+0x120>
50008630:	e5933000 	ldr	r3, [r3]
50008634:	e1a03123 	lsr	r3, r3, #2
50008638:	e203300f 	and	r3, r3, #15
5000863c:	e2433001 	sub	r3, r3, #1
50008640:	e3530007 	cmp	r3, #7
50008644:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
50008648:	ea000037 	b	5000872c <do_key+0x108>
5000864c:	5000866c 	.word	0x5000866c
50008650:	500086bc 	.word	0x500086bc
50008654:	5000872c 	.word	0x5000872c
50008658:	5000870c 	.word	0x5000870c
5000865c:	5000872c 	.word	0x5000872c
50008660:	5000872c 	.word	0x5000872c
50008664:	5000872c 	.word	0x5000872c
50008668:	5000871c 	.word	0x5000871c
5000866c:	e59f30d4 	ldr	r3, [pc, #212]	; 50008748 <do_key+0x124>
50008670:	e59f00d4 	ldr	r0, [pc, #212]	; 5000874c <do_key+0x128>
50008674:	e12fff33 	blx	r3
50008678:	e59f30d0 	ldr	r3, [pc, #208]	; 50008750 <do_key+0x12c>
5000867c:	e5933000 	ldr	r3, [r3]
50008680:	e2033003 	and	r3, r3, #3
50008684:	e3530000 	cmp	r3, #0
50008688:	1afffffa 	bne	50008678 <do_key+0x54>
5000868c:	eb000036 	bl	5000876c <flip_ver>
50008690:	eb000050 	bl	500087d8 <start_rotat>
50008694:	e59f30b8 	ldr	r3, [pc, #184]	; 50008754 <do_key+0x130>
50008698:	e3a02465 	mov	r2, #1694498816	; 0x65000000
5000869c:	e5832000 	str	r2, [r3]
500086a0:	e59f30b0 	ldr	r3, [pc, #176]	; 50008758 <do_key+0x134>
500086a4:	e59f20b0 	ldr	r2, [pc, #176]	; 5000875c <do_key+0x138>
500086a8:	e5922000 	ldr	r2, [r2]
500086ac:	e2822565 	add	r2, r2, #423624704	; 0x19400000
500086b0:	e1a02102 	lsl	r2, r2, #2
500086b4:	e5832000 	str	r2, [r3]
500086b8:	ea00001c 	b	50008730 <do_key+0x10c>
500086bc:	e59f3084 	ldr	r3, [pc, #132]	; 50008748 <do_key+0x124>
500086c0:	e59f0098 	ldr	r0, [pc, #152]	; 50008760 <do_key+0x13c>
500086c4:	e12fff33 	blx	r3
500086c8:	e59f3080 	ldr	r3, [pc, #128]	; 50008750 <do_key+0x12c>
500086cc:	e5933000 	ldr	r3, [r3]
500086d0:	e2033003 	and	r3, r3, #3
500086d4:	e3530000 	cmp	r3, #0
500086d8:	1afffffa 	bne	500086c8 <do_key+0xa4>
500086dc:	eb000032 	bl	500087ac <flip_hor>
500086e0:	eb00003c 	bl	500087d8 <start_rotat>
500086e4:	e59f3068 	ldr	r3, [pc, #104]	; 50008754 <do_key+0x130>
500086e8:	e3a02465 	mov	r2, #1694498816	; 0x65000000
500086ec:	e5832000 	str	r2, [r3]
500086f0:	e59f3060 	ldr	r3, [pc, #96]	; 50008758 <do_key+0x134>
500086f4:	e59f2060 	ldr	r2, [pc, #96]	; 5000875c <do_key+0x138>
500086f8:	e5922000 	ldr	r2, [r2]
500086fc:	e2822565 	add	r2, r2, #423624704	; 0x19400000
50008700:	e1a02102 	lsl	r2, r2, #2
50008704:	e5832000 	str	r2, [r3]
50008708:	ea000008 	b	50008730 <do_key+0x10c>
5000870c:	e59f3034 	ldr	r3, [pc, #52]	; 50008748 <do_key+0x124>
50008710:	e59f004c 	ldr	r0, [pc, #76]	; 50008764 <do_key+0x140>
50008714:	e12fff33 	blx	r3
50008718:	ea000004 	b	50008730 <do_key+0x10c>
5000871c:	e59f3024 	ldr	r3, [pc, #36]	; 50008748 <do_key+0x124>
50008720:	e59f0040 	ldr	r0, [pc, #64]	; 50008768 <do_key+0x144>
50008724:	e12fff33 	blx	r3
50008728:	ea000000 	b	50008730 <do_key+0x10c>
5000872c:	e1a00000 	nop			; (mov r0, r0)
50008730:	e59f300c 	ldr	r3, [pc, #12]	; 50008744 <do_key+0x120>
50008734:	e59f2008 	ldr	r2, [pc, #8]	; 50008744 <do_key+0x120>
50008738:	e5922000 	ldr	r2, [r2]
5000873c:	e5832000 	str	r2, [r3]
50008740:	e8bd8800 	pop	{fp, pc}
50008744:	11000f4c 	.word	0x11000f4c
50008748:	43e11a2c 	.word	0x43e11a2c
5000874c:	50008c24 	.word	0x50008c24
50008750:	12810020 	.word	0x12810020
50008754:	11c000a0 	.word	0x11c000a0
50008758:	11c000d0 	.word	0x11c000d0
5000875c:	11c00048 	.word	0x11c00048
50008760:	50008c38 	.word	0x50008c38
50008764:	50008c4c 	.word	0x50008c4c
50008768:	50008c60 	.word	0x50008c60

5000876c <flip_ver>:
5000876c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
50008770:	e28db000 	add	fp, sp, #0
50008774:	e59f302c 	ldr	r3, [pc, #44]	; 500087a8 <flip_ver+0x3c>
50008778:	e59f2028 	ldr	r2, [pc, #40]	; 500087a8 <flip_ver+0x3c>
5000877c:	e5922000 	ldr	r2, [r2]
50008780:	e3c220c0 	bic	r2, r2, #192	; 0xc0
50008784:	e5832000 	str	r2, [r3]
50008788:	e59f3018 	ldr	r3, [pc, #24]	; 500087a8 <flip_ver+0x3c>
5000878c:	e59f2014 	ldr	r2, [pc, #20]	; 500087a8 <flip_ver+0x3c>
50008790:	e5922000 	ldr	r2, [r2]
50008794:	e3822080 	orr	r2, r2, #128	; 0x80
50008798:	e5832000 	str	r2, [r3]
5000879c:	e28bd000 	add	sp, fp, #0
500087a0:	e8bd0800 	pop	{fp}
500087a4:	e12fff1e 	bx	lr
500087a8:	12810010 	.word	0x12810010

500087ac <flip_hor>:
500087ac:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
500087b0:	e28db000 	add	fp, sp, #0
500087b4:	e59f3018 	ldr	r3, [pc, #24]	; 500087d4 <flip_hor+0x28>
500087b8:	e59f2014 	ldr	r2, [pc, #20]	; 500087d4 <flip_hor+0x28>
500087bc:	e5922000 	ldr	r2, [r2]
500087c0:	e38220c0 	orr	r2, r2, #192	; 0xc0
500087c4:	e5832000 	str	r2, [r3]
500087c8:	e28bd000 	add	sp, fp, #0
500087cc:	e8bd0800 	pop	{fp}
500087d0:	e12fff1e 	bx	lr
500087d4:	12810010 	.word	0x12810010

500087d8 <start_rotat>:
500087d8:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
500087dc:	e28db000 	add	fp, sp, #0
500087e0:	e59f3018 	ldr	r3, [pc, #24]	; 50008800 <start_rotat+0x28>
500087e4:	e59f2014 	ldr	r2, [pc, #20]	; 50008800 <start_rotat+0x28>
500087e8:	e5922000 	ldr	r2, [r2]
500087ec:	e3822001 	orr	r2, r2, #1
500087f0:	e5832000 	str	r2, [r3]
500087f4:	e28bd000 	add	sp, fp, #0
500087f8:	e8bd0800 	pop	{fp}
500087fc:	e12fff1e 	bx	lr
50008800:	12810010 	.word	0x12810010

50008804 <image_rotat>:
50008804:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
50008808:	e28db000 	add	fp, sp, #0
5000880c:	e59f3064 	ldr	r3, [pc, #100]	; 50008878 <image_rotat+0x74>
50008810:	e3a02c06 	mov	r2, #1536	; 0x600
50008814:	e5832000 	str	r2, [r3]
50008818:	e59f305c 	ldr	r3, [pc, #92]	; 5000887c <image_rotat+0x78>
5000881c:	e3a02206 	mov	r2, #1610612736	; 0x60000000
50008820:	e5832000 	str	r2, [r3]
50008824:	e59f3054 	ldr	r3, [pc, #84]	; 50008880 <image_rotat+0x7c>
50008828:	e3a02465 	mov	r2, #1694498816	; 0x65000000
5000882c:	e5832000 	str	r2, [r3]
50008830:	e59f304c 	ldr	r3, [pc, #76]	; 50008884 <image_rotat+0x80>
50008834:	e59f204c 	ldr	r2, [pc, #76]	; 50008888 <image_rotat+0x84>
50008838:	e5832000 	str	r2, [r3]
5000883c:	e59f3048 	ldr	r3, [pc, #72]	; 5000888c <image_rotat+0x88>
50008840:	e3a02000 	mov	r2, #0
50008844:	e5832000 	str	r2, [r3]
50008848:	e59f3040 	ldr	r3, [pc, #64]	; 50008890 <image_rotat+0x8c>
5000884c:	e59f2034 	ldr	r2, [pc, #52]	; 50008888 <image_rotat+0x84>
50008850:	e5832000 	str	r2, [r3]
50008854:	e59f3038 	ldr	r3, [pc, #56]	; 50008894 <image_rotat+0x90>
50008858:	e59f2028 	ldr	r2, [pc, #40]	; 50008888 <image_rotat+0x84>
5000885c:	e5832000 	str	r2, [r3]
50008860:	e59f3030 	ldr	r3, [pc, #48]	; 50008898 <image_rotat+0x94>
50008864:	e3a02000 	mov	r2, #0
50008868:	e5832000 	str	r2, [r3]
5000886c:	e28bd000 	add	sp, fp, #0
50008870:	e8bd0800 	pop	{fp}
50008874:	e12fff1e 	bx	lr
50008878:	12810010 	.word	0x12810010
5000887c:	12810030 	.word	0x12810030
50008880:	12810050 	.word	0x12810050
50008884:	1281003c 	.word	0x1281003c
50008888:	01e00320 	.word	0x01e00320
5000888c:	12810040 	.word	0x12810040
50008890:	12810044 	.word	0x12810044
50008894:	1281005c 	.word	0x1281005c
50008898:	12810060 	.word	0x12810060

5000889c <key_init>:
5000889c:	e92d4800 	push	{fp, lr}
500088a0:	e28db004 	add	fp, sp, #4
500088a4:	e59f2098 	ldr	r2, [pc, #152]	; 50008944 <key_init+0xa8>
500088a8:	e59f3094 	ldr	r3, [pc, #148]	; 50008944 <key_init+0xa8>
500088ac:	e5933000 	ldr	r3, [r3]
500088b0:	e38338ff 	orr	r3, r3, #16711680	; 0xff0000
500088b4:	e3833cff 	orr	r3, r3, #65280	; 0xff00
500088b8:	e5823000 	str	r3, [r2]
500088bc:	e59f2084 	ldr	r2, [pc, #132]	; 50008948 <key_init+0xac>
500088c0:	e59f3080 	ldr	r3, [pc, #128]	; 50008948 <key_init+0xac>
500088c4:	e5933000 	ldr	r3, [r3]
500088c8:	e3c338ff 	bic	r3, r3, #16711680	; 0xff0000
500088cc:	e3c33cff 	bic	r3, r3, #65280	; 0xff00
500088d0:	e5823000 	str	r3, [r2]
500088d4:	e59f206c 	ldr	r2, [pc, #108]	; 50008948 <key_init+0xac>
500088d8:	e59f3068 	ldr	r3, [pc, #104]	; 50008948 <key_init+0xac>
500088dc:	e5933000 	ldr	r3, [r3]
500088e0:	e3833822 	orr	r3, r3, #2228224	; 0x220000
500088e4:	e3833c22 	orr	r3, r3, #8704	; 0x2200
500088e8:	e5823000 	str	r3, [r2]
500088ec:	e59f3058 	ldr	r3, [pc, #88]	; 5000894c <key_init+0xb0>
500088f0:	e59f2054 	ldr	r2, [pc, #84]	; 5000894c <key_init+0xb0>
500088f4:	e5922000 	ldr	r2, [r2]
500088f8:	e3c2203c 	bic	r2, r2, #60	; 0x3c
500088fc:	e5832000 	str	r2, [r3]
50008900:	e59f2048 	ldr	r2, [pc, #72]	; 50008950 <key_init+0xb4>
50008904:	e59f3044 	ldr	r3, [pc, #68]	; 50008950 <key_init+0xb4>
50008908:	e5933000 	ldr	r3, [r3]
5000890c:	e1e03803 	mvn	r3, r3, lsl #16
50008910:	e1e03823 	mvn	r3, r3, lsr #16
50008914:	e5823000 	str	r3, [r2]
50008918:	e59f2034 	ldr	r2, [pc, #52]	; 50008954 <key_init+0xb8>
5000891c:	e59f3030 	ldr	r3, [pc, #48]	; 50008954 <key_init+0xb8>
50008920:	e5933000 	ldr	r3, [r3]
50008924:	e1e03823 	mvn	r3, r3, lsr #16
50008928:	e1e03803 	mvn	r3, r3, lsl #16
5000892c:	e5823000 	str	r3, [r2]
50008930:	e3a00040 	mov	r0, #64	; 0x40
50008934:	e59f101c 	ldr	r1, [pc, #28]	; 50008958 <key_init+0xbc>
50008938:	e3a02000 	mov	r2, #0
5000893c:	ebfffe89 	bl	50008368 <irq_request_cpu0_>
50008940:	e8bd8800 	pop	{fp, pc}
50008944:	11000c60 	.word	0x11000c60
50008948:	11000e0c 	.word	0x11000e0c
5000894c:	11000f0c 	.word	0x11000f0c
50008950:	11000e98 	.word	0x11000e98
50008954:	11000e9c 	.word	0x11000e9c
50008958:	50008624 	.word	0x50008624

5000895c <lcd_init>:
5000895c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
50008960:	e28db000 	add	fp, sp, #0
50008964:	e59f31c4 	ldr	r3, [pc, #452]	; 50008b30 <lcd_init+0x1d4>
50008968:	e59f21c4 	ldr	r2, [pc, #452]	; 50008b34 <lcd_init+0x1d8>
5000896c:	e5832000 	str	r2, [r3]
50008970:	e59f31c0 	ldr	r3, [pc, #448]	; 50008b38 <lcd_init+0x1dc>
50008974:	e59f21b8 	ldr	r2, [pc, #440]	; 50008b34 <lcd_init+0x1d8>
50008978:	e5832000 	str	r2, [r3]
5000897c:	e59f31b8 	ldr	r3, [pc, #440]	; 50008b3c <lcd_init+0x1e0>
50008980:	e59f21ac 	ldr	r2, [pc, #428]	; 50008b34 <lcd_init+0x1d8>
50008984:	e5832000 	str	r2, [r3]
50008988:	e59f21b0 	ldr	r2, [pc, #432]	; 50008b40 <lcd_init+0x1e4>
5000898c:	e59f31ac 	ldr	r3, [pc, #428]	; 50008b40 <lcd_init+0x1e4>
50008990:	e5933000 	ldr	r3, [r3]
50008994:	e1a03823 	lsr	r3, r3, #16
50008998:	e1a03803 	lsl	r3, r3, #16
5000899c:	e5823000 	str	r3, [r2]
500089a0:	e59f2198 	ldr	r2, [pc, #408]	; 50008b40 <lcd_init+0x1e4>
500089a4:	e59f3194 	ldr	r3, [pc, #404]	; 50008b40 <lcd_init+0x1e4>
500089a8:	e5933000 	ldr	r3, [r3]
500089ac:	e3833c22 	orr	r3, r3, #8704	; 0x2200
500089b0:	e3833022 	orr	r3, r3, #34	; 0x22
500089b4:	e5823000 	str	r3, [r2]
500089b8:	e59f3184 	ldr	r3, [pc, #388]	; 50008b44 <lcd_init+0x1e8>
500089bc:	e59f2180 	ldr	r2, [pc, #384]	; 50008b44 <lcd_init+0x1e8>
500089c0:	e5922000 	ldr	r2, [r2]
500089c4:	e3c2200f 	bic	r2, r2, #15
500089c8:	e5832000 	str	r2, [r3]
500089cc:	e59f3174 	ldr	r3, [pc, #372]	; 50008b48 <lcd_init+0x1ec>
500089d0:	e59f2170 	ldr	r2, [pc, #368]	; 50008b48 <lcd_init+0x1ec>
500089d4:	e5922000 	ldr	r2, [r2]
500089d8:	e3c2200f 	bic	r2, r2, #15
500089dc:	e5832000 	str	r2, [r3]
500089e0:	e59f3160 	ldr	r3, [pc, #352]	; 50008b48 <lcd_init+0x1ec>
500089e4:	e59f215c 	ldr	r2, [pc, #348]	; 50008b48 <lcd_init+0x1ec>
500089e8:	e5922000 	ldr	r2, [r2]
500089ec:	e3822006 	orr	r2, r2, #6
500089f0:	e5832000 	str	r2, [r3]
500089f4:	e59f3150 	ldr	r3, [pc, #336]	; 50008b4c <lcd_init+0x1f0>
500089f8:	e59f214c 	ldr	r2, [pc, #332]	; 50008b4c <lcd_init+0x1f0>
500089fc:	e5922000 	ldr	r2, [r2]
50008a00:	e3822002 	orr	r2, r2, #2
50008a04:	e5832000 	str	r2, [r3]
50008a08:	e3a03547 	mov	r3, #297795584	; 0x11c00000
50008a0c:	e3a02d17 	mov	r2, #1472	; 0x5c0
50008a10:	e5832000 	str	r2, [r3]
50008a14:	e59f3134 	ldr	r3, [pc, #308]	; 50008b50 <lcd_init+0x1f4>
50008a18:	e3a02e2e 	mov	r2, #736	; 0x2e0
50008a1c:	e5832000 	str	r2, [r3]
50008a20:	e59f312c 	ldr	r3, [pc, #300]	; 50008b54 <lcd_init+0x1f8>
50008a24:	e59f212c 	ldr	r2, [pc, #300]	; 50008b58 <lcd_init+0x1fc>
50008a28:	e5832000 	str	r2, [r3]
50008a2c:	e59f3128 	ldr	r3, [pc, #296]	; 50008b5c <lcd_init+0x200>
50008a30:	e59f2128 	ldr	r2, [pc, #296]	; 50008b60 <lcd_init+0x204>
50008a34:	e5832000 	str	r2, [r3]
50008a38:	e59f3124 	ldr	r3, [pc, #292]	; 50008b64 <lcd_init+0x208>
50008a3c:	e59f2124 	ldr	r2, [pc, #292]	; 50008b68 <lcd_init+0x20c>
50008a40:	e5832000 	str	r2, [r3]
50008a44:	e59f3120 	ldr	r3, [pc, #288]	; 50008b6c <lcd_init+0x210>
50008a48:	e59f2120 	ldr	r2, [pc, #288]	; 50008b70 <lcd_init+0x214>
50008a4c:	e5832000 	str	r2, [r3]
50008a50:	e59f311c 	ldr	r3, [pc, #284]	; 50008b74 <lcd_init+0x218>
50008a54:	e59f211c 	ldr	r2, [pc, #284]	; 50008b78 <lcd_init+0x21c>
50008a58:	e5832000 	str	r2, [r3]
50008a5c:	e59f3118 	ldr	r3, [pc, #280]	; 50008b7c <lcd_init+0x220>
50008a60:	e3a02000 	mov	r2, #0
50008a64:	e5832000 	str	r2, [r3]
50008a68:	e59f3110 	ldr	r3, [pc, #272]	; 50008b80 <lcd_init+0x224>
50008a6c:	e59f2110 	ldr	r2, [pc, #272]	; 50008b84 <lcd_init+0x228>
50008a70:	e5832000 	str	r2, [r3]
50008a74:	e59f310c 	ldr	r3, [pc, #268]	; 50008b88 <lcd_init+0x22c>
50008a78:	e3a02206 	mov	r2, #1610612736	; 0x60000000
50008a7c:	e5832000 	str	r2, [r3]
50008a80:	e59f3104 	ldr	r3, [pc, #260]	; 50008b8c <lcd_init+0x230>
50008a84:	e59f20e8 	ldr	r2, [pc, #232]	; 50008b74 <lcd_init+0x218>
50008a88:	e5922000 	ldr	r2, [r2]
50008a8c:	e2822306 	add	r2, r2, #402653184	; 0x18000000
50008a90:	e1a02102 	lsl	r2, r2, #2
50008a94:	e5832000 	str	r2, [r3]
50008a98:	e59f30f0 	ldr	r3, [pc, #240]	; 50008b90 <lcd_init+0x234>
50008a9c:	e59f20ec 	ldr	r2, [pc, #236]	; 50008b90 <lcd_init+0x234>
50008aa0:	e5922000 	ldr	r2, [r2]
50008aa4:	e3c22020 	bic	r2, r2, #32
50008aa8:	e5832000 	str	r2, [r3]
50008aac:	e59f30dc 	ldr	r3, [pc, #220]	; 50008b90 <lcd_init+0x234>
50008ab0:	e59f20d8 	ldr	r2, [pc, #216]	; 50008b90 <lcd_init+0x234>
50008ab4:	e5922000 	ldr	r2, [r2]
50008ab8:	e3822001 	orr	r2, r2, #1
50008abc:	e5832000 	str	r2, [r3]
50008ac0:	e59f30cc 	ldr	r3, [pc, #204]	; 50008b94 <lcd_init+0x238>
50008ac4:	e59f20c8 	ldr	r2, [pc, #200]	; 50008b94 <lcd_init+0x238>
50008ac8:	e5922000 	ldr	r2, [r2]
50008acc:	e3c22807 	bic	r2, r2, #458752	; 0x70000
50008ad0:	e5832000 	str	r2, [r3]
50008ad4:	e59f30b8 	ldr	r3, [pc, #184]	; 50008b94 <lcd_init+0x238>
50008ad8:	e59f20b4 	ldr	r2, [pc, #180]	; 50008b94 <lcd_init+0x238>
50008adc:	e5922000 	ldr	r2, [r2]
50008ae0:	e3822801 	orr	r2, r2, #65536	; 0x10000
50008ae4:	e5832000 	str	r2, [r3]
50008ae8:	e59f30a4 	ldr	r3, [pc, #164]	; 50008b94 <lcd_init+0x238>
50008aec:	e59f20a0 	ldr	r2, [pc, #160]	; 50008b94 <lcd_init+0x238>
50008af0:	e5922000 	ldr	r2, [r2]
50008af4:	e3c22007 	bic	r2, r2, #7
50008af8:	e5832000 	str	r2, [r3]
50008afc:	e59f3090 	ldr	r3, [pc, #144]	; 50008b94 <lcd_init+0x238>
50008b00:	e59f208c 	ldr	r2, [pc, #140]	; 50008b94 <lcd_init+0x238>
50008b04:	e5922000 	ldr	r2, [r2]
50008b08:	e3822001 	orr	r2, r2, #1
50008b0c:	e5832000 	str	r2, [r3]
50008b10:	e3a03547 	mov	r3, #297795584	; 0x11c00000
50008b14:	e3a02547 	mov	r2, #297795584	; 0x11c00000
50008b18:	e5922000 	ldr	r2, [r2]
50008b1c:	e3822003 	orr	r2, r2, #3
50008b20:	e5832000 	str	r2, [r3]
50008b24:	e28bd000 	add	sp, fp, #0
50008b28:	e8bd0800 	pop	{fp}
50008b2c:	e12fff1e 	bx	lr
50008b30:	11400180 	.word	0x11400180
50008b34:	22222222 	.word	0x22222222
50008b38:	114001a0 	.word	0x114001a0
50008b3c:	114001c0 	.word	0x114001c0
50008b40:	114001e0 	.word	0x114001e0
50008b44:	1003c534 	.word	0x1003c534
50008b48:	1003c234 	.word	0x1003c234
50008b4c:	10010210 	.word	0x10010210
50008b50:	11c00004 	.word	0x11c00004
50008b54:	11c00010 	.word	0x11c00010
50008b58:	000c1509 	.word	0x000c1509
50008b5c:	11c00014 	.word	0x11c00014
50008b60:	0023d109 	.word	0x0023d109
50008b64:	11c00018 	.word	0x11c00018
50008b68:	000efb1f 	.word	0x000efb1f
50008b6c:	11c00020 	.word	0x11c00020
50008b70:	0000802d 	.word	0x0000802d
50008b74:	11c00048 	.word	0x11c00048
50008b78:	0005dc00 	.word	0x0005dc00
50008b7c:	11c00040 	.word	0x11c00040
50008b80:	11c00044 	.word	0x11c00044
50008b84:	0018f9df 	.word	0x0018f9df
50008b88:	11c000a0 	.word	0x11c000a0
50008b8c:	11c000d0 	.word	0x11c000d0
50008b90:	11c00034 	.word	0x11c00034
50008b94:	11c0003c 	.word	0x11c0003c

50008b98 <draw_point>:
50008b98:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
50008b9c:	e28db000 	add	fp, sp, #0
50008ba0:	e24dd01c 	sub	sp, sp, #28
50008ba4:	e50b0010 	str	r0, [fp, #-16]
50008ba8:	e50b1014 	str	r1, [fp, #-20]
50008bac:	e50b2018 	str	r2, [fp, #-24]
50008bb0:	e50b301c 	str	r3, [fp, #-28]
50008bb4:	e3a03206 	mov	r3, #1610612736	; 0x60000000
50008bb8:	e50b3008 	str	r3, [fp, #-8]
50008bbc:	e51b3014 	ldr	r3, [fp, #-20]
50008bc0:	e3a02e32 	mov	r2, #800	; 0x320
50008bc4:	e0030392 	mul	r3, r2, r3
50008bc8:	e1a02003 	mov	r2, r3
50008bcc:	e51b3010 	ldr	r3, [fp, #-16]
50008bd0:	e0823003 	add	r3, r2, r3
50008bd4:	e1a03103 	lsl	r3, r3, #2
50008bd8:	e51b2008 	ldr	r2, [fp, #-8]
50008bdc:	e0823003 	add	r3, r2, r3
50008be0:	e51b2018 	ldr	r2, [fp, #-24]
50008be4:	e1a01802 	lsl	r1, r2, #16
50008be8:	e51b201c 	ldr	r2, [fp, #-28]
50008bec:	e1a02402 	lsl	r2, r2, #8
50008bf0:	e1811002 	orr	r1, r1, r2
50008bf4:	e59b2004 	ldr	r2, [fp, #4]
50008bf8:	e1812002 	orr	r2, r1, r2
50008bfc:	e5832000 	str	r2, [r3]
50008c00:	e28bd000 	add	sp, fp, #0
50008c04:	e8bd0800 	pop	{fp}
50008c08:	e12fff1e 	bx	lr
