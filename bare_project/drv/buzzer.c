#include <buzzer.h>
#include <irq.h>
#include <comm.h>
#include <uart.h>
#include <display.h>

/******************全局变量区************************************************/
u32 periodnum      = 200000;  //PWM工作时的时中周期个数
int buzzer_flag    = 0;       //控制PWM输出的开和关 
int buzzer_on_off  = 0;       //控制是否将当前的时钟周期个数更新到寄存器
/**************************************************************************/

/*
 * buzzer_init: 蜂鸣器的初始化
 *
 * @periodnum: PWM的工作的时钟周期个数
 *
 * */
void buzzer_init(void)
{
	/*timer0's set*/
	TCFG0 = 99; //divide PCLK to 1MHz
	TCFG1 &= ~0xf;   //timer0 work f = 1MHz

	//set duty as 1/2
	TCNTB0 = periodnum;
	TCMPB0 = periodnum >> 1;

	TCON &= ~0xf;
		
	/*manual update tcntb0, tcmpb0*/
	TCON |= 1 << 1;
	TCON &= ~(1 << 1);

	/*set auto-reload and start work*/
	TCON |= (1 << 0) | (1 << 3);
}
/**   
 *
 *  函数  名： buzzer_control
 *  参    数： x触屏点横坐标值，范围（0 -  799）
 *             y触屏点列坐标值，范围( 0 - 479)
 *  函数功能： 根据触屏点坐标值的范围，进行蜂鸣器的频率加减，及蜂鸣器的开关
 *
 * */
void buzzer_control(int x,int y)
{
	/*开关蜂鸣器*/
	if(x >= 270 && x <= 401 && y >= 76 && y <= 345)
	{
	        
		if(buzzer_flag == 0)             /*开蜂鸣器*/                       
		{                                             
			GPD0CON &= ~0xf;                          
			GPD0CON |= 0x2;	        /*将蜂蜜器对应引脚设置为PWM输出*/
			buzzer_flag = 1;        /*用于循环控制蜂器开关*/
			buzzer_on_off = 1;      /*表示在开蜂鸣器状态可以给寄存器TCNTB0，TCMPB0赋新值*/
			display_string(115,141,"****",((16<<16)|(176<<8)|76),0,6);    /*刷屏*/
			display_string(115,141," ON ",0xffffff,0,6);                  /*显示 NO*/
		}else if(buzzer_flag == 1)     /*关蜂鸣器*/
		{                                                
			GPD0CON &= ~0xf;                             
			GPD0CON &= ~(0x2 << 0);	  /*关蜂鸣器对应引脚的PWM*/                 
			buzzer_flag = 0;          /*用于循环控制蜂蜜器开关*/
			buzzer_on_off = 0;	  /*表示在关蜂鸣器状态不可以给寄存器TCNTB0，TCMPB0赋新值*/
			display_string(115,141,"****",((16<<16)|(176<<8)|76),0,6);   /*刷屏*/
			display_string(115,141," OFF ",0xffffff,0,6);                /*显示 OFF*/
		}
	}
	/*加蜂名器频率*/
	if(x >= 62 && x <= 360) 
	{
		if(periodnum <= 600000)
			periodnum += 5000;
		uprintf("+++++++++periodnum = %d\n",periodnum);
	}
	/*减蜂鸣器频率*/
	if(x >= 614 && x <= 728 && y <= 428 && y >= 315)
	{
		if(periodnum >= 10000)
			periodnum -= 5000;	
		uprintf("---------periodnum = %d\n",periodnum);
	}
	/*用于控制当进入蜂鸣器模块时,初始状态为不工作，buzzer_on_off：全局变量初始值为零*/     
	if(buzzer_on_off == 1)
	{
		//set duty as 1/2
		TCNTB0 = periodnum;
		TCMPB0 = periodnum >> 1;        //二分频
	}
}
/**
 *
 *   函数  名：delay_buzzer_di;
 *   函数功能：实现短暂延时
 *
 * */
static void  delay_buzzer_di(void)
{
	u32 i;
	u32 j;
	for(i = 0;i < 120;i++)
	{
		for(j = 0;j < 1000;j++)
		{;}
	}
} 

/**
 *  函数  名：buzzer_di
 *  函数功能：实现蜂鸣器响一声，用于AD报警，及作为按键提醒
 *  
 * */
void buzzer_di()
{
		
	GPD0CON &= ~0xf;
	GPD0CON |= 0x1;	        //将鸣器对应引脚设置为普通 IO 输出引脚
		
	GPD0DAT = 1;           //根据原理图知该引脚输出高电平期间，蜂鸣器响
	delay_buzzer_di();     //延时使得，产生di一声的效果
	GPD0DAT = 0;           //输出低电,使得蜂鸣器不响
}
/**
 *  函数  名：buzzer_didi
 *  函数功能：蜂鸣器长响，用于shell命令控制硬件
 * */
void buzzer_didi()
{
	GPD0CON &= ~0xf;
	GPD0CON |= 0x1;	
	GPD0DAT = 1;
}
/**
 *
 * 函数  名：buzzer_close
 * 函数功能：关蜂鸣器  用于shell命令控制硬件
 * */
void buzzer_close()
{
	GPD0CON &= ~0xf;
	GPD0CON |= 0x1;	
	GPD0DAT = 0;
}
