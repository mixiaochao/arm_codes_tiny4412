#ifndef IRQ_H_
#define IRQ_H_

#include <comm.h>

#define NUM 160

typedef void (*do_irq_t)(void);

extern void do_irq(void);
extern void irq_request_cpu0(int irqnum, void (*do_isr)(void), int lev);

#define ICCICR_CPU0 	*((u32 *)0x10480000) 
#define ICCPMR_CPU0 	*((u32 *)0x10480004) 
#define ICCIAR_CPU0 	*((u32 *)0x1048000C)
#define ICCEOIR_CPU0 	*((u32 *)0x10480010) 

#define ICDDCR 		*((u32 *)0x10490000) 
#define ICDIPR0_CPU0 	((u32 *)0x10490400)
#define ICDIPTR0_CPU0 	((u32 *)0x10490800) 
#define ICDISER0_CPU0 	((u32 *)0x10490100) 

#endif
