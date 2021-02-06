#ifndef ADC_H_
#define ADC_H_

#include <comm.h>

#define ADC_INT 42
#define START_ADC_CONVERT (ADCCON |= 1 << 0)

extern void adc_init(int channel);

#define ADCCON 		*((u32 *)0x126c0000) 
#define ADCDLY 		*((u32 *)0x126c0008)
#define ADCDAT 		*((u32 *)0x126c000C) 
#define CLRINTADC 	*((u32 *)0x126c0018) 
#define ADCMUX 		*((u32 *)0x126c001C) 


#endif
