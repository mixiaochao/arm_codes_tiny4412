#ifndef LED_H_
#define LED_H_

#include <comm.h>

extern void led_init(void);
extern void led_on(int num);
extern void led_off(int num);

#define GPM4CON	*((u32 *)0x110002e0) 
#define GPM4DAT *((u32 *)0x110002e4)

#endif
