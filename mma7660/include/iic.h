#ifndef MXC_MMA7660_H_
#define MXC_MMA7660_H_

#include <lib.h>


#define GPA1CON			(*(volatile u32 *)0x11400020)
#define GPX3CON			(*(volatile u32 *)0x11000c60)
#define EXT_INT43CON		(*(volatile u32 *)0x11000e0c)
#define EXT_INT43_FLTCON0	(*(volatile u32 *)0x11000e98)
#define EXT_INT43_MASK		(*(volatile u32 *)0x11000f0c)
#define EXT_INT43_PEND		(*(volatile u32 *)0x11000f4c)


#define IIC3_BASE 			0x13890000
#define I2CCON3 			(*(volatile u32 *)(IIC3_BASE + 0x0000)) 
#define I2CSTAT3 			(*(volatile u32 *)(IIC3_BASE + 0x0004))
#define I2CADD3 			(*(volatile u32 *)(IIC3_BASE + 0x0008))
#define I2CDS3 				(*(volatile u32 *)(IIC3_BASE + 0x000C))
#define I2CLC3 				(*(volatile u32 *)(IIC3_BASE + 0x0010))

extern void i2c_mma_eint25_init(void);

#endif
