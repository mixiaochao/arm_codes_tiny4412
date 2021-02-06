#include <led.h>

/*设置GPM4[0:3]引脚为输出功能，低四个引脚都输出高电平*/
void led_init(void)
{
	GPM4CON &= ~0xffff;
	GPM4CON |= 0x1111;

	GPM4DAT |= 0xf;
}

void led_on(u32 num)
{
	if (num >= 0 && num <= 3) {
		GPM4DAT &= ~(0x1 << num);
	}
}

void led_off(u32 num)
{
	if (num >= 0 && num <= 3) {
		GPM4DAT |= (0x1 << num);
	}
}
