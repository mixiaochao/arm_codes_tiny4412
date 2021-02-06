#include <lcd.h>
#include <key.h>
#include <common.h>
#include <irq.h>
#include <image.h>

void do_key(void)
{
	switch((EXT_INT43_PEND>>2) & 0xf)
	{
		case 1:
			printf("key 1 irq occure!!\n");
			WAIT_ROTAT_END;
			flip_ver();
			start_rotat();
			VIDW00ADD0B0 = DST_IMAGE;
			VIDW00ADD1B0 = DST_IMAGE + VIDOSD0C * 4;

			break;
		case 2:
			printf("key 2 irq occure!!\n");
			WAIT_ROTAT_END;
			flip_hor();
			start_rotat();
			VIDW00ADD0B0 = DST_IMAGE;
			VIDW00ADD1B0 = DST_IMAGE + VIDOSD0C * 4;
			break;
		case 4:
			printf("key 3 irq occure!!\n");
			break;
		case 8:
			printf("key 4 irq occure!!\n");
			break;
		default:
			break;
	}

	EXT_INT43_PEND =  EXT_INT43_PEND;
}
