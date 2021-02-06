#ifndef gobang_H_
#define gobang_H_

#define SZ 	32
#define WAITH 	15

#define WRITE 	1
#define BLACK	2

//extern static int data[WAITH][WAITH] = {0};
extern int  Win_Y_N(int X,int Y,int flag_wr_or_bl);
extern void tp_data_deal_with(int x,int y,int flag_wr_or_bl);
extern void gobang_back_clean();

extern void again_time_clear();
extern void again_time_clear_n();
extern void gobang_menu(int x,int y);

extern void change_backgroud();
#endif

