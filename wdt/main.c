#include <mmu.h>
#include <wdt.h>
#include <irq.h>
#include <lcd.h>
#include <backlight.h>
#include <pwm.h>

void do_unde(void)
{

}

void do_svc(u32 imme)
{

}

int main(void)
{

	
	set_backlight_start(127);

	rebuild_vectors_table();		

	irq_request_cpu0(WDTID, do_wdt_timer, 0);

	wdt_timer_init(3000);

	lcd_init();

	return 0;
}

