#ifndef BUZZER_H_
#define BUZZER_H_

#include <comm.h>

#define GPD0CON 	*((u32 *)0x114000a0) 

#define TCFG0 		*((u32 *)0x139d0000) 
#define TCFG1 		*((u32 *)0x139d0004) 
#define TCON 		*((u32 *)0x139d0008) 
#define TCNTB0 		*((u32 *)0x139d000C) 
#define TCMPB0 		*((u32 *)0x139d0010) 
#define TCNTO0 		*((u32 *)0x139d0014) 
#define TCNTB1 		*((u32 *)0x139d0018) 
#define TCMPB1 		*((u32 *)0x139d001C) 
#define TCNTO1 		*((u32 *)0x139d0020) 
#define TCNTB2 		*((u32 *)0x139d0024) 
#define TCMPB2 		*((u32 *)0x139d0028) 
#define TCNTO2 		*((u32 *)0x139d002C) 
#define TCNTB3 		*((u32 *)0x139d0030) 
#define TCMPB3 		*((u32 *)0x139d0034) 
#define TCNTO3 		*((u32 *)0x139d0038) 
#define TCNTB4 		*((u32 *)0x139d003C) 
#define TCNTO4 		*((u32 *)0x139d0040) 
#define TINT_CSTAT 	*((u32 *)0x139d0044)  


extern void buzzer_init(u32 num);

#endif
