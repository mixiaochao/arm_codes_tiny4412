#include <irq.h>
#include <display.h>
#include <buzzer.h>
#include <adc.h>
#include <uart.h>

/***********************全局变量区***************************************/
int ad_alarm_val = 2600;                                //ad   报警阈值
/***********************************************************************/

/**
 *  函 数 名：dispaly_ad_da
 *  函数功能：显示当前电压数字量及所对应的模拟量
 *  参    数：ad_tem  电压数字量
 *  	      da_tem  电压模拟量
 * */
static void dispaly_ad_da(int  ad_tem,int da_tem)
{
	 /***************************显示AD**********************************/
        display_2448num(500,52,11,0xffffff,0,8);                           //A
        display_2448num(524,52,12,0xffffff,0,8);                           //D
        display_2448num(548,52,10,0xffffff,0,8);                           //:

        ad_clean_lcd(572,52,4,0xffffff,0,8);                               //清屏
        display_2448num(572,52,ad_tem /1000,0x000000,0,8);                 //千
        display_2448num(596,52,ad_tem %1000/100,0x000000,0,8);             //百
        display_2448num(620,52,ad_tem %1000%100/10,0x000000,0,8);          //十
        display_2448num(644,52,ad_tem % 1000%100%10,0x000000,0,8);         //个

	 /**************************显示DA**********************************/
        display_2448num(90,52,12,0xffffff,0,8);                             //D
        display_2448num(114,52,11,0xffffff,0,8);                            //A
        display_2448num(138,52,10,0xffffff,0,8);                            //:
	
        ad_clean_lcd(162,52,4,0xffffff,0,8);	                            //清屏
        display_2448num(162,52,da_tem /1000,0x000000,0,8);                  //千
        display_2448num(186,52,da_tem %1000/100,0x000000,0,8);              //百
        display_2448num(210,52,da_tem %1000%100/10,0x000000,0,8);          //十
        display_2448num(234,52,da_tem % 1000%100%10,0x000000,0,8);         //个
        display_2448num(258,52,14,0xffffff,0,8);                           //m
        display_2448num(282,52,15,0xffffff,0,8);                           //v
        /**************************************************************/
}
/**
 *  函数  名：dispaly_ad_alarm_val
 *  函数功能：显示AD报警阈值
 * */
static void display_ad_alarm_val(void)
{
        ad_clean_lcd(380,254,4,0xff0000,0,8);	                                    //清屏
        display_2448num(380,254,ad_alarm_val /1000,0x000000,0,8);                  //千
        display_2448num(404,254,ad_alarm_val %1000/100,0x000000,0,8);              //百
        display_2448num(428,254,ad_alarm_val %1000%100/10,0x000000,0,8);           //十
        display_2448num(452,254,ad_alarm_val % 1000%100%10,0x000000,0,8);          //个
}
/*  
 * 函数  名：ad_alarn_do
 * 函数功能：当电压数字量超过阈值时通过调用buzzer_di 函数控制蜂鸣器报警
 * 参    数：ad_tem 当前电压数字量
 * */
static void ad_alarm_do(int ad_tem)
{
	int i = 0;
	if(ad_tem > ad_alarm_val)
	{
		for(i = 0;i < 10;i++)
		{
			buzzer_di();
			uprintf("do-------");
		}
	}
}
/*
 *
 *   函数  名：ad_alarm
 *   函数功能：根据触摸屏坐标加减调整报警阈值
 * */
 void ad_alarm(int x,int y)
{
	
	if(x >= 97 && x <= 242 && y >= 335 && y <= 400)
	{
		if(ad_alarm_val >=0&&ad_alarm_val<=4096)
			ad_alarm_val += 100;
		uprintf("++");
		buzzer_di();
	}		
	
	if(x >= 585 && x <= 725 && y >= 333 && y <= 398)
	{
		if(ad_alarm_val >=0&&ad_alarm_val<=4096)
			ad_alarm_val -= 100;
		uprintf("--");
		buzzer_di();
	}

	display_ad_alarm_val();   //显示报警阈值
}
/*
 *   函数  名：do_adc
 *   函数功能：接收内置AD处理器处理的AD结果，并根据AD位数为12位将其转换为对应的模拟电压值
 * */
static void do_adc(void)
{
        int ad_tem;
        int da_tem;
     
        CLRINTADC = 95273856;
        uprintf("ADC ----> %d\n", ADCDAT&0xfff);

        ad_tem = ADCDAT&0xfff;                                  //取ADC数据寄存器的数据   12位AD 故 0- 4096 
        da_tem = (18*ad_tem/4096)*100;                          //转换为对应的模拟电压值  0 - 1800mv

        uprintf("ad_tem = %d\n",ad_tem);
        uprintf("da_tem = %d\n",da_tem);
	
        dispaly_ad_da(ad_tem,da_tem);                           //显示处理AD，DA结果值
		ad_alarm_do(ad_tem);                            //显示报警阈值
}
/***
 *  函数  名：adc_init
 *  函数功能：初始化ADC
 *  参    数：channel:通道选择
 * **/
void adc_init(int channel)
{
	         // 12位AD //使能AD转换//AD转换频率设为1MHz 
        ADCCON = (1 << 16) | (1 << 14) | (99 << 6); 
        ADCDLY = 0xffff;

        if(channel >= 0 && channel <= 3){
                ADCMUX = channel;
        }
        irq_request_cpu0(ADC_INT, do_adc, 0);
#define IESR2 *((u32 *)0X10440020)
        IESR2 |= 1 << 19;
}


