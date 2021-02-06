#include <iic.h>
#include <irq.h>
#include <tp.h>
#include <isr.h>
#include <timer.h>

void tp_int_init(void)
{
	/*
 		触摸屏控制模块外部中断所用4412接口：

		GPX1_6
	*/
	/*将GPX1_6设置成外部中断功能*/
	GPX1CON |= 0xf << 24; 

	/*设置中断的触发方式为下降边沿*/
	EXT_INT41CON &= ~(0x7 << 24); 
	EXT_INT41CON |= 2 << 24;

	/*使能数字滤波，并设置滤波需要的延时周期总数*/
	EXT_INT41_FLTCON1 |= 0xff<<16;

	/*使能对应的外部中断*/
	EXT_INT41_MASK &= ~(1 << 6);

	/*exynos4412 i2c*/
	iic1_init(9527);

	irq_request_cpu0(TP_IRQ, do_tp, 0);

	/*初始化timer2的中断*/

	timer2_init(15);
}

