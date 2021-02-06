#include <irq.h>


/*函数指针数组的每一个元素指向对应中断号的中断处理函数*/
handler_t isr[160];

/*中断发生前需要写好，中断发生后自动被硬件调用*/
/*中断信号的响应函数*/
void do_irq(void)
{
	handler_t handler = NULL;

	/*获取GIC收到的CPU核心的处理响应状态中的中断号*/
	u32 irqnum = ICCIAR_CPU0&0x3ff;

	/*取出中断注册时准备的中断处理函数的地址*/
	handler = isr[irqnum];

	/*执行与对应中断号相关的中断处理函数*/
	handler();

	handler = NULL;
		
	/*清GIC的中断*/
	ICCEOIR_CPU0 = irqnum;

	printf("call do_irq\n");
}


/*中断发生前需要做的设置*/
/*根据中断号irqnum设置GIC， 开启CPU核心对中断的响应*/
void irq_request_cpu0(u32 irqnum, void (*handler)(void), u32 level)
{
	/*使能GIC和CPU0转发中断信号的接口*/
	ICCICR_CPU0 = 0x1;
	/*设置CPU0接收中断信号的优先级阈值为最低*/
	ICCPMR_CPU0 = 0xff;
	/*使能GIC监视中断信号并转发给CPU核心*/
	ICDDCR = 0x1;

	if ((irqnum >= 0) && (irqnum < 160)) {

		/*设置中断号为irqnum的中断的优先级*/	
		ICDIPR_CPU0[irqnum/4] &= ~(0xff << (irqnum%4)*8);
		ICDIPR_CPU0[irqnum/4] |= level << ((irqnum%4)*8);

		/*设置中断号为irqnum的中断转发给cpu0*/	
		ICDIPTR_CPU0[irqnum/4] &= ~(0xff << (irqnum%4)*8);	
		ICDIPTR_CPU0[irqnum/4] |= 0x1 << ((irqnum%4)*8);	

		/*用于使能中断号为irqnum的中断*/
		ICDISER_CPU0[irqnum/32] |= 0x1 << (irqnum%32);
	} else {
		return;
	}


	isr[irqnum] = handler;

	/*开启CPU核心对中断的响应*/
	__asm__ __volatile__ (
		"mrs r0, cpsr\n\t"
		"bic r0, #0x80\n\t"
		"msr cpsr, r0\n\t"
	);
}

