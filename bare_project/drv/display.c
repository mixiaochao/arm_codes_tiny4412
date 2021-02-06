#include <display.h>
#include <lcd.h>
#include <font12_22.h>
#include <uart.h>
#include <zk.h>
#include <font8_16.h>
#include <wdt.h>
extern int wdt_time;

static void display_dat(int x,int y,char *dat,int row,int col,int color,int win,int ipage)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0;i < row;i++)
	{
		for(j = 0; j < (col/8);j++)
		{
			for(k = 0; k < 8; k++)
			{
				if( ((*dat)<<k)&0x80 )
				{
					if(win == 0)
						draw_point_page(x+j*8+k,y+i,color,ipage);	
					if(win == 1)	
						draw_point1(x+j*8+k,y+i,color);
					if(win == 2)	
						draw_point2(x+j*8+k,y+i,color);

				}
			}
			dat++;
		}
	}
}
/*--------------------------display_hanzi------------------------------------*/

//extern unsigned char time_hanzi3241[1804];
extern unsigned char time_hanzi3233[1584];
void display_hanzi(int x,int y,int num,int color,int win,int ipage)
{
	display_dat(x,y,(void *)(time_hanzi3233+4*33*num),33,32,color,win,ipage);
}

/*---------------------display_ASCII && string---------------------------------*/
static void display_numdat(int x,int y,char *dat,int row,int col,int color,int win,int ipage)
{
	unsigned short tmp;
	int i,j;
	for(i = 0; i < row;i++)
	{
		tmp = (dat[2*i]<<8)|dat[2*i+1];
		for(j = 0;j < col;j++)
		{
			if((tmp<<j)&0x8000)
			{
				if(win == 0)
					draw_point_page(x+j,y+i,color,ipage);	
				if(win == 1)	
					draw_point1(x+j,y+i,color);	
				if(win == -1)
					draw_point(x+j,y+i,color);
			}
		}
	}
}

extern unsigned char font12_22[11264];

void display_ASCII(int x,int y,char ch,int color,int win,int ipage)
{
	int i = (int)ch;
	display_numdat(x,y,(void *)(font12_22+2*22*i),22,12,color,win,ipage);
}

extern unsigned char font8_16[4096];

void display_ASCII8_16(int x,int y,char ch,int color,int win,int ipage)
{
	int i = (int)ch;
	display_dat(x,y,(void *)(font8_16+1*16*i),16,8,color,win,ipage);
}

void display_string(int x,int y,char *str,int color,int win,int ipage)
{
	int i = 0;
	int m = 0;
	for(i = 0; str[i] != '\0';i++)
	{
		m = (int)(str[i]);
		display_numdat(x+i*12,y,(void *)(font12_22+2*22*m),22,12,color,win,ipage);
	}
}

/*------------------------display big numble-----------------------------*/

void display_4897num(int x,int y,int num,int color,int win,int ipage)
{
	display_dat(x,y,(void *)num4897[num],97,48,color,win,ipage);
}

void display_2448num(int x,int y,int num,int color,int win,int ipage)
{
        display_dat(x,y,(void *)(num2448+3*48*num),48,24,color,win,ipage);
}

extern unsigned char num2435[1260];
void display_2435num(int x,int y,int num,int color,int win,int ipage)
{
	display_dat(x,y,(void *)(num2435+3*35*num),35,24,color,win,ipage);
}

/*----------------------clean_LCD-----------------------------------------*/
void clean_lcd(int x1,int y1,int x2,int y2,int color,int win,int ipage)
{
	int i = 0;
	int j = 0;
	for(i = x1; i < x2;i++)
		for(j = y1; j < y2;j++)
		{
			if(win == 0)
				draw_point_page(i,j,color,ipage);
			if(win == 1)
				draw_point1(i,j,color);
			if(win == 2)
				draw_point2(i,j,color);

		}
}
void draw_line(int x,int y,int len,int wide,int color,int win,int ipage)
{
	int i;
	int j;
	for(i = x;i < len+x;i++)
		for(j = y; j < wide+y; j++)
		{
			if(win == 0)
				draw_point_page(i,j,color,ipage);	
			if(win == 1)
				draw_point1(i,j,color);
			if(win == -1)
				draw_point(i,j,color);
		}
}

#define RAW 22
#define HAN 12

void lcd_stdout(int c)
{
	const unsigned char *curr = NULL;	
	int i,j;
	unsigned short tmp;

	static int x = 0;
	static int y = 0;

	if(c == '\n')
	{
		y += RAW;
		x = 0;

		if(y > 457){
			clean_screen(COL(0,0,0));
			y = 0;
			x = 0;
		}
		return;
	}
	else if(c == '\r')
		return;

	curr = font12_22 + c*RAW*2;
	for(i = 0; i < RAW; i++){
		tmp = (curr[2*i] << 8) | curr[2*i+1];	
		for(j = 0; j < HAN; j++){
			if((tmp<<j)&0x8000){
				draw_point(x+j, y+i, COL(255,255,255));
			}
		}
	} 

	x += 14;
	if(x > 783){
		x = 0;
		y += RAW;
		if(y > 457){
			clean_screen(COL(0,0,0));
			y = 0;
		}
	}
}



/*------------------画棋盘------------------------------*/
void gobang_diaplay()
{
	int i = 0;
	int j = 0;

	for(j=0; j<480; j++)
	{
		for(i =0; i<800; i++)
		{
			if(j > 0 && (j%30==0)&&(i>=180)&&(i<600))	
				//draw_point_page(i, j, COL(0,0,0),1);
				draw_point1(i,j,0);
			if(i>150&&(i%30==0)&&(i<620)&&(j>=30)&&(j<=450))
				//draw_point_page(i, j, COL(0,0,0),1);	
				draw_point1(i,j,0);	
		}
	}
}

/*------------------画五子棋-三个字-----------------------------*/
void display_img(int x,int y,int color,int win)
{
	display_dat(30,40,(void *)gobang_img,400,104,color,1,1);	
}



//extern char bl_wh_win[3072]；
/*------------------显示黑白胜  -三个字-----------------------------*/
void display_gobangscore(int x,int y,int colour)
{
	int i = 0;
	if(colour==1)
	{
		for(i=0;i<3;i++)
		{
			display_dat(x+64*i, y, (void *)(bl_wh_win+8*64*i),64,64,0,1,1);
		}
	}
	if(colour==2)
	{
		for(i=3;i<6;i++)
			display_dat(x+64*(i-3),y,(void *)(bl_wh_win+8*64*i),64,64,0xffffff,1,1);
	}	

}
/*------------------显示分数-三位----------------------------*/

void display_wh_bl_score(int x,int y,int colour,int score)
{

	int unit;
	int ten;
	int hundred;
	unit = score%10;
	ten  = score/10%10;
	hundred=score/100;	
	if(colour==1)
	{
		display_dat(x+98, y+20, (void *)(wh_bl_score+2*33*10),33,16,COL(192,86,0),1,1);
		display_dat(x+80, y+20, (void *)(wh_bl_score+2*33*10),33,16,COL(192,86,0),1,1);
		display_dat(x+62, y+20, (void *)(wh_bl_score+2*33*10),33,16,COL(192,86,0),1,1);

		display_dat(x+98, y+20, (void *)(wh_bl_score+2*33*unit),33,16,0,1,1);
		display_dat(x+80, y+20, (void *)(wh_bl_score+2*33*ten),33,16,0,1,1);
		display_dat(x+62, y+20, (void *)(wh_bl_score+2*33*hundred),33,16,0,1,1);
	}
	if(colour==2)
	{
		display_dat(x+98, y+20, (void *)(wh_bl_score+2*33*10),33,16,COL(192,86,0),1,1);
		display_dat(x+80, y+20, (void *)(wh_bl_score+2*33*10),33,16,COL(192,86,0),1,1);
		display_dat(x+62, y+20, (void *)(wh_bl_score+2*33*10),33,16,COL(192,86,0),1,1);

		display_dat(x+98, y+20, (void *)(wh_bl_score+2*33*unit),33,16,COL(255,255,255),1,1);
		display_dat(x+80, y+20, (void *)(wh_bl_score+2*33*ten),33,16,COL(255,255,255),1,1);
		display_dat(x+62, y+20, (void *)(wh_bl_score+2*33*hundred),33,16,COL(255,255,255),1,1);    
	}		
}


/*------------------开始 新局 退出 -三位----------------------------*/
void display_gobang_oper(int x,int y)
{
	int i = 0;

	display_dat(x+5, y, (void *)(gobang_oper+4*33*0),33,32,COL(0,0,0),1,1);
	display_dat(x+50, y, (void *)(gobang_oper+4*33*1),33,32,COL(255,0,0),1,1);
	display_dat(x+80, y, (void *)(gobang_oper+4*33*2),33,32,COL(255,255,255),1,1);

	display_dat(x+25, y+30*3, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+42, y+30*3, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+66, y+30*3, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);

	for(i = 5;i < 7;i++)
	{
		display_dat(x+30*(i-4), y+30*3, (void *)(gobang_oper+4*33*(i-2)),33,32,COL(255,0,0),1,1);	
	}

	display_dat(x+25, y+30*5, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+42, y+30*5, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+66, y+30*5, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);

	for(i = 7;i < 9;i++)
		display_dat(x+30*(i-6), y+30*5, (void *)(gobang_oper+4*33*(i-2)),33,32,COL(255,0,0),1,1);

	display_dat(x+25, y+30*7, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+42, y+30*7, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+66, y+30*7, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	for(i = 9;i < 11;i++)
		display_dat(x+30*(i-8), y+30*7, (void *)(gobang_oper+4*33*(i-2)),33,32,COL(255,0,0),1,1);
	display_dat(x+25, y+30*9, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+42, y+30*9, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+66, y+30*9, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	for(i = 11;i < 13;i++)
		display_dat(x+30*(i-10), y+30*9, (void *)(gobang_oper+4*33*(i-2)),33,32,COL(255,0,0),1,1);

	display_dat(x+25, y+30*11, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+42, y+30*11, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	display_dat(x+66, y+30*11, (void *)(gobang_oper+4*33*13),33,32,COL(0,0,255),1,1);
	for(i = 13;i < 15;i++)
		display_dat(x+30*(i-12), y+30*11, (void *)(gobang_oper+4*33*(i-2)),33,32,COL(255,0,0),1,1);


}

/*------------------再来一局----------------------------*/
void display_again_timer(int x,int y)
{
	int i;
	for(i = 0;i < 4;i++)
		display_dat(x+56*i, y, (void *)(again_time+7*56*i),56,56,COL(12,128,0),2,1);

	display_dat(x+20, y+60, (void *)(yes_or_no),37,40,COL(12,128,0),2,1);
	display_dat(x+140, y+60, (void *)(yes_or_no+5*37),37,40,COL(12,128,0),2,1);

}


void gobang_all_display()
{
	gobang_diaplay();//画棋盘
	display_gobang_oper(650,30);//显示开始 悔棋 背景 新局 退出	
	display_img(0,0,0,0);//显示五子棋三个字


}

void ad_clean_lcd(int x,int y,int count,int colour,int win,int page)
{   
	int i; 
	int j;
	
	for(i = 0; i < 48;i++)
    	{
		for(j = 0;j < (24 * count);j++)
        {
			if(win == 0)
			{
				draw_point_page(x + j,y + i,colour,page);
            }else if(win == 1)
			{
                   ;
            }
        }
	}

}

