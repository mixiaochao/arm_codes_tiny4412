#include <common.h>
#include <iic.h>
#include <irq.h>

/* iic1初始化设置 */
void iic1_init(int addr)
{
	/* 将触摸屏控制模块的输出引脚所连接的GPIO口
 	   设置为IIC总线的sclk和sdat专用*/
	iic1_gpio_init();
		
	I2CADD = addr; //Flowcharts of Operations in Each Mode 1

	/* 对PCLK进行分频得到sclk的一个频率，使能收发中断*/
//	I2CCON = (1 << 6) | (1 << 5) | (15);//Flowcharts of Operations in Each Mode 2
	I2CCON = (1<<7)|(1<<6)|(1<<5); //196KHz
	
	/*使能收发数据*/ 
	I2CSTAT = 1 << 4; //Flowcharts of Operations in Each Mode 3
	

	/*SDA线上的延时使能和延时对应的时钟周期个数的设置*/
//	I2CLC = (1 << 2) | 3;

//	iic1_enable_ack();
}

//将ctpm和4412相连的两个引脚设置成I2C_1_SCL 
//和 I2C_1_SDA专用。
void iic1_gpio_init(void)
{
	GPD1CON &= ~(0xff << 8);
	GPD1CON |= 0x22 << 8;
}

void resume_iic_scl(void)
{
	I2CCON &= ~(1<<4);
}

int wait_until_iic_irq(void)
{
	int i;

	#define MAX_WAIT  0x3fff

	for (i = 0; i < MAX_WAIT; i++)
	{	
		if (I2CCON & (1<<4))	
			return 0;
	}
	return -1;
}

void delay(int val)
{
        val *= 66; 

        while (val--)
                ;   
}

int read_data(char *data, int len)
{
	int i, ret = -1;

	I2CDS = (DEV_ADDR<<1)|1; //master rx
	I2CSTAT = 0xb0;
	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;

	if (I2CSTAT & 1)
	{
		ret = -2;  //no ack
		goto END;
	}
	
	for (i = 0; i < len; i++)
	{
		resume_iic_scl();
		if (wait_until_iic_irq() < 0)
			goto END;
		
		data[i] = I2CDS;
	}		
	ret = i;

END:
	I2CSTAT = 0x90; // stop signal
	resume_iic_scl();
	delay(1000);
	
	return ret;
}
