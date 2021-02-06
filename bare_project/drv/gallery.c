#include<gallery.h>
#include<lcd.h>
#include<uart.h>
#include<timer.h>
#include<isr.h>

extern int touch_fun;
extern int touch_fun_2 ;
static int num_g = 0;

extern int points;
int pic_change=0;
void pic_viwer(void)
{
	int x0, y0, x1, y1;

	u32 *dst = (u32 *)(0x53000000+(800*480*4*3));
	u32 *src = (u32 *)(0x55000000);

	for(y0 = 0; y0 < 4; y0++){    //小图片所在的行
		for(x0 = 0; x0 < 5; x0++){//小图片所在的列
			for(y1  = 0; y1 < 120; y1++){
				for(x1 = 0; x1 < 160; x1++){
					*(dst + (y0*120 + y1)*800 + x0*160 + x1) = \
					*(src + ((y0*5 + x0)*480 + y1*4)*800 + x1*5);	
				}
			}
		}
	}
	VIDW00ADD0B0 = 0x53000000+(800*480*4*3);
	VIDW00ADD1B0 = 0x53000000+(800*480*4*3)+ VIDOSD0C*4;
}

#define S_TO_BIG 1
#define BIG_TO_S 2
#define NEXT     3
#define LAST     4
extern int slip_dict;//滑屏距离
void gallery_display(int x,int y)
{
	if(slip_dict > 50)
	{
		touch_fun_2 = NEXT;
	}
	else if(slip_dict < -50)
	{
		touch_fun_2 = LAST;
	}
	else
	{
		touch_fun_2 = 0;
	}
	if(x!=0 && y!=0)
	{
		if(points ==1&&pic_change ==0) 
		{	
		
			num_g = y/120*5 + x/160;//320 120
			if(num_g>=20) num_g = 0;
			if(num_g<0) num_g = 19;	
			VIDW00ADD0B0 = 0x55000000 + num_g*480*800*4;
			VIDW00ADD1B0 = 0x55000000 + VIDOSD0C*4;	
		
			pic_change = 1;
		}
	}	
	if( touch_fun_2 ==NEXT&&pic_change ==1) 
	{
		num_g++;
		if(num_g>=20) num_g = 0;	uprintf("gallery insert 3\n");
		VIDW00ADD0B0 = 0x55000000 + num_g*480*800*4;
		VIDW00ADD1B0 = 0x55000000 + VIDOSD0C*4;
		pic_change =1;
	
	}
	if(touch_fun_2 ==LAST&&pic_change ==1) //&&touch_fun_2 != 0
	{		
		num_g--;
		if(num_g<0) num_g = 19;	
		uprintf("gallery insert 4\n");
		VIDW00ADD0B0 = 0x55000000 + num_g*480*800*4;
		VIDW00ADD1B0 = 0x55000000 + VIDOSD0C*4;	
		pic_change =1;	
		
	}	
	
	if(points ==3) 
	{		
		pic_viwer();	
		pic_change = 0;
		 num_g = 0;
	}
		
	
}









