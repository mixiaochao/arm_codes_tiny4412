#include <wdt.h>
#include <irq.h>
#include <led.h>
#include <uart.h>
#include <display.h>
#include <mmu.h>
#include <vector.h>
#include <timer.h>
#include <rtc.h>
#include <adc.h>
#include <lcd.h>
#include <boot.h>
#include <menu.h>
#include <comm.h>


void display_wdt_time(int wdt_time)
{
		display_4897num(216,160,11,0x84a425,0,5);
		display_4897num(264,160,11,0x84a425,0,5);
		display_4897num(216,160,wdt_time/10,0xff7b29,0,5);
		display_4897num(264,160,wdt_time%10,0xff7b29,0,5);
}


void wdt_init(int ms)
{

#define AUTOMATIC_WDT_RESET_DISABLE *((u32*)(0x10020408))
#define MASK_WDT_RESET_REQUEST      *((u32*)(0x1002040c))

	AUTOMATIC_WDT_RESET_DISABLE = 0;
	MASK_WDT_RESET_REQUEST = 0;

	WTCON = (0xff << 8) | (0x1 << 5) | (0x3 << 3) | (0x1 << 2);
	WTDAT = WTCNT = ms*3;

	ENABLE_RESET;

}
extern int wdt_time;
void wdt_ctrl(int x,int y)
{
	if(x<=400&&y>=240)//喂狗
	{
		WTDAT = WTCNT = 150000*3;
		wdt_time = 15;
	}
}



