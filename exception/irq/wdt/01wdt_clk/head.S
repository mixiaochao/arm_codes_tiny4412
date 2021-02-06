
.align 2
.text
.global _start

_start: 
	b       reset     		   @0x0
        ldr     pc, _undefined_instruction @0x4
        ldr     pc, _software_interrupt	   @0x8	
        ldr     pc, _prefetch_abort        @0xc
        ldr     pc, _data_abort            @0x10
        ldr     pc, _not_used              @0x14
        ldr     pc, _irq                   @0x18    
        ldr     pc, _fiq		   @0x1c

_undefined_instruction: 
	.word undefined_instruction
_software_interrupt:   
	.word software_interrupt
_prefetch_abort:        
	.word prefetch_abort
_data_abort:            
	.word data_abort
_not_used:              
	.word not_used
_irq:                   
	.word irq 
_fiq:                   
	.word fiq 

reset:
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

	bl clr_bss
	bl main

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}

undefined_instruction:
	
	mov sp, #0x79000000
	stmfd sp!, {r0-r12, lr}
	bl do_unde
	ldmfd sp!, {r0-r12, pc}^
	
software_interrupt:
	stmfd sp!, {r0-r12, lr}
	sub r0, lr,#4
	ldr r0, [r0]
	bic r0, r0, #0xff000000
	bl do_svc
	ldmfd sp!, {r0-r12, pc}^

prefetch_abort:

data_abort:

not_used:

irq:
	mov sp, #0x78000000
	sub lr, #4
	stmfd sp!, {r0-r12, lr}
	ldr pc, do_irq_
	ldmfd sp!, {r0-r12, pc}^

do_irq_:
	.word do_irq

fiq:

excep_sec:

excep_start:
	.word _start	
excep_end:
	.word excep_sec

.globl excep_start
.globl excep_end
 
__start_bss:
	.word _bss_start
__end_bss:
	.word _bss_end

clr_bss:
	ldr r0, __start_bss
	ldr r1, __end_bss

	mov r2, #0

	loop:
		cmp r0, r1
		bge end
		str r2, [r0], #4
		b loop
	end:
		
	mov pc, lr	
		
