#include <lib.h>
#include <uart.h>

#define DRIVER_BLK_START	49
#define DRIVER_BLK_SIZE		2048	
#define DRIVER_DST_ADDR		0x43e00000

#define EXTERNAL_FUNC_ADDRESS   0x02020030  
    
#define SDMMC_ReadBlocks(uStartBlk, uNumOfBlks, uDstAddr)\
(((void(*)(u32, u32, u32*))(*((u32 *)EXTERNAL_FUNC_ADDRESS)))(uStartBlk, uNumOfBlks, uDstAddr))

void entry(void)
{
	void (*jump_to_ddr)(void) = (void *)DRIVER_DST_ADDR;

	uart0_init();
	uprintf("coming into bl2...ok...\n");

	SDMMC_ReadBlocks(DRIVER_BLK_START, DRIVER_BLK_SIZE, (u32 *)DRIVER_DST_ADDR);

	jump_to_ddr();		
}
