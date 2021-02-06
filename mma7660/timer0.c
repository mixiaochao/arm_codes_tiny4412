#include <timer.h>

#if 0
void do_timer4(void)
{
	if (TINT_CSTAT & (1 << 9)) {
		printf("do what you want do...\n");
		TINT_CSTAT |= 1 << 9;
	}	
}
#endif

/*
	timer0_init: 设置timer0定时器作为内部定时器
	@ms	   ：定时的周期，单位为ms。		
*/
void timer0_init(u32 periodus, u32 dutyus)
{
	/*第一级分频后的频率为1MHz*/
	TCFG0 &= ~0xff;	
	TCFG0 |= 99;
	/*第二级分频后的频率为1MHz*/
	TCFG1 &= ~0xf;

	TCNTB0 = periodus;
	TCMPB0 = dutyus;

	TCON  = 0;

	/*将TCNTB0和TCMPB0里的值更新进逻辑单元*/
	TCON |= (1 << 3) | (1 << 1); 
	TCON &= ~(1 << 1);	


	/*使能timer4的中断*/
	//TINT_CSTAT |= 1 << 4;
}

void beep_set_hz(u32 freq)
{
#define USPERSEC 1000000UL
	u32 tmp = USPERSEC/freq;

	GPD0CON &= ~0xf;
	GPD0CON |= 0x1;

	GPD0DAT &= ~0x1;

	timer0_init(tmp, tmp >> 1);
}

void stop_pwm0_out(void)
{
	/*设置GPD0的0引脚为TOU0*/
	TCON &= ~(1 << 0);

	GPD0CON &= ~0xf;
	GPD0CON |= 0x1;

	GPD0DAT &= ~0x1;
}

void start_pwm0_out(void)
{
	/*设置GPD0的0引脚为TOU0*/
	GPD0CON &= ~0xf;
	GPD0CON |= 0x2;

	TCON |= (1 << 0);
}
