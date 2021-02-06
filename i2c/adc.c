#include <adc.h>

void do_adc(void)
{
	printf("adc --> %d\n", adc_read());
	CLRINTADC = 0;
}

void adc_init(void)
{
	/*选择12bit量化精度，使能分频，设置分频值是99*/
	ADCCON = (1 << 16) | (1 << 14) | (99 << 6);

	ADCDLY = 0xffff;
	ADCMUX = 0;

	/*使能ADC的转换结束中断*/
	IESR2 |= 1 << 19;
}

u16 adc_read(void)
{
	return ADCDAT&0xfff;
}


