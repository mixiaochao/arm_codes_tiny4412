#include <key.h>

/*将4个按键对应的GPIO引脚设置成输入功能*/
void key_init(void)
{
	GPX3CON &= ~(0xffff << 8);
}

u32 scanf_keys(void)
{
	u32 keynum;

	while (((GPX3DAT>>2)&0xf) == 0xf){
		;
	}	

	switch ((GPX3DAT>>2)&0xf) {//0xe, 0xd, 0xb, 0x7
		case 0xe:
			keynum = 1;
			break;
		case 0xd:
			keynum = 2;
			break;
		case 0xb:
			keynum = 3;
			break;
		case 0x7:
			keynum = 4;
			break;
	}
	printf("key %d is down!\n", keynum);

	while (((GPX3DAT>>2)&0xf) != 0xf){
		;
	}	

	printf("key %d is up!\n", keynum);

	return keynum;
}
