#ifndef MXC_I2C_H_
#define MXC_I2C_H_

#include <lib.h>

#define GPD1CON 	*((volatile u32 *)0x114000c0)

#define I2CCONn 	*((volatile u32 *)0x13870000) 
#define I2CSTATn 	*((volatile u32 *)0x13870004)
#define I2CADDn 	*((volatile u32 *)0x13870008) 
#define I2CDSn 		*((volatile u32 *)0x1387000C) 
#define I2CLCn 		*((volatile u32 *)0x13870010) 

extern void i2c_pending_test(void);

#endif
