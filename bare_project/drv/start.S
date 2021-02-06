
.text
.align 2
.global _start

_start:

	b reset  		@0x0
	ldr pc,unde_		
	ldr pc,svc_		
	ldr pc,prefech_abt_	
	ldr pc,data_abt_	
	.word 0x95273856
	ldr pc,irq_             @0x18
	ldr pc,fiq_

unde_:.word unde
svc_: .word svc
prefech_abt_:.word prefech_abt
data_abt_   :.word data_abt
irq_: .word irq
fiq_: .word fiq	  

_end:

reset:

	ldr sp, =0x7fe00000

	mrs r0,cpsr
	bic r0,#0x1f
	orr r0,#0x12
	msr cpsr,r0

	ldr sp,=0x7ff00000

	mrs r0,cpsr
	bic r0,#0x1f
	orr r0,#0x13
	msr cpsr,r0

	bl clear_bss
	bl app_entry

step:
	b step

unde:
	mov sp,#0x80000000
	stmfd sp!,{r0-r12,lr}
	mov lr,pc
	ldr pc,do_unde_
	ldmfd sp!,{r0-r12,pc}^

	do_unde_:
		.word do_unde	
svc:
	stmfd sp!,{r0-r12,lr}
	sub lr,#4
	ldr r0,[lr]
	bic r0,#0xff000000
	mov lr, pc
	ldr pc,do_svc_
	ldmfd sp!,{r0-r12,pc}^

	do_svc_:
		.word do_svc	
prefech_abt:
data_abt:
irq:
	sub lr,#4
	stmfd sp!,{r0-r12,lr}
	mov lr,pc
	ldr pc,do_irq_
	ldmfd sp!,{r0-r12,pc}^	

	do_irq_:
		.word do_irq
fiq:	
.global _end
.global _start

clear_bss:

	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4
	
	ldr r0,bss_start
	ldr r1,bss_end

	mov r2,#0

	for_clear:
		cmp r0,r1
		bgt end

		str r2,[r0],#4
	b for_clear
	
	end:

	sub sp, fp, #12
	ldm sp,{fp, sp, pc}

bss_start:
	.word milletbss_start
bss_end:
	.word milletbss_end


