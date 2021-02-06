#include <lib.h>

#define CLK_SRC_PERIL0 		*((volatile u32 *)0x1003c250)
#define CLK_SRC_TOP1   		*((volatile u32 *)0x1003c214)
#define CLK_DIV_PERIL0   	*((volatile u32 *)0x1003c550)
#define CLK_SRC_LEFTBUS   	*((volatile u32 *)0x10034200)
#define MPLL_CON0   		*((volatile u32 *)0x10040108)

#define MEMSIZE_TEST            *((volatile u32 *)0x110002c4)

int main(void)
{
	printf("CLK_SRC_PERIL0 = %#x\n", CLK_SRC_PERIL0);
	printf("CLK_SRC_TOP1 = %#x\n", CLK_SRC_TOP1);
	printf("CLK_SRC_LEFTBUS = %#x\n", CLK_SRC_LEFTBUS);
	printf("M: %d, P:%d, S:%d\n", (MPLL_CON0>>16)&0x3ff, 
					(MPLL_CON0>>8)&0x3f,
					MPLL_CON0&0x7);
	printf("CLK_DIV_PERIL0 = %#x\n", CLK_DIV_PERIL0);

	printf("xxx = %d\n", MEMSIZE_TEST>>5);

	return 0;
}
