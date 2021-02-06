#include <timer.h>
#include <common.h>
#include <irq.h>

void timer4_init(int ms)
{
	/*第一级的分频因子设置为99，100MHz/100=1MHz*/
	TCFG0 &= ~(0xff << 8);
	TCFG0 |= 99 << 8;

	/*第二级分频因子为1， 最终的TIMER4的工作频率为1MHz*/
	TCFG1 &= ~(0xf << 16);

	TCNTB4 = 1000*ms;

}

void timer4_start(void)
{
	TCON &= ~(0x7 << 20);

	/*手动加载*/
	TCON |= (1 << 21);
	TCON &= ~(1 << 21);

	/*启动定时器*/
	TCON |= 1 << 20;

	/*使能timer4的中断*/
	TINT_CSTAT |= 1 << 4;
}
