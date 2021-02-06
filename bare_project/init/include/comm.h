#ifndef COMM_H_
#define COMM_H_

typedef volatile unsigned int u32;
typedef volatile unsigned short u16;
typedef volatile unsigned char u8;

#define NULL (void *)0
#define EXTERNAL_FUNC_ADDRESS 0x2020030
#define copy_to_ddr_from_sd(uStartBlk, uNumOfBlks, uDstAddr)   \
    (((void(*)(u32, u32, u32*))(*((u32 *)EXTERNAL_FUNC_ADDRESS)))(uStartBlk, uNumOfBlks, uDstAddr))

#define printf(...) (((int (*)(const char *, ...))0x43e11434)(__VA_ARGS__))

#endif
