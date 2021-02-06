#include <common.h>
#include <key.h>
#include <vectors.h>
#include <irq.h>
#include <lcd.h>
#include <image.h>

int main(void)
{
	/*建立异常向量表*/
	build_vectors();

	/*按键中断的设置*/
	key_init();

	lcd_init();

	image_rotat();

	return 0;
}
