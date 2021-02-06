#ifndef MILLET_IRQ_H_
#define MILLET_IRQ_H_

#include <common.h>

#define GPX3CON			  *((u32 *)0x11000c60) 
#define EXT_INT43_CON 	  *((u32 *)0x11000E0C) 
#define EXT_INT43_FLTCON0 *((u32 *)0x11000E98) 
#define EXT_INT43_FLTCON1 *((u32 *)0x11000E9c) 
#define EXT_INT43_MASK 	  *((u32 *)0x11000F0C) 
#define EXT_INT43_PEND    *((u32 *)0x11000F4C) 

#define KEY_IRQ 		  64 
#define LEV 		      0 

extern void key_init(void);

#endif
