#include <mmu.h>
#include <rtc.h>
#include <irq.h>

void do_unde(void)
{

}

void do_svc(u32 imme)
{

}

int main(void)
{
	rtctime_t t = {
		.year = 17,
		.mon  = 6,
		.mday = 16,
		.hour = 14,
		.min  = 15,
		.sec  = 0,
		.wday = 5
	};


	rebuild_vectors_table();		

	rtc_tic_irq_init();	
	rtc_settime(&t);


	return 0;
}

