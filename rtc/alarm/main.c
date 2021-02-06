#include <mmu.h>
#include <rtc.h>
#include <timer.h>
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
		.hour = 16,
		.min  = 35,
		.sec  = 0,
		.wday = 5
	};


	rebuild_vectors_table();		

	rtc_tic_irq_init();	
	rtc_settime(&t);

	t.hour = 16;
	t.min  = 35;
	t.sec  = 10;

	rtc_set_alarm(&t);

	beep_set_hz(5);

	return 0;
}

