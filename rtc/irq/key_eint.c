#include <keyeint.h>

void do_keys(void)
{
	switch ((EXT_INT43_PEND>>2)&0xf) {
		case 0x1:
			printf("key 1 dnup...\n");
			break;
		case 0x2:
			printf("key 2 dnup...\n");
			break;
		case 0x4:
			printf("key 3 dnup...\n");
			break;
		case 0x8:
			printf("key 4 dnup...\n");
			break;
	}

	EXT_INT43_PEND = EXT_INT43_PEND;
}

void key_eint_init(void)
{
	/*设置GPX3[2:5]为外部中断功能*/
	GPX3CON |= 0xffff << 8;

	/*设置GPX3[2:5]的中断触发方式为上升沿*/
	EXT_INT43CON &= ~(0xffff << 8);
	EXT_INT43CON |= (0x3333 << 8);

	/*选择数字滤波，使能数字滤波，设置滤波的时钟周期个数*/
	EXT_INT43_FLTCON0 |= 0xffff << 16;
	EXT_INT43_FLTCON1 |= 0xffff;

	/*使能4个按键对应的外部中断*/
	EXT_INT43_MASK &= ~(0xf << 2);
}

