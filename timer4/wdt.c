#include <wdt.h>

void do_wdt_timer(void)
{
	printf("watch dog coming...\n");
	WTCLRINT = 0;
}

void wdt_timer_init(u32 ms)
{
	WTCON = (255 << 8) | (1 << 5) | (3 << 3) | (1 << 2);
	WTDAT = 3*ms;
	WTCNT = 3*ms;
}

void wdt_reset_init(u32 ms)
{
	WTCON = (255 << 8) | (1 << 5) | (3 << 3) | (1 << 0);
	WTDAT = 3*ms;
	WTCNT = 3*ms;

#define AUTOMATIC_WDT_RESET_DISABLE  	*((volatile u32 *)0x1002040C)
#define MASK_WDT_RESET_REQUEST		*((volatile u32 *)0X10020408)

	AUTOMATIC_WDT_RESET_DISABLE = 0;
	MASK_WDT_RESET_REQUEST = 0;
}
