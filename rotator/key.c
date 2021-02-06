#include <key.h>
#include <irq.h>
#include <isr.h>

void key_init(void)
{
	 GPX3CON |= 0xffff << 8;
	 
	 //设置4个按键的触发方式为falling
	 EXT_INT43_CON &= ~(0xffff << 8);
	 EXT_INT43_CON |= 0x2222 << 8;

	 EXT_INT43_MASK &= ~(0xf << 2);

	 EXT_INT43_FLTCON0 |= 0xffff << 16;

	 EXT_INT43_FLTCON1 |= 0xffff;	
		
	 irq_request_cpu0_(KEY_IRQ, do_key, LEV);
}
