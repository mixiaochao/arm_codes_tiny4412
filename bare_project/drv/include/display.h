#ifndef DISPLAY_H_
#define DISPLAY_H_

extern void display_hanzi(int x,int y,int num,int color,int win,int ipage);
extern void display_ASCII(int x,int y,char ch,int color,int win,int ipage);
extern void display_ASCII8_16(int x,int y,char ch,int color,int win,int ipage);
extern void display_string(int x,int y,char *str,int color,int win,int ipage);

extern void display_4897num(int x,int y,int num,int color,int win,int ipage);
extern void display_2448num(int x,int y,int num,int color,int win,int ipage);


extern void display_2435num(int x,int y,int num,int color,int win,int ipage);
extern void clean_lcd(int x1,int y1,int x2,int y2,int color,int win,int ipage);
extern void draw_line(int x,int y,int len,int wide,int color,int win,int ipage);
extern void lcd_stdout(int c);

extern void display_img(int x,int y,int color,int win);
extern void gobang_diaplay() ;

extern void display_gobangscore(int x,int y,int colour);
extern void display_wh_bl_score(int x,int y,int colour,int score);

extern void display_gobang_oper(int x,int y);
extern void display_again_timer(int x,int y);
extern void gobang_all_display();


extern void ad_clean_lcd(int x,int y,int count,int colour,int win,int page);

#endif
