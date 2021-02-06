#include <mmu.h>
#include <vector.h>
#include <wdt.h>
#include <led.h>
#include <buzzer.h>
#include <timer.h>
#include <key.h>
#include <rtc.h>
#include <adc.h>
#include <lcd.h>
#include <display.h>
#include <uart.h>
#include <boot.h>
#include <menu.h>
#include <comm.h>

void do_unde(void)
{
//	printf("undef instruction exception occur!!\n");
}

void do_svc(int imme24)
{
//	printf("call %s!\n", __func__);
}


void app_entry(void)
{


	copy_to_ddr_from_sd(705, 40960, (u32*)0x53000000);	
	copy_to_ddr_from_sd(42000, 61440,(u32*)0x55000000);	
	build_vectors_table(VECTOR_BASE);

	uart0_init();
	lcd_init();
	boot_view();

	VIDW00ADD0B0 = 0x53000000;
	VIDW00ADD1B0 = 0x53000000 + VIDOSD0C*4;

}
