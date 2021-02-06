#ifndef RTC_H_
#define RTC_H_

#include <comm.h>

typedef struct{
	u32 yea;
	u32 mon;
	u32 date;
	u32 week;
	u32 hor;
	u32 min;
	u32 sec;
}rtc_time_t;

extern void rtc_tic_init(int ms);
extern void setrtcalarm(rtc_time_t *time);
extern void setrtctime(rtc_time_t *time);
extern void getrtctime(rtc_time_t *time);

#define INTP 	 	*((u32 *)0x10070030) 
#define RTCCON 		*((u32 *)0x10070040) 
#define TICCNT 		*((u32 *)0x10070044) 
#define RTCALM 		*((u32 *)0x10070050) 
#define ALMSEC 		*((u32 *)0x10070054) 
#define ALMMIN 		*((u32 *)0x10070058) 
#define ALMHOUR		*((u32 *)0x1007005C) 
#define ALMDAY 		*((u32 *)0x10070060) 
#define ALMMON 		*((u32 *)0x10070064) 
#define ALMYEAR		*((u32 *)0x10070068) 
#define BCDSEC 		*((u32 *)0x10070070) 
#define BCDMIN 		*((u32 *)0x10070074) 
#define BCDHOUR		*((u32 *)0x10070078) 
#define BCDDAY 		*((u32 *)0x1007007C) 
#define BCDDAYWEEK 	*((u32 *)0x10070080) 
#define BCDMON 		*((u32 *)0x10070084) 
#define BCDYEAR		*((u32 *)0x10070088) 
#define CURTICCNT 	*((u32 *)0x10070090) 




#define ENABLE_TICK_TIMER (RTCCON |= 1 << 8)
#define DISABLE_TICK_TIMER (RTCCON &= ~(1 << 8))
#endif
