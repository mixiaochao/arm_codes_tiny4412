#include <lcd.h>
#include <backlight.h>

int main(void)
{
	int i,j;

	set_backlight_start(127);

	lcd_init();

	for(i = 0; i < 800; i++){
		for(j = 0; j < 480; j++){
			draw_point(i,j,255,0,0);
		}
	}


	return 0;
}

