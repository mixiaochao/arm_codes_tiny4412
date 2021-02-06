#ifndef XCM_KEY_EINT_H_
#define XCM_KEY_EINT_H_

#include <lib.h>

extern void key_eint_init(void);
extern void do_keys(void);

#define KEY4INT 		64

#define GPX3CON			*((volatile u32 *)0x11000c60)
#define EXT_INT43CON		*((volatile u32 *)0x11000e0c)
#define EXT_INT43_FLTCON0	*((volatile u32 *)0x11000e98)
#define EXT_INT43_FLTCON1	*((volatile u32 *)0x11000e9c)
#define EXT_INT43_MASK		*((volatile u32 *)0x11000f0c)
#define EXT_INT43_PEND		*((volatile u32 *)0x11000f4c)


#endif
