#include <calendar.h>
#include <display.h>
#include <lcd.h>
#include <rtc.h>
#include <timer.h>
#include <uart.h>
int months[2][13] = {
		{0,31,28,31,30,31,30,31,31,30,31,30,31},
		{0,31,29,31,30,31,30,31,31,30,31,30,31}
	};

char cns[13][10] = {
		"","一月", "二月", "三月", "四月", "五月", "六月",
		"七月", "八月", "九月", "十月", "十一月", "十二月",
	};


static int isLeap(int year)
{
	return ((year%4==0)&&(year%100!=0))||(year%400==0);
}

// 求1月1号是星期几
static int firstYear(int year)
{
	int i;
	int yeardays = 0;
	
	for (i=1980; i<year; i++) {
		yeardays += 365 + isLeap(i);
	}
	
	return (yeardays%7 + 2 ) % 7;
}

#if 0
// 显示年历
void f1()
{
	int year;
	int idx;
	int i;
	
	printf("year: ");
	scanf("%d", &year);
	int fist_year = firstYear(year);
	
	for (idx=1; idx<=12; idx++ ) {
		int fist_mon  = firstMonth(year, idx);
		printf("\n\n%s\n", cns[idx]);
		printf("日 一 二 三 四 五 六\n");
		printf("--------------------\n");
	
		for (i=0; i<fist_mon; i++)
			printf("   ");
		for (i=1; i<=months[isLeap(year)][idx]; i++) {
			printf("%2d ", i);
			if ((i%7+fist_mon)%7 == 0 )
				printf("\n");
		}
	
		printf("\n--------------------\n");
	}
}

#endif

// 求当前月1号是星期几
static int firstMonth(int year, int month)
{
	int i;
	int monthdays = 0;

	for (i=1; i<month; i++) {
		monthdays += months[isLeap(year)][i];
	}
	
	return (monthdays%7 + firstYear(year)) % 7;
}

static void itod(unsigned int num, char *buf)
{
	int i;

	if(num < 10){
		buf[0] = num + '0';
		buf[1] = '\0';
		return;
	}

	itod(num/10, buf);

	for(i = 0; buf[i] != '\0'; i++);

	buf[i] = num%10 + '0';
	buf[i+1] = '\0';
}
 
static void draw_cricle(int x,int y,int color)
{
	int r = 18;
	int i,j;
	for(i = x-r; i < x+r; i++)
		for(j = y-r; j < y+r; j++)
		{
			if((i-x)*(i-x)+(j-y)*(j-y) <= r*r)
				draw_point1(i,j,color);
		}
}


#define POS_X 200
#define POS_Y 150
#define SPACE 25
#define CAL_BACKGROUND ((239<<16)|(41<<8)|(41<<0))
// 显示月历
static void display_month(int year,int month,int date)
{
	int i;
	int j = 0;
	int k = 0;
//	int date = 8;
	char buf[32] = {0};
	//int fist_year = firstYear(year);//求当前年1月1日是星期几
	int fist_mon  = firstMonth(year, month);//求当前月1号是星期几

	//printf("日 一 二 三 四 五 六\n");
	//printf("--------------------\n");
	
// 	flush_win1();
#define CAL_BACKGROUND1 ((239<<16)|(214<<8)|(9<<0))
	//显示年
	display_2435num(POS_X+40+24*0,POS_Y-80,year/1000,  CAL_BACKGROUND1,1,0);
	display_2435num(POS_X+40+24*1,POS_Y-80,year/100%10,CAL_BACKGROUND1,1,0);
	display_2435num(POS_X+40+24*2,POS_Y-80,year/10%10, CAL_BACKGROUND1,1,0);
	display_2435num(POS_X+40+24*3,POS_Y-80,year%10,    CAL_BACKGROUND1,1,0);
	display_hanzi(POS_X+40+24*4,POS_Y-80,7,CAL_BACKGROUND1,1,0);//年
	//显示月
	if(month/10 != 0)
		display_4897num(POS_X+200,POS_Y-120,month/10,CAL_BACKGROUND1,1,0);
	display_4897num(POS_X+248,POS_Y-120,month%10,CAL_BACKGROUND1,1,0);
	display_hanzi(POS_X+248+48,POS_Y-80,8,CAL_BACKGROUND1,1,0);//月
	
	display_string(POS_X,POS_Y,"SUN  MON  TUE  WED  THU  FRI  SAT  ",CAL_BACKGROUND,1,7);
	for (i=0; i<fist_mon; i++);
		//printf("   ");
		//display_string(0+12*5*i,0+25,"*****",0x00ff00,0,7);
	for (i=1; i<=months[isLeap(year)][month]; i++) 
	{
		///printf("%2d ", i);
		itod(i,buf);
		if(j == 0)
		{
			if(i == date)
				draw_cricle(POS_X+12+4+12*fist_mon*5+12*(i-1)*5+6,POS_X+11,0x00ff00);
			display_string(POS_X+12+12*fist_mon*5+12*(i-1)*5,POS_Y+(22+SPACE)*(j+1),buf,CAL_BACKGROUND,1,7);	
		}
		else
		{
			if(i == date)
				draw_cricle(POS_X+12+4+12*5*k+6,POS_Y+(22+SPACE)*(j+1)+11,0x00ff00);
			display_string(POS_X+12+12*5*k,POS_Y+(22+SPACE)*(j+1),buf,CAL_BACKGROUND,1,7);
			k++;
		}
		if ((i%7+fist_mon)%7 == 0 )
		{
			//printf("\n");
			j++;
			k = 0;
		}
	}
//	printf("\n--------------------\n");
}
extern int slip_dict;
rtc_time_t time;
int cal_count = 0;
void calendar_menu()
{
	cal_count++;
	if(cal_count == 1)
		getrtctime(&time);
	display_month(2000+time.yea,time.mon,time.date);	
	if(slip_dict > 100)//slip to left
	{
		uprintf("month++\n");
		time.mon++;
		if(time.mon == 13)
		{
			time.mon = 1;
			time.yea++;
			if(time.yea == 99)
				time.yea = 0;
		}
		flush_win1();

		uprintf("month++:%d\n",time.mon);
		display_month(2000+time.yea,time.mon,time.date);	
		slip_dict = 0;
	}
	if(slip_dict < -100)
	{
		uprintf("month--\n");
		time.mon--;
		if(time.mon == 0)
		{
			time.mon = 12;
			time.yea--;
			if(time.yea == 0)
				time.yea = 99;
		}
		flush_win1();
		
		uprintf("month--:%d\n",time.mon);
		display_month(2000+time.yea,time.mon,time.date);	
		slip_dict = 0;
	}
}



