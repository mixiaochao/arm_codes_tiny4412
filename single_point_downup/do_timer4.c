#include <timer.h>
#include <common.h>
#include <tp.h>

void do_timer4(void)
{
	int result = 0;

	if(TINT_CSTAT&(1 << 9)){
		
		if(touchscreen_stat == 1){
			printf("touchscreen is up!\n");	
			touchscreen_stat = 0;
			result = x1 - x0;
			if (result < 0) {
				result = 0 - result;
				if (result > 200) {
					printf("move left ...\n");
				}
			} else {
				if (result > 200) {
					printf("move right ...\n");
				}
			}			
		}

		TINT_CSTAT |= 1 << 9;
	}
}
