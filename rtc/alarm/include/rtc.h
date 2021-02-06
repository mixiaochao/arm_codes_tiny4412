#ifndef XCM_RTC_H_
#define XCM_RTC_H_

#include <lib.h>

#define INTP 			*((volatile u32 *)0x10070030) 
#define RTCCON 			*((volatile u32 *)0x10070040) 
#define TICCNT 			*((volatile u32 *)0x10070044) 
#define RTCALM 			*((volatile u32 *)0x10070050) 
#define ALMSEC 			*((volatile u32 *)0x10070054) 
#define ALMMIN 			*((volatile u32 *)0x10070058) 
#define ALMHOUR			*((volatile u32 *)0x1007005C) 
#define ALMDAY 			*((volatile u32 *)0x10070060) 
#define ALMMON 			*((volatile u32 *)0x10070064) 
#define ALMYEAR			*((volatile u32 *)0x10070068) 
#define BCDSEC 			*((volatile u32 *)0x10070070) 
#define BCDMIN 			*((volatile u32 *)0x10070074) 
#define BCDHOUR			*((volatile u32 *)0x10070078) 
#define BCDDAYWEEK 		*((volatile u32 *)0x10070080) 
#define BCDDAY 			*((volatile u32 *)0x1007007c) 
#define BCDMON 			*((volatile u32 *)0x10070084) 
#define BCDYEAR			*((volatile u32 *)0x10070088) 
#define CURTICCNT 		*((volatile u32 *)0x10070090)

typedef struct{
    u32 sec;    /* Seconds (0-60) */
    u32 min;    /* Minutes (0-59) */
    u32 hour;   /* Hours (0-23) */
    u32 mday;   /* Day of the month (1-31) */
    u32 mon;    /* Month (0-11) */
    u32 year;   /* Year - 1900 */
    u32 wday;   /* Day of the week (0-6, Sunday = 0) */
}rtctime_t;

extern u16  bin2bcd(u16 n);
extern u16  bcd2bin(u16 n);

extern void rtc_gettime(rtctime_t *t);
extern void rtc_settime(rtctime_t *t);
extern void rtc_set_alarm(rtctime_t *t);
extern void rtc_tic_irq_init(void);

extern void do_ticalarm(void);

#define RTCTIC_IRQID  77	
#define RTCALM_IRQID  76	

#endif
