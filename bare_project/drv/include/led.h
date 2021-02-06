#ifndef LED_H_
#define LED_H_

#include <comm.h>

#define GPM4CON  *((u32 *)0x110002E0)
#define GPM4DAT  *((u8 *)0x110002E4)

#define GPM40_out  (1<<(0*4))
#define GPM41_out  (1<<(1*4))
#define GPM42_out  (1<<(2*4))
#define GPM43_out  (1<<(3*4))

extern void led_init();
extern void led_on(int num);
extern void led_off(int num);
extern void all_led_on();
extern void all_led_off();
extern void led_control(int x,int y);
#endif
