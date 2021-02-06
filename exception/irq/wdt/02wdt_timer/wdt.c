#include <wdt.h>

/*看门狗的定时中断处理函数*/
void do_wdt_timer(void)
{
	printf("watch dog coming...\n");
	WTCLRINT = 0;
}

/*利用wdt设备来实现16bit定时*/
void wdt_timer_init(u32 ms)
{
	WTCON = (255 << 8) | (1 << 5) | (3 << 3) | (1 << 2);
	WTDAT = 3*ms;
	WTCNT = 3*ms;
}
