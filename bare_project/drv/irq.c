#include <irq.h>

static do_irq_t isrs[NUM];  

void do_irq(void)
{
	do_irq_t handler = NULL;

	int irqnum;

	irqnum = ICCIAR_CPU0&0x3ff;	
	ICCEOIR_CPU0 = irqnum;

	handler = isrs[irqnum];

	handler();
}


void irq_request_cpu0(int irqnum, void (*do_isr)(void), int lev)
{
	ICCICR_CPU0 = 0x1;
	ICCPMR_CPU0 = 0xff;	
	ICDDCR = 0x1;
	
	ICDIPR0_CPU0[irqnum>>2] &= ~(0xff << (irqnum%4)*8);
	ICDIPR0_CPU0[irqnum>>2] |= (lev << (irqnum%4)*8);

	ICDIPTR0_CPU0[irqnum>>2] &= ~(0xff << ((irqnum%4)*8));
	ICDIPTR0_CPU0[irqnum>>2] |= (0x1 << ((irqnum%4)*8));

	ICDISER0_CPU0[irqnum>>5] |= 0x1 << (irqnum%32);

	isrs[irqnum] = do_isr;	

	__asm__ __volatile__(

		"mrs r0, cpsr\n\t"
		"bic r0, #0x80\n\t"
		"msr cpsr,r0\n\t"
	);
}
