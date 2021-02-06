#include <gobang.h>
#include <display.h>
#include <iic.h>
#include <comm.h>
#include <irq.h>
#include <tp.h>
#include <lcd.h>
#include <timer.h>
#include <uart.h>
#include <buzzer.h>

#define SZ 	32
#define WAITH 	15

#define WRITE 	1
#define BLACK	2

int flag = 1;
static int data[WAITH][WAITH] = {};
int flag_re = 0;
int wh_score = 0;
int bl_score = 0;
int again_time_flag=0;
int gobang_begin  = 0;
int gobang_back = 0;
int rollback[WAITH*WAITH] = {};
int sqnum = 0;

/*
 *   函数功能：判断当前棋手的输赢
 *
 *   参    数：@X:	      当前点列坐标对应数组的列下标
 *	       @Y:            当前点行坐标对应数组的行下标
 *	       @flag_wr_or_bl:当前若是白方走棋完值为1，当前若是黑方走完棋值为2
 *
 *   返回  值  ：若白方赢返回1，若黑方赢返回2
 *   	     ：不赢返回0
 *
 * */

int  Win_Y_N(X,Y,flag_wr_or_bl)
{
	/*放向参数定义*/
	int up_down = 1;
	int left_right = 1;
	int rightdown_leftup = 1;
	int leftdown_rightup = 1;

	int i = 0;
	/**************判断上下方向是否有连棋***************/
	for (i = 1;i < 5;i++) 	
	{
		if ((Y + i < WAITH) && (data[X][Y + i] == flag_wr_or_bl))
			up_down++;
		else 
			break;
	}
	for (i = 1;i < 5;i++)  	
	{
		if((Y - i) && data[X][Y - i] == flag_wr_or_bl)
			up_down++;
		else
			break;
	}
	if (up_down >= 5)
		return flag_wr_or_bl;
	/**************判断左右方向是否有连棋***************/
	for(i = 1;i < 5;i++)  
	{
		if(X + i < WAITH && data[X + i][Y] == flag_wr_or_bl)
			left_right++;
		else
			break;
	} 
	for (i = 1;i < 5;i++) 
	{
		if (X - i > 0 && data[X - i][Y] == flag_wr_or_bl)
			left_right++;
		else
			break;
	}
	if (left_right >= 5)
		return flag_wr_or_bl;
	/**************判断右下左上对角方向是否有连棋******************/
	for (i = 1;i < 5;i++)
	{
		if (X + i < WAITH && Y + i < WAITH && (data[X + i][Y + i] == flag_wr_or_bl))
			rightdown_leftup++;
		else
			break;
	}
	for (i = 1;i < 5;i++)
	{
		if (X - i > 0 && Y - i > 0 && (data[X - i][Y - i] == flag_wr_or_bl))
			rightdown_leftup++;
		else
			break;
	}
	if (rightdown_leftup >= 5)
	{
		return flag_wr_or_bl;
	}
	/*************判断左下右上对角方向是否有连棋************************/
	for (i = 1;i < 5;i++)
	{
		if (X - i > 0 && Y + i < WAITH && (data[X - i][Y + i] == flag_wr_or_bl))
			leftdown_rightup++;
		else
			break;
	}
	for (i = 1;i < 5;i++)
	{
		if (X + i < WAITH && Y -i > 0 && (data[X + i][Y - i] == flag_wr_or_bl))
			leftdown_rightup++;
		else 
			break;
	}
	if (leftdown_rightup >= 5)
	{
		return flag_wr_or_bl;
	}	
	return 0;
}

static int date_change_x(int x)
{
	if(x>=165 && x <= 195)
	{
		return 0;
	}else if(x >195 && x <= 225)
	{
		return 1;
	}else if(x >225 && x <= 255)
	{
		return 2;
	}else if(x > 255 && x <= 285)
	{
		return 3;
	}else if(x > 285 && x <= 315)
	{
		return 4;
	}else if(x > 315 && x <= 345)
	{
		return 5;
	}else if(x > 345 && x <= 375)
	{
		return 6;
	}else if(x > 375 && x <= 405)
	{
		return 7;
	}else if(x > 405 && x<= 435)
	{
		return 8;
	}else if(x > 435 && x<= 465)
	{
		return 9;
	}else if(x > 465 && x<= 495)
	{
		return 10;
	}else if(x > 495 && x<= 525)
	{
		return 11;
	}else if(x > 525 && x <= 555)
	{
		return 12;
	}else if (x > 555 && x <= 585)
	{
		return 13;
	}else if(x > 585 && x <= 615)
	{
		return 14;
	}else
	{
		return 0xffff;
	}
}

static int date_change_y(int y)
{
	if(y >= 15 && y <= 45)
	{
		return 0;	
	}else if (y > 45 && y <= 75)
	{
		return 1;
	}else if (y > 75 && y <= 105)
	{
		return 2;
	}else if(y > 105 && y <= 135)
	{
		return 3;
	}else if (y > 135 && y <= 165)
	{
		return 4;
	}else if (y > 165 && y <= 195)
	{
		return 5;
	}else if (y > 195 && y <= 225)
	{
		return 6;
	}else if (y > 225 && y <= 255)
	{
		return 7;
	}else if (y > 255 && y <= 285)
	{
		return 8;
	}else if (y > 285 && y <= 315)
	{
		return 9;
	}else if (y > 315 && y <= 345)
	{
		return 10;
	}else if (y > 345 && y <= 375)
	{	
		return 11;
	}else if (y > 375 && y <= 405)
	{
		return 12;
	}else if (y > 405 && y <= 435)
	{
		return 13;
	}else if (y > 435 && y <= 465)
	{
		return 14;
	}
	else{
		return 0xffff;
	}
}

void draw_point_draw(int X,int Y,int colour) //画白点
{
	int i = 0;
	int j = 0;
	int Cx = (180 + 30*X);
	int Cy = (30 + 30*Y);
	int r = 10;
	
	for (i = Cx - r;i < Cx + r;i++)
	{		
		for(j = Cy -r;j < Cy +r;j++)
		{
			if(((i -Cx)*(i - Cx) + (j -Cy)*(j - Cy)) <= r*r)
			{
				if(colour == 1)
				{
					draw_point2(i,j,COL(255,255,255));
				}else if(colour == 2) {
					draw_point2(i,j,COL(0,0,0));
				}else if(colour == 3)
				{	
					draw_point2(i,j,COL(0,255,0));
				}

			}
		}
	}
	buzzer_di();

}
void tp_data_deal_with(int x,int y,int flag_wr_or_bl)
{
	int X = 0;
	int Y = 0;
	int tem_win_y_n = 0;	

	if (x >= 165 && x <= 165 + 30 * 15 && y >= 15 && y <= 15 + 30 * 15)
	{
		X = date_change_x(x);
		Y = date_change_y(y);

		uprintf  ("(%d,%d)\n",X,Y);
		//uprintf  ("rollback[%d] = %x\n",sqnum,rollback[sqnum]);

		if(( data[X][Y] == WRITE) || (data[X][Y] == BLACK) )
		{
		
			if(flag == 1)
			{
				flag = 2;
			}else if(flag == 2)
			{
				flag = 1;
			}
		
			uprintf("has a point\n");;//提示该处已有棋，请重新走棋。
		}else {
			data[X][Y] = flag_wr_or_bl;
			rollback[sqnum] =  0x00 | X << 8 | Y << 0; 

			//在 (X * 30 + 180 ,Y * 30 + 30) 画点
			if (data[X][Y] == WRITE) {
				draw_point_draw(X, Y, WRITE); //画白点
				uprintf ("白方>>>>>>\n");	
			}else if (data[X][Y] == BLACK)
			{
				draw_point_draw(X,Y,BLACK); //画黑点
				uprintf ("黑方>>>>>\n");
			}

			if(flag_re != 0)
				flag_re = 0;

			uprintf("(%d,%d)\n",X,Y);
			uprintf("rollback[%d] = %x\n",sqnum,rollback[sqnum]);
			sqnum++;
		}
	}else {
		//提示超出棋盘范围，请重新走棋	
		uprintf("please try again\n");
	}
	//判断输赢
	tem_win_y_n = Win_Y_N(X,Y,flag_wr_or_bl);

	if (tem_win_y_n == flag_wr_or_bl) {

		//赢，输出恭喜画面
		switch(tem_win_y_n)	
		{
			case WRITE:
				uprintf  ("--------------白方赢------------------\n");
				display_gobangscore(610,410,2);
				wh_score++;
				display_wh_bl_score(660,50,2,wh_score);
				display_again_timer(300,200);
				again_time_flag = 1;
				gobang_begin  = 0;
				 timer4_init(1000);
				//白方赢	
         			//恭喜白方				
				//提示是否下一局
				//若是则清空棋盘，清空数组
				//若不则给出game over 画面
				break;
			case BLACK:
				uprintf ("---------------------黑方赢---------------\n");
				display_gobangscore(610,410,1);
				bl_score++;
				display_wh_bl_score(585,50,1,bl_score);
				display_again_timer(300,200);
				again_time_flag = 1;
				gobang_begin  = 0;
				 timer4_init(1000);
				//黑方赢
				//恭喜黑方
				//提示是否下一局
				//若是则清空棋盘，清空数组
				//若不则给出game over 画面
				break;
			default:	
				break;
		}

	}else if (tem_win_y_n == 0)
	{
		;//提示另一方走棋
	}	

}
void gobang_back_clean()
{
	int i ,j;
	for(i = 0;i<15;i++)
		for(j = 0;j<15;j++)
			data[i][j] = 0;
		//flush_win2();
		//flush_win1();
	//clean_lcd(800,480,COL(192,86,0),0,1);
}

void gobang_back_clean_r(int s)
{
	int i = s;

	for (i=s; i>=0; i--)
		rollback[i] = 0;
}

void again_time_clear()
{
	flush_win2();
	flush_win1();
	clean_lcd(165,15,615,465,0x00ff00,2,0);
	gobang_back_clean();//清数据 
	gobang_back_clean_r(sqnum);
	gobang_all_display();
}

void again_time_clear_n()
{
	flush_win2();
	flush_win1();
	gobang_back_clean();
	gobang_back_clean_r(sqnum);
	gobang_all_display();
	
	wh_score = 0;//白方比分清零
	bl_score = 0;	
}

static void Screen(int i)
{

	VIDW00ADD0B0 = 0x53000000+800*480*4*(8+i);
	VIDW00ADD1B0 = 0x53000000+800*480*4*(8+i) + VIDOSD0C*4;
}

void change_backgroud()
{
	static int i = 0;
	i++;
	if(i == 5)
	{
		i = 0;
		VIDW00ADD0B0 = 0x53000000+800*480*4*1;
		VIDW00ADD1B0 = 0x53000000+800*480*4*1 + VIDOSD0C*4;

	}
	if(i != 0)
		Screen(i);
	gobang_diaplay(100,100,0,0);//画棋盘
	display_gobang_oper(650,30);//显示开始 悔棋 背景 新局 退出	
	display_img(0,0,0,0);//显示五子棋三个字
}


void gobang_menu(int x,int y)
{

		if(x>=675&&x<=748&&y>=120&&y<=153)//开始按钮
		{
			gobang_begin  = 1;
			flag = 1;
			buzzer_di();
			sqnum = 0;
		}

		//悔棋按钮
		if(x>=675&&x<=748&&y>=180&&y<=213) {
			if (sqnum > 0){
				sqnum = sqnum - 1;
				int ly = rollback[sqnum] & 0xff;
				int lx = (rollback[sqnum] >> 8) & 0xff;
			
				uprintf("sqnum=%d\n",sqnum);
				uprintf("lx=%d,ly=%d\n",lx,ly);
				data[lx][ly] = 0;
				draw_point_draw(lx,ly,3); //清棋子
				buzzer_di();

				//flag_re = flag;
				if (flag == 1)
					flag = 2;
				else if (flag == 2)
					flag = 1;
			}
		}

		//退出按钮
		
		if(x>=675&&x<=748&&y>=360&&y<=393)//退出按钮
		{
			gobang_back = 1;
			flush_win2();
			flush_win1();
			gobang_back_clean();
			buzzer_di();
			gobang_begin = 0;
			sqnum = 0;
		}

		if(x>=675&&x<=748&&y>=300&&y<=333)//新局
		{
			gobang_begin  = 0;
			again_time_clear_n();
			buzzer_di();
			sqnum = 0;

		}
		if(x>=675&&x<=748&&y>=243&&y<=273)//背景
		{
			change_backgroud();
			buzzer_di();
		}

		if(x>=320&&x<=360&&y>=260&&y<=297&& again_time_flag==1)//再来一局 是
		{
			again_time_flag  = 0;
			gobang_begin  = 0;
			again_time_clear();	
			buzzer_di();
			sqnum = 0;
		}
		
		if(x>=440&&x<=480&&y>=260&&y<=297&& again_time_flag ==1)
		{
			again_time_flag = 0;
			gobang_begin  = 0;
			again_time_clear_n();
			buzzer_di();
			sqnum = 0;
		}
		
		if(gobang_begin ==1)//游戏开始
		{
			if(x != 0 && y != 0)
			{	
				if (x >= 165 && x <= 165 + 30 * 15 && y >= 15 && y <= 15 + 30 * 15)
				{
					//if (flag_re == 0){
						flag++;
						if(flag == 3)
							flag = 1;
					//}else
					//	flag = flag_re;
				}
			}
			uprintf("----------Main  GOBANG---------------------------\n");
			uprintf("|*********************************************|\n");
			uprintf("----------------flag = %d\n",flag);
			if(flag%2 == 0)
			{
				uprintf("white--------------------------->\n");	
				tp_data_deal_with(x,y,1);
				uprintf("white----------------end------->\n");	
			}else if (flag%2 != 0)
			{
				uprintf("<-----------------------------black\n");
				tp_data_deal_with(x,y,2);
				uprintf("<---end---------------------black\n");
			}
			uprintf("|*********************************************|\n\n");	
		}	

}

