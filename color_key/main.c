#include <lcd.h>
#include <backlight.h>

int main(void)
{
	set_backlight_start(127);

	lcd_init();

	return 0;
}

