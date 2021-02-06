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

void app_entry(void)
{
	void (*jumptodrv)(void) = (void *)0x43e00000;

	copy_to_ddr_from_sd(49, 656, (u32 *)0x43e00000);	

	jumptodrv();
}
