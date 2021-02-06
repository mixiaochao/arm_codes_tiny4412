#ifndef WDT_H_
#define WDT_H_

#include <comm.h>

extern void wdt_init(int ms);

#define WTCON 		*((u32 *)0x10060000) 
#define WTDAT 		*((u32 *)0x10060004) 
#define WTCNT 		*((u32 *)0x10060008) 
#define WTCLRINT 	*((u32 *)0x1006000C) 

#endif
