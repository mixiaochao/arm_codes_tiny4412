#ifndef MILLET_LCD_H_
#define MILLET_LCD_H_

#include <lib.h>

#define GPF0CON 		*((volatile u32 *)0x11400180)
#define GPF1CON 		*((volatile u32 *)0x114001a0)
#define GPF2CON 		*((volatile u32 *)0x114001c0)
#define GPF3CON 		*((volatile u32 *)0x114001e0)

#define LCDBLK_CFG 		*((volatile u32 *)0x10010210)

#define CLK_SRC_LCD0	*((volatile u32 *)0x1003c234)
#define CLK_DIV_LCD		*((volatile u32 *)0x1003c534)


#define LCDBASE 0x11C00000

#define VIDCON0 		*((volatile u32 *)(0x0000+LCDBASE)) 
#define VIDCON1 		*((volatile u32 *)(0x0004+LCDBASE))
#define VIDCON2 		*((volatile u32 *)(0x0008+LCDBASE))
#define VIDCON3 		*((volatile u32 *)(0x000C+LCDBASE))
#define VIDTCON0		*((volatile u32 *)(0x0010+LCDBASE))
#define VIDTCON1		*((volatile u32 *)(0x0014+LCDBASE))
#define VIDTCON2		*((volatile u32 *)(0x0018+LCDBASE))
#define WINCON0 		*((volatile u32 *)(0x0020+LCDBASE))
#define SHADOWCON		*((volatile u32 *)(0x0034+LCDBASE))
#define WINCHMAP2		*((volatile u32 *)(0x003C+LCDBASE))
#define VIDOSD0A 		*((volatile u32 *)(0x0040+LCDBASE))
#define VIDOSD0B 		*((volatile u32 *)(0x0044+LCDBASE))
#define VIDOSD0C 		*((volatile u32 *)(0x0048+LCDBASE)) 
#define VIDW00ADD0B0 	*((volatile u32 *)(0x00A0+LCDBASE)) 
#define VIDW00ADD1B0 	*((volatile u32 *)(0x00D0+LCDBASE)) 

#define WINCON1  		*((volatile u32 *)0x11c00024)
#define VIDOSD1A 		*((volatile u32 *)0x11c00050) 
#define VIDOSD1B 		*((volatile u32 *)0x11c00054)
#define VIDOSD1C 		*((volatile u32 *)0x11c00058) 
#define VIDOSD1D 		*((volatile u32 *)0x11c0005C)
#define VIDW01ADD0B0 		*((volatile u32 *)0x11c000A8)
#define VIDW01ADD1B0		*((volatile u32 *)0x11c000d8)
#define VIDW01ADD2		*((volatile u32 *)0x11c00104)
#define	W1KEYCON0		*((volatile u32 *)0x11C00140)
#define	W1KEYCON1		*((volatile u32 *)0x11c00144)

#define FRAMBUFFER0 0x60000000
#define FRAMBUFFER1 0x66000000

extern void lcd_init(void);
extern void draw_point(int x, int y, int r, int g, int b);

#define COL(r,g, l)  ((r << 16) | (g << 8) | (l))
#endif
