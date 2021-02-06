#ifndef MILLET_LCD_H_
#define MILLET_LCD_H_

#include <common.h>

#define GPIOBASE 0x11400000

#define GPF0CON *((u32*)(GPIOBASE + 0x0180)) 
#define GPF1CON *((u32*)(GPIOBASE + 0x01a0)) 
#define GPF2CON *((u32*)(GPIOBASE + 0x01c0)) 
#define GPF3CON *((u32*)(GPIOBASE + 0x01e0)) 


#define CLKBASE 0x10030000

#define CLK_SRC_LCD0 *((u32*)(CLKBASE + 0xc234))
#define CLK_DIV_LCD  *((u32*)(CLKBASE + 0xc534))

#define LCDBASE 0x11C00000

#define VIDCON0 		*((u32*)(LCDBASE + 0x0000)) 
#define VIDCON1 		*((u32*)(LCDBASE + 0x0004)) 
#define VIDTCON0 		*((u32*)(LCDBASE + 0x0010)) 
#define VIDTCON1 		*((u32*)(LCDBASE + 0x0014)) 
#define VIDTCON2 		*((u32*)(LCDBASE + 0x0018)) 
#define VIDTCON3 		*((u32*)(LCDBASE + 0x001C)) 
#define WINCON0 		*((u32*)(LCDBASE + 0x0020)) 
#define SHADOWCON 		*((u32*)(LCDBASE + 0x0034)) 
#define VIDOSD0A 		*((u32*)(LCDBASE + 0x0040)) 
#define VIDOSD0B 		*((u32*)(LCDBASE + 0x0044)) 
#define VIDOSD0C 		*((u32*)(LCDBASE + 0x0048)) 
#define VIDW00ADD0B0 	*((u32*)(LCDBASE + 0x00A0)) 
#define VIDW00ADD1B0 	*((u32*)(LCDBASE + 0x00D0)) 
#define WINCHMAP2 	 	*((u32*)(LCDBASE + 0x003c))

#define LCDBLK_CFG 		*((u32*)(0x10010210))

extern void lcd_init();

#endif
