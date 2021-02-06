#include <lcd.h>
#include <common.h>

//#define BPP565 XX

#define FRAMEBUFFER00 0x60000000

void lcd_init(void)
{
	//gpio
	GPF0CON = 0x22222222;
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;
	GPF3CON &= ~(0xffff);
	GPF3CON |= 0x2222;
	//时钟
	CLK_DIV_LCD &= ~0xf;

	CLK_SRC_LCD0 &= ~0xf;
	CLK_SRC_LCD0 |= 6;

	//系统配置
	LCDBLK_CFG |= 1 << 1; //使能显示控制器

	//lcd控制器 8
	VIDCON0 = (23 << 6);

	//配置LCD需要的时序的极性
	VIDCON1 = (1 << 9) | (1 << 7) | (1 << 6) | (1 << 5);

	//LCD要求的垂直同步信号的时序参数
	VIDTCON0 = (12 << 16) | (21 << 8) | (9);

	//LCD要求的水平同步信号的时序参数
	VIDTCON1 = (35 << 16) | (209 << 8) | (9);

	//设置要显示的LCD的行和列的大小
	VIDTCON2 = (479 << 11) | 799;

	//win0
#ifdef BPP565
	WINCON0 = (1 << 16) | (5 << 2) | 1;

	//窗口的大小，以字为单位
	VIDOSD0C = 480 * 800 >> 1;
#else
	WINCON0 = (1 << 15)| (11 << 2) | 1; //使能按字交换

	//窗口的大小，以字为单位
	VIDOSD0C = 480 * 800;
#endif

	//设置要显示的LCD的左上角的x，y坐标。
	VIDOSD0A = 0;
	
	//设置要显示的LCD的右下角的x，y坐标。
	VIDOSD0B = (799 << 11) | 479;

	VIDW00ADD0B0 = FRAMEBUFFER00;
	VIDW00ADD1B0 = FRAMEBUFFER00 + VIDOSD0C * 4;

	//选择DMA传输数据的方式，并使能DMA的0通道
	SHADOWCON &= ~(1 << 5);
   	SHADOWCON |= 1;
	
	WINCHMAP2 &= ~(7 << 16);
	WINCHMAP2 |= 1 << 16;

	WINCHMAP2 &= ~7;
	WINCHMAP2 |= 1;
 
	VIDCON0 |= 3;	
}

void draw_point(int x, int y, int r, int g, int b)
{
#ifdef BPP565
	unsigned short *v = (void *)FRAMEBUFFER00;
	*(v + y * 800 + x) = (r << 11) | (g << 5) | b;
#else
	unsigned int *v = (void *)FRAMEBUFFER00;
	*(v + y * 800 + x) = (r << 16) | (g << 8) | b;
#endif
}
