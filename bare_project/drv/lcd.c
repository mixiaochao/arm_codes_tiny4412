#include <lcd.h>
#include <backlight.h>

#define MILLET888 45

static void window0_init(void)
{
#ifdef MILLET888	//888
	WINCON0 = (1 << 15) | (0xb << 2) | (0x1 << 0);		
	VIDOSD0C = 800*480;
#else
	WINCON0 = (1 << 16) | (0x5 << 2) | (0x1 << 0);		//565
	VIDOSD0C = 800*480 >> 1;
#endif	
	VIDOSD0A = 0;		//左上角坐标
	VIDOSD0B = (799 << 11) | (479 << 0); //右下角坐标

	WINCHMAP2 &= ~0x7;
	WINCHMAP2 |= 0x1;

	WINCHMAP2 &= ~(0X7  << 16);
	WINCHMAP2 |= (0X1  << 16);

	SHADOWCON |= 0x1;        //10bit
	SHADOWCON &= ~(0x1 << 5);

	VIDW00ADD0B0 = FRAMBUFFER0;
	VIDW00ADD1B0 = FRAMBUFFER0 + VIDOSD0C*4;
}

static void window1_init(void)
{
#ifdef MILLET888
    WINCON1 = (1 << 15) | (0xb << 2)| (1 << 0); 
    VIDOSD1D = 800*480;
    VIDW01ADD2 = ((0 * 4) << 13) | ((800*4)); ///////////
#else
    WINCON1 = (1 << 16) | (5 << 2) | (1 << 0); 
    VIDOSD1D = 800*480 >> 1;
    VIDW01ADD2 = (( 0* 2) << 13) | ((800*2)); //////////
#endif

/* 指定窗口起始位置: */
    VIDOSD1A = 0;
/* 指定窗口结束位置: */
    VIDOSD1B = (799<<11) | (479<<0);

    SHADOWCON &= ~(0x1<<6);
    SHADOWCON |= 0x1<<1;

    WINCHMAP2 &= ~(0x7<<19);
    WINCHMAP2 |= 0x2<<19;

    WINCHMAP2 &= ~(0x7<<3);
    WINCHMAP2 |= 0x2<<3;
    
    W1KEYCON1 &= ~(0xffffff); /////////////
    W1KEYCON1 |= (0xff << 0);/////////////

    W1KEYCON0 &= ~(0x1<<25); ///////////
   	W1KEYCON0 |= (0x1<<25);

    VIDOSD1C = 0x999 << 12; //设置window1的BUF0的透明度

    VIDW01ADD0B0 = FRAMBUFFER1;
    VIDW01ADD1B0 = FRAMBUFFER1 + VIDOSD0C*4 ;
}



static void window2_init(void)
{
#ifdef MILLET888
    WINCON2 = (1 << 15) | (0xb << 2)| (1 << 0); 
    VIDOSD2D = 800*480;
    VIDW02ADD2 = ((0 * 4) << 13) | ((800*4)); ///////////
#else
    WINCON2 = (1 << 16) | (5 << 2) | (1 << 0); 
    VIDOSD2D = 800*480 >> 1;
    VIDW02ADD2 = (( 0* 2) << 13) | ((800*2)); //////////
#endif

/* 指定窗口起始位置: */
    VIDOSD2A = 0;
/* 指定窗口结束位置: */
    VIDOSD2B = (799<<11) | (479<<0);

    SHADOWCON &= ~(0x1<<7);
    SHADOWCON |= 0x1<<2;

    WINCHMAP2 &= ~(0x7<<19);
    WINCHMAP2 |= 0x5<<19;

    WINCHMAP2 &= ~(0x7<<6);
    WINCHMAP2 |= 0x5<<6;
    
    W2KEYCON1 &= ~(0xffffff); /////////////
    W2KEYCON1 |= (0x00ff00 << 0);/////////////

    W2KEYCON0 &= ~(0x1<<25); ///////////
   	W2KEYCON0 |= (0x1<<25);

    VIDOSD2C = 0x999 << 12; //设置window1的BUF0的透明度

    VIDW02ADD0B0 = FRAMBUFFER2;
    VIDW02ADD1B0 = FRAMBUFFER2 + VIDOSD0C*4 ;
}

void flush_win1()
{
	int i,j;
	for(i=0;i<800;i++)
		for(j=0;j<480;j++)
 		draw_point1(i,j, 0xff);//蓝色
}

void flush_win2()
{
	int i,j;
	for(i=0;i<800;i++)
		for(j=0;j<480;j++)
 		draw_point2(i,j, 0x00ff00);//蓝色
}

void lcd_init(void)
{
	/*将lcd和exynos4412相连的引脚设置成显示控制器*/
	GPF0CON	= 0x22222222;
	GPF1CON	= 0x22222222;
	GPF2CON	= 0x22222222;
	GPF3CON	&= ~0xffff;
	GPF3CON |= 0x2222;

	/*设置打点频率及使能数据的输出*/
	VIDCON0 = (0x2 << 6);

	/*设置时序的极性*/
	VIDCON1 = (0x1 << 9) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5);  //9???

	/*垂直同步信号的时序参数*/
	VIDTCON0 = (12 << 16) | (21 << 8) | (9 << 0);	

	/*水平同步信号的时序参数*/
	VIDTCON1 = (25 << 16) | (209 << 8) | (19 << 0);	

	/*设置物理LCD的分辨率大小*/
	VIDTCON2 = (479 << 11) | (799 << 0);

	/*window0 的初始化*/
	window0_init();
	window1_init();
	window2_init();
 	flush_win1();
 	flush_win2();
	/*设置LCD的时钟源：FIMD_SCLK*/
	CLK_SRC_LCD0 &= ~0xf;
	CLK_SRC_LCD0 |= 0x6;

	CLK_DIV_LCD &= ~0xf;
	CLK_DIV_LCD |= 0x7;

	/*打开背光*/
	LCDBLK_CFG |= 1 << 1;
	
	VIDCON0 |= 0x3;

	set_backlight_start(127);
}

void draw_point(int x, int y, int col)
{
#ifdef MILLET888
	*((u32 *)FRAMBUFFER0 + y*800 + x) = col;
#else
	*((u16 *)FRAMBUFFER0 + y*800 + x) = col;
#endif
}

void draw_point_page(int x, int y, int col,int ipage)
{
#ifdef MILLET888
	u32 frambuffer0 = 0x53000000 + 800*480*4*ipage;
	*((u32 *)frambuffer0 + y*800 + x) = col;
#else
	*((u16 *)FRAMBUFFER0 + y*800 + x) = col;
#endif
}


void draw_point1(int x, int y, int col)
{
#ifdef MILLET888
	*((u32 *)FRAMBUFFER1 + y*800 + x) = col;
#else
	*((u16 *)FRAMBUFFER1 + y*800 + x) = col;
#endif
}

void draw_point2(int x, int y, int col)
{
#ifdef MILLET888
	*((u32 *)FRAMBUFFER2 + y*800 + x) = col;
#else
	*((u16 *)FRAMBUFFER2 + y*800 + x) = col;
#endif
}

void clean_screen(int col)
{
	int i;

	for(i = 0; i < 800*480; i++){
		*((u32 *)FRAMBUFFER0 +i) = col;
	}
}


void clean_screen_half(int col)
{
	int i;
	for(i = 0; i < 800*400; i++)
	{
	*((u32 *)FRAMBUFFER1 +i) = col;
	}
}



