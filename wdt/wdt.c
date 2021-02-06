#include <wdt.h>

static u32 pic_num = 0;

/*看门狗的定时中断处理函数*/
void do_wdt_timer(void)
{
	printf("watch dog coming...\n");
	WTCLRINT = 0;

	pic_num++;
	if (pic_num == 20) {
		pic_num = 0;
	}
#define SZ 800*480*4

	/*设置WINDOW0的BUFFER0的起始地址*/
	VIDW00ADD0B0 = FRAMBUFFER0 + pic_num*SZ; 
	/*设置WINDOW0的BUFFER0的结束地址*/
	VIDW00ADD1B0 = FRAMBUFFER0 + VIDOSD0C*4 + pic_num*SZ; 
	
	
}

/*利用wdt设备来实现16bit定时*/
void wdt_timer_init(u32 ms)
{
	WTCON = (255 << 8) | (1 << 5) | (3 << 3) | (1 << 2);
	WTDAT = 3*ms;
	WTCNT = 3*ms;
}
