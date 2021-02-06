#include <lcd.h>
#include <backlight.h>

int main(void)
{
	int i,j;

	set_backlight_start(127);

	lcd_init();

	return 0;
}

