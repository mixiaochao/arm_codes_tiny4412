#ifndef TIMER_H_ 
#define TIMER_H_

#include "common.h"

#define PWMBASE 0x139D0000

#define TCFG0  			*((u32 *)(PWMBASE + 0x0000)) 
#define TCFG1  			*((u32 *)(PWMBASE + 0x0004)) 
#define TCON   			*((u32 *)(PWMBASE + 0x0008)) 
#define TCNTB0 			*((u32 *)(PWMBASE + 0x000C)) 
#define TCMPB0 			*((u32 *)(PWMBASE + 0x0010)) 
#define TCNTO0 			*((u32 *)(PWMBASE + 0x0014)) 
#define TCNTB1 			*((u32 *)(PWMBASE + 0x0018)) 
#define TCMPB1 			*((u32 *)(PWMBASE + 0x001C)) 
#define TCNTO1 			*((u32 *)(PWMBASE + 0x0020)) 
#define TCNTB2 			*((u32 *)(PWMBASE + 0x0024)) 
#define TCMPB2 			*((u32 *)(PWMBASE + 0x0028)) 
#define TCNTO2 			*((u32 *)(PWMBASE + 0x002C)) 
#define TCNTB3 			*((u32 *)(PWMBASE + 0x0030)) 
#define TCMPB3 			*((u32 *)(PWMBASE + 0x0034)) 
#define TCNTO3 			*((u32 *)(PWMBASE + 0x0038)) 
#define TCNTB4 			*((u32 *)(PWMBASE + 0x003C)) 
#define TCNTO4 			*((u32 *)(PWMBASE + 0x0040)) 
#define TINT_CSTAT  		*((u32 *)(PWMBASE + 0x0044))

extern void timer4_init(int ms);
extern void do_timer4(void);
extern void timer4_start(void);

#define TIMER4 73 

#endif

