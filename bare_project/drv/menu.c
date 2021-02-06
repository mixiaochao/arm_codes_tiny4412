#include <lcd.h>
#include <isr.h>
#include <rtc.h>
#include <key.h>
#include <boot.h>
#include <display.h>
#include <gobang.h>
#include <led.h>
#include <uart.h>
#include <calendar.h>
#include <gallery.h>
#include <wdt.h>
#include <display.h>
#include <time.h>
#include <adc.h>
#include <timer.h>
#include <buzzer.h>

int Menu_flag = 0;
#define MAIN_MENU 0
#define GOBANG    1
#define TIME      2
#define GALLERY   3
#define LED_MENU  4
#define AD_MENU   5
#define CALENDER  6
#define CLOCK     7
#define BUZZER    8
#define WATCHDOG  9

extern int points;
extern  int boot_flag;
extern int gobang_begin;
extern int gobang_back;
int gallery_time = 0;
extern int pic_change;
extern int cal_count;
extern int wdt_time;
static void Screen(int i)
{

	VIDW00ADD0B0 = 0x53000000+800*480*4*i;
	VIDW00ADD1B0 = 0x53000000+800*480*4*i + VIDOSD0C*4;
}


void menu(int x,int y)
{

	if(Menu_flag == MAIN_MENU && boot_flag == 1)
	{	
		Screen(0);//主界面
		
		if(x>=130&&x<250&&y>=100&&y<200)//五子棋图标范围
		{
			Menu_flag = GOBANG;
			Screen(1);
			gobang_all_display();
			
			x = 0;//防止点击五子棋图标对下棋的影响
			y = 0;
		}
		else if(x>=300&&x<400&&y>=100&&y<200)//时钟图标范围
		{
			Menu_flag = TIME;
			Screen(2);
		}
		else if(x>=430&&x<520&&x>=100&&y<200)//图库
		{
			Menu_flag = GALLERY;
			Screen(3);
			pic_viwer();//缩略图
			x = 0;
			y = 0;
		}
		else if(x>=590&&x<670&&y>=100&&y<200)//LED
		{
			Menu_flag = LED_MENU;
			Screen(4);
			uprintf("--------------LED----------------\n");
		}
		else if(x>=120&&x<200&&y>=250&&y<350)//wathdog
		{
			Menu_flag = WATCHDOG;
			Screen(5);
			wdt_init(150000);
			timer4_init(1000);
		}
		else if(x>=270&&x<370&&y>=250&&y<350)//BUZZER
		{
			Menu_flag = BUZZER;
			buzzer_init();
			Screen(6);
			x = 0;
			y = 0;
		}
		else if(x>=430&&x<530&&y>250&&y<350)//CALENDER
		{
			Menu_flag = CALENDER;
			Screen(7);
		}
		else if(x>=590&&x<670&&y>=250&&y<350)
		{
			Menu_flag = AD_MENU;
			adc_init(0); 
			timer3_init(1000);
			Screen(8);
		}
	}

	if(Menu_flag == GOBANG)
	{
		gobang_menu(x,y);

		if(gobang_back ==1)//退出坐标
		{
			Menu_flag = MAIN_MENU;
			gobang_back_clean();
			flush_win2();
			gobang_back  = 0;
			gobang_begin = 0;

			Screen(0);//主菜单界面
		}
	}

	if(Menu_flag == TIME)
	{
		tp_time_menu(x,y);
		if(x>760&&x<799&&y>0&&y<40)	
		{
			Screen(0);//主菜单界面
			Menu_flag = MAIN_MENU;
		}
	}	
	if(Menu_flag == GALLERY)
	{
		if(points <= 3)	
		{
		 gallery_display(x,y);
		}
		if(points > 3)	
		{
			Screen(0);//主菜单界面
			Menu_flag = MAIN_MENU;
			gallery_time = 0;
			pic_change = 0;
		}
	}

	if(Menu_flag == LED_MENU)
	{
		#if 1
		uprintf("----------------------------------led control---------------------------\n");
		uprintf("points:%d\n",points);
		if(x!=0&&y!=0)
		{
			led_control(x,y);
		}
		#endif
		if(x>760&&x<799&&y>0&&y<40)	
		{
			uprintf("@@@@@@@@@@@@@@@@@@@@@@quit@@@@@@@@@@@@@@@@@@@@@\n");
			uprintf("points:%d\n",points);
			Screen(0);//主菜单界面
			Menu_flag = MAIN_MENU;
		}
	}

	if(Menu_flag == WATCHDOG)
	{
		if(points < 2)	
			wdt_ctrl(x,y);
		if(x>760&&x<799&&y>0&&y<40)	
		{
			Screen(0);//主菜单界面
			Menu_flag = MAIN_MENU;
			//uprintf("menu_flag3 : %d\n",Menu_flag);
		 	DISABLE_RESET;
			wdt_time = 15;
		}
	}


	if(Menu_flag == BUZZER)
	{
		buzzer_control(x,y);
		if(x>760&&x<799&&y>0&&y<40)	
		{
			GPD0CON &= ~0xf;
			GPD0CON &= ~(0x2 << 0);

			Screen(0);//主菜单界面
			Menu_flag = MAIN_MENU;
			
		}
	}

	if(Menu_flag == CALENDER)
	{

		//display_month(2015,10);
		calendar_menu();
		if(x>760&&x<799&&y>0&&y<40)	
		{
			flush_win1();
			cal_count = 0;
			Screen(0);//主菜单界面
			Menu_flag = MAIN_MENU;
		}
	}


	if(Menu_flag == AD_MENU)
	{
		ad_alarm(x,y);
		if(x>760&&x<799&&y>0&&y<40)	
		{
			 TINT_CSTAT &= ~(1 << 3);
			Screen(0);//主菜单界面
			Menu_flag = MAIN_MENU;
		}
	}
}




