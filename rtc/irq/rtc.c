#include <rtc.h>
#include <irq.h>

//12  0001  0010 -> 0x12
u16  bin2bcd(u16 n)
{
	return ((n%10) | ((n/10) << 4));
}

//0x12  --> 12
u16  bcd2bin(u16 n)
{
	return (n&0xf) + ((n>>4)&0xf)*10;	
}

void rtc_gettime(rtctime_t *t)
{
	t->year = bcd2bin(BCDYEAR);
	t->mon  = bcd2bin(BCDMON);
	t->mday = bcd2bin(BCDDAY);
	t->hour = bcd2bin(BCDHOUR);
	t->min  = bcd2bin(BCDMIN);
	t->sec  = bcd2bin(BCDSEC);
	t->wday = bcd2bin(BCDDAYWEEK); 	
}

/*设置RTC的系统时间寄存器*/
void rtc_settime(rtctime_t *t)
{
	RTCCON |= 0x1;

	BCDYEAR    =   bin2bcd(t->year); 
	BCDMON     =   bin2bcd(t->mon);  
	BCDDAY     =   bin2bcd(t->mday); 
	BCDHOUR    =   bin2bcd(t->hour); 
	BCDMIN     =   bin2bcd(t->min);  
	BCDSEC     =   bin2bcd(t->sec);  
	BCDDAYWEEK =   bin2bcd(t->wday); 

	RTCCON &= ~0x1;
}

void do_ticalarm(void)
{
	if (INTP&0x2) {
		printf("wake up ...di di di...\n");
		INTP |= 0x2;
	} else if (INTP&0x1) {
		rtctime_t t;

		rtc_gettime(&t);

		printf("20%02d-%02d-%02d  %02d:%02d:%02d  weekday: %d\n",
				t.year, t.mon, t.mday, t.hour, t.min, t.sec,
							t.wday);
		INTP |= 0x1;
	}
}

void rtc_set_alarm(rtctime_t *t)
{
	//ALMYEAR   =	bin2bcd(t->year);   
	//ALMMON    =	bin2bcd(t->mon);  
	//ALMDAY    =	bin2bcd(t->mday); 
	ALMHOUR	  =	bin2bcd(t->hour); 
	ALMMIN    =	bin2bcd(t->min);  
	ALMSEC    =	bin2bcd(t->sec);    

	/*使能闹钟，考虑时分秒*/
	RTCALM = (1 << 6) | (0x7 << 0);

	irq_request_cpu0(RTCALM_IRQID, do_ticalarm, 0);
}

/*TIC的定时中断周期为0.5s*/
void rtc_tic_irq_init(void)
{
	irq_request_cpu0(RTCTIC_IRQID, do_ticalarm, 0);

	TICCNT = (32768 >> 1) - 1;
	RTCCON |= 1 << 8;
	RTCCON &= ~(0xf << 4);
}
