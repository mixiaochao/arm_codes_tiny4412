#include <i2c.h>

#define SLAVE_ADD(A)  (A << 1)
#define IIC_FIRST_BYTE(S, C)  (SLAVE_ADD(S) | (C))
#define WRITE 0
#define READ  1



void i2c_pending_test(void)
{
	int i;
	int j;

	GPD1CON &= ~(0xff<<8);
	GPD1CON |= 0x22<<8;

	/*使能收发中断，对PCLK分频得到196KHz*/
	I2CCONn = (1<<6)|(1<<5); //tx clk=196khz

	I2CSTATn = 1<<4; //serial output

//	for (i = 50; i <= 127; i++) {

		I2CDSn = IIC_FIRST_BYTE(0x38, WRITE); //
		I2CSTATn = 0xf0; //master tx, start signal, serial ouput

		printf("i = %d, before: 0x%08x\n", i, I2CSTATn);

		j = 9527;
		while (!(I2CCONn & (1<<4))){
			j--;
			if (j == 0) {
				printf(".");
				break;
			}
		}
		delay(30);
		printf("i = %d, after : 0x%08x\n", i, I2CSTATn);
	

		I2CSTATn = 0xd0;
		I2CCONn &= ~(1 << 4);
		delay(30);
//	}
	

}

