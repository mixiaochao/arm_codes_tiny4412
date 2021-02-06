#ifndef XCM_KEY_H_
#define XCM_KEY_H_

#include <lib.h>

#define GPX3BASE 0x11000000
#define GPX3CON  *((volatile u32 *)(GPX3BASE + 0xc60))
#define GPX3DAT  *((volatile u32 *)(GPX3BASE + 0xc64))

extern void key_init(void);
extern u32 scanf_keys(void);

#endif
