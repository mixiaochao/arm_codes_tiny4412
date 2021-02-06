#include <lib.h>
#include <mmu.h>

void do_unde(void)
{

}

void do_svc(u32 imme)
{

}

int main(void)
{

#define CLK_SRC_TOP0 *((volatile u32 *)0x1003c210)
#define CLK_DIV_TOP *((volatile u32 *)0x1003c510)
	rebuild_vectors_table();		

	/*测试WDT的时钟源PCLK是多少HZ*/
	printf("xxxx = %d\n", 0x1&(CLK_SRC_TOP0>>16));
	printf("xxxx = %d\n", 0xf&(CLK_DIV_TOP>>4));

	/*800MHz/8 = 100MHz*/

	return 0;
}

