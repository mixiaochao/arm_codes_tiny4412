#include <led.h>

int main(void)
{
	int i = 0;

	led_init();

	while (1) {
		printf("led %d is on!\n", i+1);
		led_on(i);
		delay(10);
		led_off(i);
		i++;
		if (i > 3) i = 0;
	}
}
