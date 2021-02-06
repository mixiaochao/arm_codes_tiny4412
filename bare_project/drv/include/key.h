#ifndef KEY_H_
#define KEY_H_

#include <comm.h>

#define GPX3CON			*((u32 *)0x11000c60) 
#define EXT_INT43CON		*((u32 *)0x11000e0c)
#define EXT_INT43_FLTCON0	*((u32 *)0x11000e98)
#define EXT_INT43_FLTCON1	*((u32 *)0x11000e9c)
#define EXT_INT43_MASK		*((u32 *)0x11000f0c)
#define EXT_INT43_PEND		*((u32 *)0x11000f4c)

extern void eint_key(void);

#endif
