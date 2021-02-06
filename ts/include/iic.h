#ifndef MILLET__IIC_H
#define MILLET__IIC_H

#include <lib.h>

#define DEV_ADDR  0x38

#define GPD1CON 			(*(volatile u32 *)(0x11400000 + 0x00C0))

#define IIC1_BASE 			0x13870000
#define I2CCON 				(*(volatile u32 *)(IIC1_BASE + 0x0000)) 
#define I2CSTAT 			(*(volatile u32 *)(IIC1_BASE + 0x0004))
#define I2CADD 				(*(volatile u32 *)(IIC1_BASE + 0x0008))
#define I2CDS 				(*(volatile u32 *)(IIC1_BASE + 0x000C))
#define I2CLC 				(*(volatile u32 *)(IIC1_BASE + 0x0010))

extern void iic1_gpio_init(void);
extern void iic1_init(int addr);
extern void resume_iic_scl(void);
extern int wait_until_iic_irq(void);
extern int read_data(char *data, int len);

#endif
