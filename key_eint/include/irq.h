#ifndef XCM_IRQ_H_
#define XCM_IRQ_H_

#include <lib.h>

typedef void (*handler_t)(void);
extern void irq_request_cpu0(u32 irqnum, void (*handler)(void), u32 level);

#define ICCICR_CPU0	*((volatile u32 *)0x10480000) 
#define ICCPMR_CPU0	*((volatile u32 *)0x10480004)
#define ICDDCR		*((volatile u32 *)0x10490000)

#define ICCIAR_CPU0	*((volatile u32 *)0x1048000c)
#define ICCEOIR_CPU0	*((volatile u32 *)0x10480010)

#define ICDIPR_CPU0	((volatile u32 *)0x10490400)
#define ICDIPTR_CPU0	((volatile u32 *)0x10490800)
#define ICDISER_CPU0	((volatile u32 *)0x10490100)

#endif
