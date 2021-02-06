#include <lcd.h>

static void gpio_init(void);
static void lcd_clksrc_set(void);
static void win0_init(void);
static void win1_init(void);

#define BPP888 SUIYI

/*lcd的驱动函数接口*/
void lcd_init(void)
{
	/*用于设置GFP0，GPF1，GPF2，GPF3*/
	gpio_init();

	/*选择显示控制器的时钟源为MPLLL(800MHz), 再进行(7+1)分频
	  得到100MHz*/
	lcd_clksrc_set();

	/*一会儿回来*/
	LCDBLK_CFG |= 1 << 1;

	/*对100MHz的时钟源进行3分频得到S700需要的33.3MHz*/
	VIDCON0 = (2 << 6);

	/*设置打点时钟为上升沿有效，垂直和水平同步信号需要翻转*/
	VIDCON1 = (1 << 5) | (1 << 6) | (1 << 7) | (1 << 9);

	/*对照exynos4412的时序图和S700的时序图设置垂直同步信号的时序*/
	VIDTCON0 = (12 << 16) | (21 << 8) | (9 << 0);

	
	/*对照exynos4412的时序图和S700的时序图设置水平同步信号的时序*/
	VIDTCON1 = (25 << 16) | (209 << 8) | (19 << 0); //

	/*根据LCD的物理像素点精度设置*/
	VIDTCON2 = (479 << 11) | (799 << 0);

	win0_init();	
	win1_init();

	/*开启显示和时序信号*/
	VIDCON0 |= 3;
	
}

static void win0_init(void)
{
#ifdef BPP888
	/*设置按字交换，显示数据的格式为BPP888， 使能显示*/
	WINCON0 = (1 << 15) | (0xb << 2) | (1 << 0);
	VIDOSD0C = 800*480; /*设置显示区域的数据大小，单位为字*/
#else
	WINCON0 = (1 << 16) | (0x5 << 2) | (1 << 0);
	VIDOSD0C = 800*480 >> 1;
#endif
	WINCHMAP2 &= ~(0x7 << 16);
	WINCHMAP2 |= (0x1 << 16);

	WINCHMAP2 &= ~0x7;
	WINCHMAP2 |= 0x1 << 0;

	SHADOWCON &= ~(1 << 5);
	SHADOWCON |= 1;

	/*设置LCD要显示的左上角坐标和右下角坐标*/
	VIDOSD0A = 0;
	VIDOSD0B = (799 << 11) | (479 << 0);

	/*设置WINDOW0的BUFFER0的起始地址*/
	VIDW00ADD0B0 = FRAMBUFFER0; 
	/*设置WINDOW0的BUFFER0的结束地址*/
	VIDW00ADD1B0 = FRAMBUFFER0 + VIDOSD0C*4; 
}


/*将每一个引脚设置成LCD专用*/
static void gpio_init(void)
{
	GPF0CON = 0x22222222;
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;

	GPF3CON &= ~0xffff;
	GPF3CON |= 0x2222;
}

//set sclk_fimd = 100MHz
static void lcd_clksrc_set(void)
{
	CLK_SRC_LCD0 &= ~0xf;
	CLK_SRC_LCD0 |= 0x6;

	CLK_DIV_LCD &= ~0xf;
	CLK_DIV_LCD |= 0x7;
}

void draw_point(int x, int y, int r, int g, int b)
{
#ifdef BPP888
	unsigned int *p = (void *)FRAMBUFFER0;
	*(p + y * 800 + x) = (r << 16) | (g << 8) | b;
#else
	unsigned short *p = (void *)FRAMBUFFER0;
	*(p + y * 800 + x) = (r << 11) | (g << 5) | b;
#endif
}

static void win1_init(void)
{
#ifdef BPP888
	WINCON1 = (1 << 15) | (11 << 2) | 1;
	VIDOSD1D = 480 * 800;
#else
	WINCON1 = (1 << 16) | (5 << 2) | 1;
	VIDOSD1D = 480 * 800 >> 1;
#endif
	WINCHMAP2 &= ~(7 << 3); //window 1 choose channel 1
	WINCHMAP2 |= 2 << 3;	

	WINCHMAP2 &= ~(7 << 19); //channel 1 choose window 1
	WINCHMAP2 |= 2 << 19;

	SHADOWCON &= ~(1 << 6); //禁用"本地传输"使能通道DMA的channel 1传输
	SHADOWCON |= 1 << 1;

	VIDOSD1A = 0;//设置左上角和右下角坐标
	VIDOSD1B = (799 << 11) | (479);

	VIDOSD1C = 0x000 << 12; //设置window1的BUF0的透明度

	VIDW01ADD0B0 = FRAMBUFFER1;
	VIDW01ADD1B0 = FRAMBUFFER1 + VIDOSD1D*4;
}

