#ifndef LCD_H_
#define LCD_H_

#include <comm.h>

#define FRAMBUFFER0 0x52000000
#define FRAMBUFFER1 0x62000000
#define FRAMBUFFER2 0x63000000

extern void lcd_init(void);
extern void draw_point(int x, int y, int col);
extern void draw_point_page(int x, int y, int col,int ipage);
extern void draw_point1(int x, int y, int col);
extern void draw_point2(int x, int y, int col);
extern void clean_screen(int col);
extern void clean_screen_half(int col);
extern void flush_win1();
extern void flush_win2();
#define COL(R,G,B) ((R << 16) | (G << 8) | (B << 0))
#define LCDBLK_CFG	*((u32 *)0x10010210) 

#define GPF0CON 	*((u32 *)0x11400180) 
#define GPF1CON 	*((u32 *)0x114001A0) 
#define GPF2CON 	*((u32 *)0x114001C0) 
#define GPF3CON 	*((u32 *)0x114001E0) 

#define VIDCON0 	*((u32 *)0x11c00000) 
#define VIDCON1 	*((u32 *)0x11c00004) 
#define VIDCON2 	*((u32 *)0x11c00008) 
#define VIDCON3 	*((u32 *)0x11c0000C) 
#define VIDTCON0	*((u32 *)0x11c00010) 
#define VIDTCON1	*((u32 *)0x11c00014) 
#define VIDTCON2	*((u32 *)0x11c00018) 
#define VIDTCON3	*((u32 *)0x11c0001C) 
#define WINCON0 	*((u32 *)0x11c00020) 
#define WINCON1 	*((u32 *)0x11c00024) 
#define WINCON2 	*((u32 *)0x11c00028) 
#define WINCON3 	*((u32 *)0x11c0002C) 
#define WINCON4 	*((u32 *)0x11c00030) 
#define SHADOWCON	*((u32 *)0x11c00034) 
#define WINCHMAP2	*((u32 *)0x11c0003C)
#define VIDOSD0A 	*((u32 *)0x11c00040)
#define VIDOSD0B 	*((u32 *)0x11c00044)
#define VIDOSD0C 	*((u32 *)0x11c00048)
#define VIDOSD1A 	*((u32 *)0x11c00050)
#define VIDOSD1B 	*((u32 *)0x11c00054)
#define VIDOSD1C 	*((u32 *)0x11c00058)
#define VIDOSD1D 	*((u32 *)0x11c0005C)
#define VIDOSD2A 	*((u32 *)0x11c00060)
#define VIDOSD2B 	*((u32 *)0x11c00064)
#define VIDOSD2C 	*((u32 *)0x11c00068)
#define VIDOSD2D 	*((u32 *)0x11c0006C)
#define VIDOSD3A 	*((u32 *)0x11c00070)
#define VIDOSD3B 	*((u32 *)0x11c00074)
#define VIDOSD3C 	*((u32 *)0x11c00078)
#define VIDOSD4A 	*((u32 *)0x11c00080)
#define VIDOSD4B 	*((u32 *)0x11c00084)
#define VIDOSD4C 	*((u32 *)0x11c00088)
#define VIDW00ADD0B0 	*((u32 *)0x11c000A0)
#define VIDW00ADD1B0 	*((u32 *)0x11c000D0)

//#define VIDW01ADD0B0 	*((u32 *)0x11c000A8)
//#define VIDW01ADD1B0 	*((u32 *)0x11c000D8)

#define VIDW01ADD2		*((u32 *)0x11c00104)			
#define W1KEYCON0 		*((u32 *)0x11c00140)			
#define W1KEYCON1 		*((u32 *)0x11c00144)			

#define VIDW01ADD0B0 	*((u32 *)0x11c000A8)
#define VIDW01ADD1B0 	*((u32 *)0x11c000D8)


#define VIDW02ADD2		*((u32 *)0x11c00108)			
#define W2KEYCON0 		*((u32 *)0x11c00148)			
#define W2KEYCON1 		*((u32 *)0x11c0014c)			

#define VIDW02ADD0B0 	*((u32 *)0x11c000B0)
#define VIDW02ADD1B0 	*((u32 *)0x11c000E0)


#define CLK_SRC_LCD0	*((u32 *)0x1003c234)
#define CLK_DIV_LCD	*((u32 *)0x1003c534)

#endif
