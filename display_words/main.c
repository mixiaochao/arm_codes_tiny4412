#include <lcd.h>
#include <backlight.h>
#include <words.h>

int main(void)
{
	int i,j;

	set_backlight_start(127);

	lcd_init();

	for(i = 0; i < 800; i++){
		for(j = 0; j < 480; j++){
			draw_point(i,j,0,0,255);
		}
	}

	write_words(140, 100, words, 5);
	write_words(140, 280, &words[5], 5);
			


	return 0;
}

