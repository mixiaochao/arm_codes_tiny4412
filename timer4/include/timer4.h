#ifndef XCM_TIIMER_H_
#define XCM_TIIMER_H_

#include <lib.h>

#define TCFG0 		*((volatile u32 *)0x139d0000)
#define TCFG1 		*((volatile u32 *)0x139d0004)
#define TCON 		*((volatile u32 *)0x139d0008) 
#define TCNTB0 		*((volatile u32 *)0x139d000C) 
#define TCMPB0 		*((volatile u32 *)0x139d0010) 
#define TCNTO0 		*((volatile u32 *)0x139d0014) 
#define TCNTB1 		*((volatile u32 *)0x139d0018) 
#define TCMPB1 		*((volatile u32 *)0x139d001C) 
#define TCNTO1 		*((volatile u32 *)0x139d0020) 
#define TCNTB2 		*((volatile u32 *)0x139d0024) 
#define TCMPB2 		*((volatile u32 *)0x139d0028) 
#define TCNTO2 		*((volatile u32 *)0x139d002C) 
#define TCNTB3 		*((volatile u32 *)0x139d0030) 
#define TCMPB3 		*((volatile u32 *)0x139d0034) 
#define TCNTO3 		*((volatile u32 *)0x139d0038) 
#define TCNTB4 		*((volatile u32 *)0x139d003C) 
#define TCNTO4 		*((volatile u32 *)0x139d0040) 
#define TINT_CSTAT 	*((volatile u32 *)0x139d0044) 

extern void do_timer4(void);
extern void timer4_init(u32 ms);

#endif
