#include <iic.h>
#include <comm.h>
#include <irq.h>
#include <tp.h>
#include <timer.h>
#include <uart.h>
#define SZ 32

int fst_point_flag = 1;
int points = 0;
int coordinate[2][2]; //coordinate[0][0] = x0, [0][1] = y0;

/*中断处理函数：用于以主收模式读取触摸屏控制模块处理后的数据*/
void do_tp(void)
{
		//	int i;
		int x,y;
		points = 0;
		char data[SZ];

		EXT_INT41_PEND = EXT_INT41_PEND;

		if (read_data(data, sizeof(data)) == -2) 
		{
				if (read_data(data, sizeof(data)) == -2)
				{
						//printf("no ack\n");	
						return;
				}
		}

		if (data[2] <= 0)
				return;
	//	if(data[2] >= 2)
			points = data[2];//获取触摸点数
			
		x = ((data[3]&0xf)<<8) | data[4];
		y = ((data[5]&0xf)<<8) | data[6];

		if(x >= 0 && x <= 799 && y >= 0 && y <= 479 ){

			if(fst_point_flag){
				coordinate[0][0] = coordinate[1][0] = x;
				coordinate[0][1] = coordinate[1][1] = y;
			//	uprintf("down (%d, %d)\n", coordinate[0][0],
			//					coordinate[0][1]);
				fst_point_flag = 0;
			}

			coordinate[1][0] = x;
			coordinate[1][1] = y;
		}
		timer2_enable( );	
}
