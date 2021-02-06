#include <led.h>
#include <key.h>

int main(void)
{
	u32 i = 0;
	u32 ledstat = 0xf;

	led_init();
	key_init();

	while (1) {
		i = scanf_keys(); 	
		if ((1 << (i-1)) & ledstat) {
			led_on(i-1);
			printf("led %d is on!\n", i);
		} else {
			led_off(i-1);
			printf("led %d is off!\n", i);
		}
		
		ledstat ^= (1 << (i-1));
	}
}
