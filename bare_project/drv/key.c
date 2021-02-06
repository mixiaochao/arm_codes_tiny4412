#include <key.h>
#include <irq.h>
#include <rtc.h>
#include <uart.h>
#include <display.h>

#include <time.h>


static void do_key(void)
{
	switch((EXT_INT43_PEND>>2)&0xf){
		case 1:
			time_change(0,0);
			break;
		case 2:
			time_add(0,0);
			break;
		case 4:
			time_sub(0,0);
			break;
		case 8:
			break;
		default:
			break;
	}	

	EXT_INT43_PEND = EXT_INT43_PEND;
}

/*4keys driver by external interrupt*/
void eint_key(void)
{
	/*set GPX3_2~GPX3_5 as external interrupt*/
	/*external interrupt num is: 26,27,28,29*/
	GPX3CON |= 0xffff << 8;	

	/*set interrupt trigger signal is both edge*/
	EXT_INT43CON &= ~(0xffff << 8);	
	EXT_INT43CON |= 0x3333 << 8;	

	/*set digital filter and enable*/
	EXT_INT43_FLTCON0 |= 0xffff << 16;
	EXT_INT43_FLTCON1 |= 0xffff << 0;

	/*enable external interrupt*/
	EXT_INT43_MASK &= ~(0xf << 2);

#define EINT_KEY 64
	irq_request_cpu0(EINT_KEY, do_key, 0);
}
