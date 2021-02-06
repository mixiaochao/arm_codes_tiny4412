#ifndef XCM_ADC_H_
#define XCM_ADC_H_

#include <lib.h>

#define ADCCON 		*((volatile u32 *)0x126c0000) 
#define ADCDLY 		*((volatile u32 *)0x126c0008)
#define ADCDAT 		*((volatile u32 *)0x126c000C) 
#define CLRINTADC 	*((volatile u32 *)0x126c0018) 
#define ADCMUX 		*((volatile u32 *)0x126c001C)
#define IESR2		*((volatile u32 *)0x10440020)

extern void adc_init(void);
extern u16 adc_read(void);
extern void do_adc(void);

#define ADCINT		   42
#define wait_convert_end   while(!(ADCCON&(1 << 15)))
#define start_convert	   (ADCCON |= 1)

#endif
