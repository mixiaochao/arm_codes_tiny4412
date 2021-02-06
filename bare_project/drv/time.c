#include <time.h>
#include <rtc.h>
#include <display.h>
#include <uart.h>
#include <string.h>
#include <lcd.h>
#include <key.h>
#include <buzzer.h>

#define BACKGROUND_M (42<<16)|(73<<8)|(225<<0)
#define TX 450
/*display system time*/

static void clean_time_screen()
{
	//clean hour min sec
	//display_4897num(TIME_X ,TIME_Y,11,COL(26,24,25),0,2);//clear screen
	//display_4897num(TIME_X+48,TIME_Y,11,COL(26,24,25),0,2);
	//display_4897num(TIME_X+48*3,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48*4,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48*6,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48*7,TIME_Y,11,COL(26,24,25),0,2);

	display_string(TX,0,"*************************",BACKGROUND_M,0,0);
					//	"2015-10-15  MON 21:57:35"

}


void disrtctime(rtc_time_t *time)
{
#if 0
	uprintf("20%d-%d-%d week:%d %dh-%dm-%ds\n", \
		time->yea,\
		time->mon,\
		time->date,\
		time->week,\
		time->hor,\
		time->min,\
		time->sec\
	);
#endif
	/*---------------------主菜单显示界面----------------------*/
	char buf[32] = {};
	if(time->hor == 0&& time->min == 0&& time->sec == 0)
		display_string(TX,0,"****************",BACKGROUND_M,0,0);
						  // "2015-10-01 MON "
	display_string(TX,0,itos(2000+time->yea,buf),0xffffff,0,0);
	display_string(TX+12*4,0,"-",0xffffff,0,0);

	display_string(TX+12*5,0,itos(time->mon,buf),0xffffff,0,0);
	display_string(TX+12*7,0,"-",0xffffff,0,0);

	display_string(TX+12*8,0,itos(time->date,buf),0xffffff,0,0);
	
	if(time->week == 0)
		display_string(TX+12*11,0,"SUN",0xffffff,0,0);
	if(time->week == 1)
		display_string(TX+12*11,0,"MON",0xffffff,0,0);
	if(time->week == 2)
		display_string(TX+12*11,0,"TUE",0xffffff,0,0);
	if(time->week == 3)
		display_string(TX+12*11,0,"WED",0xffffff,0,0);
	if(time->week == 4)
		display_string(TX+12*11,0,"THU",0xffffff,0,0);
	if(time->week == 5)
		display_string(TX+12*11,0,"FRI",0xffffff,0,0);
	if(time->week == 6)
		display_string(TX+12*11,0,"SAT",0xffffff,0,0);

	if(((time->hor)%10 == 0)&&(time->min == 0)&&(time->sec == 0))
		display_string(TX+12*15,0,"*",0x0000ff,0,0);	
	display_ASCII(TX+12*15,0,0x30+((time->hor)/10),0xffffff,0,0);


	if((time->min == 0) && (time->sec == 0))
		display_string(TX+12*16,0,"*",BACKGROUND_M,0,0);	
	display_ASCII(TX+12*16,0,0x30+((time->hor)%10),0xffffff,0,0);

	display_ASCII(TX+12*17,0,':',0xffffff,0,0);

	if(((time->min)%10 == 0)&&(time->sec == 0))
		display_string(TX+12*18,0,"*",BACKGROUND_M,0,0);	
	display_ASCII(TX+12*18,0,0x30+((time->min)/10),0xffffff,0,0);

	if(time->sec == 0)
		display_string(TX+12*19,0,"*",BACKGROUND_M,0,0);	
	display_ASCII(TX+12*19,0,0x30+((time->min)%10),0xffffff,0,0);
	
	display_ASCII(TX+12*20,0,':',0xffffff,0,0);

	if(((time->sec)%10) == 0)
		display_string(TX+12*21,0,"*",BACKGROUND_M,0,0);	
	display_ASCII(TX+12*21,0,0x30+((time->sec)/10),0xffffff,0,0);
		display_string(TX+12*22,0,"*",BACKGROUND_M,0,0);	
	display_ASCII(TX+12*22,0,0x30+((time->sec)%10),0xffffff,0,0);

/*--------------------------时钟界面显示-------------------------------------*/

#define FRONTGROUND ((68<<16)|(185<<8)|(205<<0))
#define BACKGROUND ((26<<16)|(24<<8)|(25<<0))
/*-----------显示年月日--------------*/
	//清屏
	if(time->hor == 0&& time->min == 0&& time->sec == 0)
	{
		display_2435num(TIME_X+24*2,     TIME_Y-40,11, BACKGROUND,0,2);
		display_2435num(TIME_X+24*3,     TIME_Y-40,11, BACKGROUND,0,2);
		display_2435num(TIME_X+24*4+32,  TIME_Y-40,11, BACKGROUND,0,2);
		display_2435num(TIME_X+24*5+32  ,TIME_Y-40,11, BACKGROUND,0,2);
		display_2435num(TIME_X+24*6+32*2,TIME_Y-40,11, BACKGROUND,0,2);
		display_2435num(TIME_X+24*7+32*2,TIME_Y-40,11, BACKGROUND,0,2);
		display_hanzi(TIME_X+24*9+32*4,  TIME_Y-40,11, BACKGROUND,0,2);//星期
	
	}
	display_2435num(TIME_X,TIME_Y-40,2,FRONTGROUND,0,2);
	display_2435num(TIME_X+24,TIME_Y-40,0,FRONTGROUND,0,2);
	display_2435num(TIME_X+24*2,TIME_Y-40,(time->yea)/10,FRONTGROUND,0,2);
	display_2435num(TIME_X+24*3,TIME_Y-40,(time->yea)%10,FRONTGROUND,0,2);
	display_hanzi(TIME_X+24*4,TIME_Y-40,7,FRONTGROUND,0,2);//年
	display_2435num(TIME_X+24*4+32,TIME_Y-40,(time->mon)/10,FRONTGROUND,0,2);
	display_2435num(TIME_X+24*5+32,TIME_Y-40,(time->mon)%10,FRONTGROUND,0,2);
	display_hanzi(TIME_X+24*6+32,TIME_Y-40,8,FRONTGROUND,0,2);//月

	display_2435num(TIME_X+24*6+32*2,TIME_Y-40,(time->date)/10,FRONTGROUND,0,2);
	display_2435num(TIME_X+24*7+32*2,TIME_Y-40,(time->date)%10,FRONTGROUND,0,2);
	display_hanzi(TIME_X+24*8+32*2,TIME_Y-40,9,FRONTGROUND,0,2);//日

	display_hanzi(TIME_X+24*9+32*3,TIME_Y-40,10,FRONTGROUND,0,2);//周
	display_hanzi(TIME_X+24*9+32*4,TIME_Y-40,time->week,FRONTGROUND,0,2);//星期

//	display_2435num(TIME_X+24*9+32*4,TIME_Y-40,(time->week),FRONTGROUND,0,2);



/*----------显示时钟---------*/
	if(((time->hor)%10 == 0)&&(time->min == 0)&&(time->sec == 0))
		display_4897num(TIME_X ,TIME_Y,11,COL(26,24,25),0,2);//clear screen
	display_4897num(TIME_X,TIME_Y,(time->hor)/10,FRONTGROUND,0,2);

	if((time->min == 0) && (time->sec == 0))
		display_4897num(TIME_X+48,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48,TIME_Y,(time->hor)%10,FRONTGROUND,0,2);

	display_4897num(TIME_X+48*2,TIME_Y,10,FRONTGROUND,0,2);//:
	
	if(((time->min)%10 == 0)&&(time->sec == 0))
		display_4897num(TIME_X+48*3,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48*3,TIME_Y,(time->min)/10,FRONTGROUND,0,2);

	if(time->sec == 0)
		display_4897num(TIME_X+48*4,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48*4,TIME_Y,(time->min)%10,FRONTGROUND,0,2);

	display_4897num(TIME_X+48*5,TIME_Y,10,FRONTGROUND,0,2);//:

	if(((time->sec)%10) == 0)
		display_4897num(TIME_X+48*6,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48*6,TIME_Y,(time->sec)/10,FRONTGROUND,0,2);
	display_4897num(TIME_X+48*7,TIME_Y,11,COL(26,24,25),0,2);
	display_4897num(TIME_X+48*7,TIME_Y,(time->sec)%10,FRONTGROUND,0,2);
}





rtc_time_t time;

static void updata_time(rtc_time_t *ptime)
{
	uprintf("updata time ...\n");
	setrtctime(ptime);
	clean_time_screen();
	uprintf("updata time ok\n");
}

static int flag_key1 = 0;

void time_change()
{
	flag_key1++;
	if(flag_key1 == 1)//hour
	{
		buzzer_di();
		getrtctime(&time);
		DISABLE_TICK_TIMER;
		draw_line(TIME_X,TIME_Y+97,48*2,3,0x00ff,0,2);
		uprintf("time change 1\n");
	}
	if(flag_key1 == 2)//min
	{
		buzzer_di();
		draw_line(TIME_X,TIME_Y+97,48*2,3,BACKGROUND,0,2);//清除上一条线

		draw_line(TIME_X+48*3,TIME_Y+97,48*2,3,0x00ff,0,2);
		uprintf("time change 2\n");
	
	}
	if(flag_key1 == 3)//sec
	{
		buzzer_di();
		draw_line(TIME_X+48*3,TIME_Y+97,48*2,3,BACKGROUND,0,2);

		draw_line(TIME_X+48*6,TIME_Y+97,48*2,3,0x00ff,0,2);
		uprintf("time change 3\n");
	
	}
	if(flag_key1 == 4)//year
	{	
		buzzer_di();
		draw_line(TIME_X+48*6,TIME_Y+97,48*2,3,BACKGROUND,0,2);

		draw_line(TIME_X,TIME_Y-5,24*4,3,0x00ff,0,2);
		uprintf("time change 4\n");


	}
	if(flag_key1 == 5)//month
	{
		
		buzzer_di();
		draw_line(TIME_X,TIME_Y-5,24*4,3,BACKGROUND,0,2);
		
		draw_line(TIME_X+24*4+32,TIME_Y-5,24*2,3,0x00ff,0,2);
	}
	if(flag_key1 == 6)//date
	{
		buzzer_di();
		draw_line(TIME_X+24*4+32,TIME_Y-5,24*2,3,BACKGROUND,0,2);
		draw_line(TIME_X+24*6+32*2,TIME_Y-5,24*2,3,0x00ff,0,2);
	}
	if(flag_key1 == 7)//week
	{
		buzzer_di();
		draw_line(TIME_X+24*6+32*2,TIME_Y-5,24*2,3,BACKGROUND,0,2);
		draw_line(TIME_X+24*9+32*3,TIME_Y-5,32*2,3,0x00ff,0,2);
		
	}
	if(flag_key1 == 8)
	{
		buzzer_di();
		flag_key1 = 0;
		draw_line(TIME_X+24*9+32*3,TIME_Y-5,32*2,3,BACKGROUND,0,2);
		uprintf("time change 4\n");
		updata_time(&time);
		ENABLE_TICK_TIMER;
	}
}

static int isLeap(int year)
{
	return ((year%4==0)&&(year%100!=0))||(year%400==0);
}
void time_add()
{
	rtc_time_t *ptime = &time;
	if(flag_key1==1)//hour
	{
		(ptime->hor)++;
		if(ptime->hor == 24)
			ptime->hor = 0;

		uprintf("hour++:%d\n",ptime->hor);
		buzzer_di();
		if((ptime->hor)%10 == 0)
				display_4897num(TIME_X ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X,TIME_Y,(ptime->hor)/10,FRONTGROUND,0,2);

		display_4897num(TIME_X+48 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48,TIME_Y,(ptime->hor)%10,FRONTGROUND,0,2);
	}

	if(flag_key1 == 2)//min
	{
		(ptime->min)++;
		if(ptime->min == 60)
			ptime->min = 0;

		uprintf("min++:%d\n",ptime->min);
		buzzer_di();
		if((ptime->min)%10 == 0)
			display_4897num(TIME_X+48*3 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*3,TIME_Y,(ptime->min)/10,FRONTGROUND,0,2);

		display_4897num(TIME_X+48*4 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*4,TIME_Y,(ptime->min)%10,FRONTGROUND,0,2);
	}

	if(flag_key1 == 3)//min
	{
		(ptime->sec)++;
		if(ptime->sec == 60)
			ptime->sec = 0;

		uprintf("sec++:%d\n",ptime->sec);
		buzzer_di();
		if((ptime->sec)%10 == 0)
				display_4897num(TIME_X+48*6 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*6,TIME_Y,(ptime->sec)/10,FRONTGROUND,0,2);

		display_4897num(TIME_X+48*7 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*7,TIME_Y,(ptime->sec)%10,FRONTGROUND,0,2);
	}
	if(flag_key1 == 4)
	{
		(ptime->yea)++;
		if(ptime->yea ==100)
			ptime->yea = 0;
		uprintf("yea++:%d\n",ptime->yea);
		buzzer_di();
		//clean year
		display_2435num(TIME_X+24*2,TIME_Y-40,11,BACKGROUND,0,2);
		display_2435num(TIME_X+24*3,TIME_Y-40,11,BACKGROUND,0,2);
	
		display_2435num(TIME_X+24*2,TIME_Y-40,(ptime->yea)/10,FRONTGROUND,0,2);
		display_2435num(TIME_X+24*3,TIME_Y-40,(ptime->yea)%10,FRONTGROUND,0,2);

	}
	if(flag_key1 == 5)
	{
		(ptime->mon)++;
		if(ptime->mon == 13)
			ptime->mon = 1;

		buzzer_di();
		display_2435num(TIME_X+24*4+32,TIME_Y-40,11,BACKGROUND,0,2);
		display_2435num(TIME_X+24*5+32,TIME_Y-40,11,BACKGROUND,0,2);

		display_2435num(TIME_X+24*4+32,TIME_Y-40,(ptime->mon)/10,FRONTGROUND,0,2);
		display_2435num(TIME_X+24*5+32,TIME_Y-40,(ptime->mon)%10,FRONTGROUND,0,2);
	}
	if(flag_key1 == 6)
	{
		(ptime->date)++;
		buzzer_di();
		if(isLeap(ptime->yea) && ptime->mon ==2&&(ptime->date)== 30)
			ptime->date = 1;
		else if((isLeap(ptime->yea)==0)&& ptime->mon == 2 &&(ptime->date)==29)
			ptime->date = 1;
		else if((ptime->mon == 4 || ptime->mon == 6 || ptime->mon == 9 || ptime->mon == 11)&& ptime->date == 31)
			ptime->date = 1;
		else if(ptime->date == 32)	
			ptime->date = 1;

		display_2435num(TIME_X+24*6+32*2,TIME_Y-40,11,BACKGROUND,0,2);
		display_2435num(TIME_X+24*7+32*2,TIME_Y-40,11,BACKGROUND,0,2);

		display_2435num(TIME_X+24*6+32*2,TIME_Y-40,(ptime->date)/10,FRONTGROUND,0,2);
		display_2435num(TIME_X+24*7+32*2,TIME_Y-40,(ptime->date)%10,FRONTGROUND,0,2);

	}
	if(flag_key1 == 7)
	{
		(ptime->week)++;
		if(ptime->week == 7)
			ptime->week = 0;
		buzzer_di();
		display_hanzi(TIME_X+24*9+32*4,TIME_Y-40,11,BACKGROUND,0,2);//星期
		display_hanzi(TIME_X+24*9+32*4,TIME_Y-40,ptime->week,FRONTGROUND,0,2);//星期
	}

}


void  time_sub()
{
	rtc_time_t *ptime = &time;
	if(flag_key1 == 1)//hour
	{
		(ptime->hor)--;
		if((ptime->hor) > 0xffff )
		{
			ptime->hor = 23;
			uprintf("-----hour-----:%d\n",ptime->hor);
		}

		uprintf("hour--:%d\n",ptime->hor);
		buzzer_di();
		if(((ptime->hor)%10 == 3) || ((ptime->hor)%10 == 9))
				display_4897num(TIME_X ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X,TIME_Y,(ptime->hor)/10,FRONTGROUND,0,2);

		display_4897num(TIME_X+48 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48,TIME_Y,(ptime->hor)%10,FRONTGROUND,0,2);
	}

	if(flag_key1 == 2)//min
	{
		(ptime->min)--;
		if((ptime->min) > 0xffff )
		{
			ptime->min = 59;
			uprintf("-----min-----:%d\n",ptime->min);
		}

		uprintf("min--:%d\n",ptime->min);
		buzzer_di();
		if((ptime->min)%10 == 9)
				display_4897num(TIME_X+48*3 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*3,TIME_Y,(ptime->min)/10,FRONTGROUND,0,2);

		display_4897num(TIME_X+48*4,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*4,TIME_Y,(ptime->min)%10,FRONTGROUND,0,2);
	}


	if(flag_key1 == 3)//sec
	{
		(ptime->sec)--;
		if((ptime->sec) > 0xffff )
		{
			ptime->sec = 59;
			uprintf("-----sec-----:%d\n",ptime->sec);
		}

		uprintf("sec--:%d\n",ptime->sec);
		buzzer_di();
		if((ptime->sec)%10 == 9)
				display_4897num(TIME_X+48*6 ,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*6,TIME_Y,(ptime->sec)/10,FRONTGROUND,0,2);

		display_4897num(TIME_X+48*7,TIME_Y,11,BACKGROUND,0,2);//clear screen
		display_4897num(TIME_X+48*7,TIME_Y,(ptime->sec)%10,FRONTGROUND,0,2);
	}
	if(flag_key1 == 4)//year
	{
		
		(ptime->yea)--;
		if(ptime->yea == 0)
			ptime->yea = 99;
		uprintf("yea++:%d\n",ptime->yea);
		buzzer_di();
		//clean year
		display_2435num(TIME_X+24*2,TIME_Y-40,11,BACKGROUND,0,2);
		display_2435num(TIME_X+24*3,TIME_Y-40,11,BACKGROUND,0,2);
	
		display_2435num(TIME_X+24*2,TIME_Y-40,(ptime->yea)/10,FRONTGROUND,0,2);
		display_2435num(TIME_X+24*3,TIME_Y-40,(ptime->yea)%10,FRONTGROUND,0,2);
	}
	if(flag_key1 == 5)
	{
		(ptime->mon)--;
		if(ptime->mon == 0)
			ptime->mon = 12;

		buzzer_di();
		display_2435num(TIME_X+24*4+32,TIME_Y-40,11,BACKGROUND,0,2);
		display_2435num(TIME_X+24*5+32,TIME_Y-40,11,BACKGROUND,0,2);

		display_2435num(TIME_X+24*4+32,TIME_Y-40,(ptime->mon)/10,FRONTGROUND,0,2);
		display_2435num(TIME_X+24*5+32,TIME_Y-40,(ptime->mon)%10,FRONTGROUND,0,2);
	}
	if(flag_key1 == 6)
	{
		(ptime->date)--;
		buzzer_di();
		if(isLeap(ptime->yea) && ptime->mon ==2&&(ptime->date)== 0)
			ptime->date = 29;
		else if((isLeap(ptime->yea)==0)&& ptime->mon == 2 &&(ptime->date)==0)
			ptime->date = 28;
		else if((ptime->mon == 4 || ptime->mon == 6 || ptime->mon == 9 || ptime->mon == 11)&& ptime->date == 0)
			ptime->date = 30;
		else if((ptime->mon == 1 || ptime->mon == 3 || ptime->mon == 5 || ptime->mon == 7 || ptime->mon == 8||ptime->mon == 10||ptime->mon ==12)&& ptime->date == 0)
			ptime->date = 31;

		display_2435num(TIME_X+24*6+32*2,TIME_Y-40,11,BACKGROUND,0,2);
		display_2435num(TIME_X+24*7+32*2,TIME_Y-40,11,BACKGROUND,0,2);

		display_2435num(TIME_X+24*6+32*2,TIME_Y-40,(ptime->date)/10,FRONTGROUND,0,2);
		display_2435num(TIME_X+24*7+32*2,TIME_Y-40,(ptime->date)%10,FRONTGROUND,0,2);

	}
	if(flag_key1 == 7)
	{
		(ptime->week)--;
		buzzer_di();
		if(ptime->week > 0xff)
			ptime->week = 6;
		display_hanzi(TIME_X+24*9+32*4,TIME_Y-40,11,BACKGROUND,0,2);//星期
		display_hanzi(TIME_X+24*9+32*4,TIME_Y-40,ptime->week,FRONTGROUND,0,2);//星期
	}

}

void tp_time_menu(int x,int y)
{

	if(x>20&&x<120&&y>210&&y<260)
	{
		time_change();
	}
	if(x>20&&x<120&&y>300&&y<350)
	{
		time_add();
	}
	if(x>20&&x<120&&y>370&&y<420)
	{
		time_sub();
	}
}

