#include <comm.h>
#include <iic.h>
#include <irq.h>

void iic1_init(int addr)
{
	/*GPD1_2,GPD1_3引脚设置成iic专用*/
	iic1_gpio_init();
		
	I2CADD = addr;

	/*使能ACK，分频得到SCL对应的频率为：195KHz, 使能收发中断*/
	I2CCON = (1<<7)|(1<<6)|(1<<5); 
	
	/*使能收发*/
	I2CSTAT = 1 << 4; 
}

/*	触摸屏控制模块和4412相连接的接口为：
 *	
 *	I2C接口使用：
 *		GPD1_2, GPD1_3
 * */
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

	#define MAX_WAIT 0x3856 

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

/*读取ft5206芯片内部寄存器的值*/
int read_data(char *data, int len)
{
	int i, ret = -1;

	I2CDS = (DEV_ADDR<<1)|1; 
	I2CSTAT = 0xb0;
//	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;

	if (I2CSTAT & 1)
	{
		ret = -2;
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
	I2CSTAT = 0x90; 
	resume_iic_scl();
	delay(1000);
	
	return ret;
}
