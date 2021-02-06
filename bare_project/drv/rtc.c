#include <rtc.h>
#include <irq.h>
#include <display.h>
#include <lcd.h>
#include <string.h>
#include <uart.h>
#include <time.h>
/*bcd code date to bin date change*/
static u32 bcd2bin(u32 bcd)
{
	return ((bcd & 0xf) + ((bcd >> 4)&0xf)*10);
}

/*bin date to bcd code date change*/
static u32 bin2bcd(u32 bin)
{
	return ((bin%10) | ((bin / 10) << 4));
}

/*alarm interrupt service function*/
static void do_alarm(void)
{
	if(INTP&0x2){
		INTP |= 1 << 1;

	//	printf("di di di, di di di...\n");
	}
}

/*set alarm*/
void setrtcalarm(rtc_time_t *time)
{
	ALMYEAR 	=  bin2bcd(time->yea); 
 	ALMMON  	=  bin2bcd(time->mon); 
 	ALMDAY  	=  bin2bcd(time->date);
 	ALMHOUR 	=  bin2bcd(time->hor); 
 	ALMMIN		=  bin2bcd(time->min); 
 	ALMSEC		=  bin2bcd(time->sec); 

	RTCALM	= (0x1 << 6) | (0x1 << 2) | (0x1 << 1) | (0x1 << 0);

#define ALARM_INT 76
	irq_request_cpu0(ALARM_INT, do_alarm, 0);
}

/*set system time*/
void setrtctime(rtc_time_t *time)
{
	RTCCON          |= 0x1;
	BCDYEAR 	=  bin2bcd(time->yea); 
 	BCDMON  	=  bin2bcd(time->mon);  
 	BCDDAY  	=  bin2bcd(time->date);
 	BCDDAYWEEK 	=  bin2bcd(time->week); 
 	BCDHOUR 	=  bin2bcd(time->hor); 
 	BCDMIN		=  bin2bcd(time->min); 
 	BCDSEC		=  bin2bcd(time->sec); 
	RTCCON          &= ~0x1;
}

/*get system time*/
void getrtctime(rtc_time_t *time)
{
	time->yea  = bcd2bin(BCDYEAR&0xff); 
 	time->mon  = bcd2bin(BCDMON&0x1f);   
 	time->date = bcd2bin(BCDDAY&0x3f); 
 	time->week = bcd2bin(BCDDAYWEEK&0x7); 
 	time->hor  = bcd2bin(BCDHOUR&0x3f); 
 	time->min  = bcd2bin(BCDMIN&0x7f); 
 	time->sec  = bcd2bin(BCDSEC&0x7f);
}


/*tic timer interrupt service function*/
static void do_tic(void)
{
	rtc_time_t time;

	if(INTP&0x1)
	{
		INTP |= 0X1;
		getrtctime(&time);
		disrtctime(&time);
	}
}

/*set rtc tic timer*/
void rtc_tic_init(int ms)
{
	TICCNT = 33*ms;
//	RTCCON|= 1 << 8;
	//Enables Tick timer 
	ENABLE_TICK_TIMER;

#define TIC_INT 77
	irq_request_cpu0(TIC_INT, do_tic, 0);	
}

