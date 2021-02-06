#ifndef XCM_LED_H_
#define XCM_LED_H_

#include <lib.h>

#define GPM4BASE 0x11000000
#define GPM4CON  *((volatile u32 *)(GPM4BASE+0x2e0))
#define GPM4DAT  *((volatile u32 *)(GPM4BASE+0x2e4))

extern void led_init(void);
extern void led_on(u32 num);
extern void led_off(u32 num);

#endif
