#include <iic.h>
#include <common.h>
#include <irq.h>
#include <tp.h>
#include <timer.h>

int touchscreen_stat = 0;
char data[31];
int x0,y0,x1,y1;

void do_tp(void)
{
	data[2] = 0;
	int tmp0,tmp1;

	EXT_INT41_PEND = EXT_INT41_PEND;

	if (read_data(data, sizeof(data)) == -2) 
	{
		if (read_data(data, sizeof(data)) == -2)
		{
			printf("no ack\n");	
			return;
		}
	}

	if (data[2] <= 0)
		return;

//	printf("points=%d: ", data[2]);

	if(!touchscreen_stat){
		x0 = x1 = (data[3]&0xf)<<8 | data[4];
		y0 = x1 = ((data[5]&0xf)<<8) | data[6];

		if(x0 >= 0 && x0 < 800 && y0 >= 0 && y0 < 480){	
			printf("\ntouchscreen is down!\n");
			touchscreen_stat = 1;
			printf("point coordenate: (x0=%d, y0=%d)\n",x0,y0); 
		}
	}else{
		tmp0 = (data[3]&0xf)<<8 | data[4];
		tmp1 = ((data[5]&0xf)<<8) | data[6];
		if(tmp0 >= 0 && tmp0 <= 800 && tmp1 >= 0 && tmp1 <= 480){	
			x1 = tmp0;
			y1 = tmp1;
		}
	}

	timer4_start( );
}
