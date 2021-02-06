#ifndef XCM_WDT_H_
#define XCM_WDT_H_

#include <lib.h>

extern void do_wdt_timer(void);
extern void wdt_timer_init(u32 ms);

#define WTCON 		*((volatile u32 *)0x10060000) 
#define WTDAT 		*((volatile u32 *)0x10060004) 
#define WTCNT 		*((volatile u32 *)0x10060008) 
#define WTCLRINT	*((volatile u32 *)0x1006000C)

#define WDTID		75

#endif
