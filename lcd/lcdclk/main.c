#include <clock.h>
#include <common.h>

int main(void)
{
	printf("CLK_DIV_LCD = %#x\n", CLK_DIV_LCD);
	printf("CLK_SRC_LCD0 = %#x\n", CLK_SRC_LCD0);

/*
 	CLK_SRC_LCD0 = 0x1111;
	FIMD0_SEL: CLK_SRC_LCD[0:3]=0x1;
	 
	默认选择的是XusbXTI 时钟源。


	CLK_DIV_LCD = 0xffffff;
	FIMD0_RATIO : CLK_DIV_LCD[0:3] = 0xf;

	SCLK_FIMD0 = MOUTFIMD0/(FIMD0_RATIO + 1) 
			   = xx/(15 + 1)
			   = ?		

	经过分析，在写LCD驱动时我们根据分析自己重新
	设置LCD的时钟源频率。

	//<1>选择时钟源为：SCLKMPLL_USER_T 
	CLK_SRC_LCD0 &= ~0xf;
	CLK_SRC_LCD0 |= 0x6;

	//<2>设置SCLKMPLL_USER_T频率的分频因子:
	
	CLK_DIV_LCD &= ~0xf;

	经过上面两步得出：

	SCLK_FIMD0 = SCLK_MPLL = 800MHz

 */

	return 0;
}
