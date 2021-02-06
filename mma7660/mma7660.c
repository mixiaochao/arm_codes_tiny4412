
#define DEV_ADDR  0x4c

#include <iic.h>
#include <irq.h>

int wait_until_iic_irq();
void resume_iic_scl();
void iicdelay(int val);
int iic_write(unsigned char reg_addr, unsigned char data);
int __iic_write(unsigned char reg_addr, unsigned char data);
static void do_eint25(void);

//1st:	first step
static inline void i2c3_init(void)
{
	// mma7660 : i2csda3/i2cscl3(GPA1_2/ GPA1_3)  eint25(GPX3_1)
	GPA1CON &= ~(0xff<<8);
	GPA1CON |= 0x33<<8;

	I2CCON3 = (1<<7)|(1<<6)|(1<<5); //enable ack, 100MHz/512, enable T/R irq, 196KHz
	I2CSTAT3 = 1<<4; //Enable Tx/Rx
}

//2end:  second step, 初始化mma7660传感器本身，在备用模式设置中断产生的情况
//	 和每秒钟样值的个数及防止抖动的时钟周期个数，阈值。
static inline void mma_init(void)
{
	///mma7660_init
	
	//在设置mma7660内部的寄存器之前应首先将0x07寄存器设置为备用模式
	iic_write(0x07, 0); //MODE register: Standby Mode;Auto-Wake is disabled;Auto-Sleep is disabled; 	
	iicdelay(10000);
	
	//SR register:64 Samples/Second Active and Auto-Sleep Mode;16 Samples/Second Auto-Wake Mode;3 measurement samples
	iic_write(0x08, ((7<<5) | (1<<3) | 1));  

	iic_write(0x05, 0xa0); //SPCNT register  internal sleep counter = 0xa0 = 160
	
	//PDET register: XYZ-axis is enabled for tap detection;Tap detection threshold is +-4 counts
	iic_write(0x09, 0x4); 

	//Tap detection debounce filtering requires 15 adjacent tap detection
	iic_write(0x0a, 15); //PD register

	//Front/Back position change causes an interrupt
	//Up/Down/Right/Left position change causes an interrupt
	//Successful tap detection causes an interrupt
	//Shake detected on the XYZ-axis causes an interrupt, and sets the Shake bit in the TILT register
	iic_write(0x06, 0xe7); //INTSU register 0xe7 = 11100111

	//set the device into Active mode
	//Auto-Wake is enabled
	//Auto-Sleep is enabled
	//Interrupt output INT is push-pull
	//Interrupt output INT is active low
	iic_write(0x07, 0x59); //MODE register: 0101 1001
	iicdelay(10000);
}

static inline void eint25_init(void)
{
	GPX3CON |= 0xf<<4;

	EXT_INT43CON &= ~(7 << 4); //low level
	EXT_INT43CON |= 2<<4; //falling edge

	EXT_INT43_FLTCON0 |= 0xff<<8;

	EXT_INT43_MASK &= ~(1<<1);

	irq_request_cpu0(64, do_eint25, 0);
}


/*i2c控制器3的初始化、mma7660的初始化、中断的设置及注册*/
void i2c_mma_eint25_init(void)
{
	i2c3_init();
	mma_init();
	eint25_init();	
}

void resume_iic_scl()
{
	I2CCON3 &= ~(1<<4);
}

int wait_until_iic_irq(void)
{
	int i;

	#define MAX_WAIT  0x3fff

	for (i = 0; i < MAX_WAIT; i++)
	{	
		if (I2CCON3 & (1<<4))	
			return 0;
	}
	return -1;
}

/*iic_write: 往mma7660内部寄存器地址为reg_addr的地址写入data数据*/
int iic_write(unsigned char reg_addr, unsigned char data)
{
	int ret;

	ret = __iic_write(reg_addr, data);
	if (ret < 0)
		return __iic_write(reg_addr, data);

	return 0;
}

int __iic_write(unsigned char reg_addr, unsigned char data)
{
	int ret = -1;

	I2CDS3 = (DEV_ADDR<<1)|0; //master tx
	I2CSTAT3 = 0xf0;
	resume_iic_scl();

	if (wait_until_iic_irq() < 0)
		goto END;
	if (I2CSTAT3 & 1)
		goto END;

	I2CDS3 = reg_addr;
	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;
	if (I2CSTAT3 & 1)
		goto END;

	I2CDS3 = data;
	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;
	if (I2CSTAT3 & 1)
		goto END;

	ret = 0;
END:   // stop signal
	I2CSTAT3 = 0xd0;
	resume_iic_scl();
	iicdelay(1000);

	return ret;
}


/*从mma7660传感器内部地址为reg_addr的寄存器读取数据*/
unsigned char read_data(unsigned char reg_addr)
{
	unsigned char ret = -1;
	
	I2CDS3 = (DEV_ADDR<<1)|0; //master tx
	I2CSTAT3 = 0xf0;

	resume_iic_scl();

	if (wait_until_iic_irq() < 0)
		goto END;
	if (I2CSTAT3 & 1)
		goto END;

	I2CDS3 = reg_addr;
	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;
	if (I2CSTAT3 & 1)
		goto END;
	
//////////////////////////////////////////////////////
	I2CDS3 = (DEV_ADDR<<1)|1; //master rx
	I2CSTAT3 = 0xb0;
	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;
	if (I2CSTAT3 & 1)
		goto END;

	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;
	
	ret = I2CDS3;

END:
	I2CSTAT3 = 0x90; // stop signal
	resume_iic_scl();
	iicdelay(1000);
	
	return ret;
}

static void do_eint25(void)
{
	printf(".");

	unsigned int ret;

	/*清除中断*/
	EXT_INT43_PEND = EXT_INT43_PEND;
	
	ret = read_data(0x03);
	if (ret < 0)
	{
		ret = read_data(0x03);
		if (ret < 0)
			return;
	}

	if ((ret & 3) == 1) {//Bafro
		printf("front ");
	}else if((ret & 3) == 2){
		printf("back  ");
	}
	
	switch ((ret>>2)&7)
	{
		case 1:
			printf("left  ");
			break;
		case 2:
			printf("right ");
			break;
		case 5:
			printf("down  ");
			break;
		case 6:
			printf("up    ");
			break;
		default:
			break;
	}

	printf("\n");
}

void iicdelay(int val)
{
        val *= 68; 

        while (val--)
                ;   
}

