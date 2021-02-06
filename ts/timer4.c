#include <timer4.h>

void do_timer4(void)
{
	if (TINT_CSTAT & (1 << 9)) {
		printf("do what you want do...\n");
		TINT_CSTAT |= 1 << 9;
	}	
}

/*
	timer4_init: 设置timer4定时器作为内部定时器
	@ms	   ：定时的周期，单位为ms。		
*/
void timer4_init(u32 ms)
{
	/*第一级分频后的频率为1MHz*/
	TCFG0 &= ~(0xff << 8);	
	TCFG0 |= 99 << 8;
	/*第二级分频后的频率为1MHz*/
	TCFG1 &= ~(0xf << 16);

	TCNTB4 = 1000*ms;

	TCON  = 0;

	TCON |= (1 << 22) | (1 << 21); 

	/*将TCNTB4里的值更新进逻辑单元*/
	TCON &= ~(1 << 21);	

	/*启动timer4工作和设置自动加载功能*/
	TCON |= (1 << 20);

	/*使能timer4的中断*/
	TINT_CSTAT |= 1 << 4;
}
