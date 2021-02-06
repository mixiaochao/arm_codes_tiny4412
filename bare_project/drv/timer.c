#include <timer.h>
#include <irq.h>
#include <adc.h>
#include <display.h>
#include <menu.h>
#include <uart.h>
#include <wdt.h>
extern int fst_point_flag;
extern int coordinate[2][2]; //coordinate[0][0] = x0, [0][1] = y0;
int num = 0;

int touch_fun = 0;
int touch_fun_2 = 0;
extern int points;
int slip_dict = 0;
#define S_TO_BIG 1
#define BIG_TO_S 2
#define NEXT     3
#define LAST     4

static void do_timer0(void)
{
	if(TINT_CSTAT&(1 << 5))
	{
		TINT_CSTAT |= 1 << 5;
#if 1		
	//	printf("come timer0 interrupt!:%d\n",num);
		if(num%2 == 0)
			draw_line(100,400,100+50*num,20,0xffffff,-1,0);
		else	
			draw_line(150+50*num,400,40,20,0xff0000,-1,0);

		num++;
		if(num > 10)
		{
			TINT_CSTAT &= ~(1 << 0);//colse timer0

		}
#endif
	//	printf("come timer0 interrupt!:%d\n",num);
	}
}

#if 0
static void do_timer1(void)
{
	if(TINT_CSTAT&(1 << 6)){
		TINT_CSTAT |= 1 << 6;
		
		printf("come timer1 interrupt!\n");
	}
}
#endif

static void do_timer2(void)
{
	int tmp;

	if(TINT_CSTAT&(1 << 7))
	{
		TINT_CSTAT |= 1 << 7;
		
		fst_point_flag = 1;	
//		uprintf("up (%d, %d)!\n", coordinate[1][0], 
//						coordinate[1][1]);
		
		tmp = (coordinate[0][0] - coordinate[1][0]);
		slip_dict = tmp;
		if(tmp > 50)
		{
			 touch_fun_2  = NEXT;
		}
		else if(tmp < -50)
			{
			 touch_fun_2 = LAST;
			}
			else
			{
 			touch_fun_2 = 0;
			}
		menu(coordinate[0][0],coordinate[0][1]);
	
		tmp = 0;
	}
}
	

static void do_timer3(void)
{
	if(TINT_CSTAT&(1 << 8)){
		TINT_CSTAT |= 1 << 8;
		
		START_ADC_CONVERT;
	}
}
int wdt_time = 15;
static void do_timer4(void)
{
	if(TINT_CSTAT&(1 << 9)){
		TINT_CSTAT |= 1 << 9;
		
		display_wdt_time(wdt_time);
		wdt_time--;
		if(wdt_time < 0)
			TINT_CSTAT &= ~(1 << 4);//diable_timer4
	}
}

void timer0_init(int ms)
{
	num = 0;

	/*get timer0 work f=1MHz*/
	TCFG0 &= ~0xff;	
	TCFG0 |= 99;
	TCFG1 &= ~0xf;

	/*set timer0's perioid  ms ms*/
	TCNTB0 = 1000*ms;

	TCON &= ~(0xf << 0);
	
	/*manual update TCNTB0*/
	TCON |= 1 << 1; 
	TCON &= ~(1 << 1);

	/*set auto-reload and start timer0 work*/
	TCON |= (1 << 3) | (1 << 0);

	/*register timer0's interrupt*/
#define TIMER0_INT 69
	irq_request_cpu0(TIMER0_INT, do_timer0, 0);

	/*enable timer0 interrupt*/
	TINT_CSTAT |= 1 << 0;
}
#if 0
void timer1_init(int ms)
{
	/*get timer1 work f=1MHz*/
	TCFG0 &= ~0xff;	
	TCFG0 |= 99 ;
	TCFG1 &= ~(0xf << 4);

	/*set timer1's perioid  ms ms*/
	TCNTB1 = 1000*ms;

	TCON &= ~(0xf << 8);
	
	/*manual update TCNTB1*/
	TCON |= 1 << 9; 
	TCON &= ~(1 << 9);

	/*set auto-reload and start timer1 work*/
	TCON |= (1 << 8) | (1 << 11);

	/*register timer1's interrupt*/
#define TIMER1_INT 70
	irq_request_cpu0(TIMER1_INT, do_timer1, 0);

	/*enable timer1 interrupt*/
	TINT_CSTAT |= 1 << 1;

}
#endif

void timer2_enable(void)
{
	TCON &= ~(0xf << 12);
	/*manual update TCNTB2*/
	TCON |= 1 << 13; 
	TCON &= ~(1 << 13);

	/*start timer2 work*/
	TCON |= (1 << 12);
	/*enable timer2 interrupt*/
	TINT_CSTAT |= 1 << 2;
}

void timer2_init(int ms)
{
	/*get timer2 work f=1MHz*/
	TCFG0 &= ~(0xff << 8);	
	TCFG0 |= 99 << 8;
	TCFG1 &= ~(0xf << 8);

	/*set timer2's perioid  ms ms*/
	TCNTB2 = 1000*ms;


	/*register timer2's interrupt*/
#define TIMER2_INT 71
	irq_request_cpu0(TIMER2_INT, do_timer2, 0);
}

void timer3_init(int ms)
{
	/*get timer3 work f=1MHz*/
	TCFG0 &= ~(0xff << 8);	
	TCFG0 |= 99 << 8;
	TCFG1 &= ~(0xf << 12);

	/*set timer3's perioid  ms ms*/
	TCNTB3 = 1000*ms;

	TCON &= ~(0xf << 16);
	
	/*manual update TCNTB3*/
	TCON |= 1 << 17; 
	TCON &= ~(1 << 17);

	/*set auto-reload and start timer3 work*/
	TCON |= (1 << 16) | (1 << 19);

	/*register timer3's interrupt*/
#define TIMER3_INT 72
	irq_request_cpu0(TIMER3_INT, do_timer3, 0);

	/*enable timer3 interrupt*/
	TINT_CSTAT |= 1 << 3;

}


void timer4_init(int ms)
{
	/*get timer4 work f=1MHz*/
	TCFG0 &= ~(0xff << 8);	
	TCFG0 |= 99 << 8;
	TCFG1 &= ~(0xf << 16);

	/*set timer4's perioid  ms ms*/
	TCNTB4 = 1000*ms;

	TCON &= ~(0x7 << 20);
	
	/*manual update TCNTB4*/
	TCON |= 1 << 21; 
	TCON &= ~(1 << 21);

	/*set auto-reload and start timer4 work*/
	TCON |= (1 << 20) | (1 << 22);

	/*register timer4's interrupt*/
#define TIMER4_INT 73
	irq_request_cpu0(TIMER4_INT, do_timer4, 0);

	/*enable timer4 interrupt*/
	TINT_CSTAT |= 1 << 4;
}









