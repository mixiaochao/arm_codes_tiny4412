#include <led.h>
#include <uart.h>

int main(void)
{
	int i = 0;

	led_init();

	while (1) {
		uprintf("%d\n", i+1);
		led_on(i);
		delay(10);
		led_off(i);
		i++;
		if (i > 3) i = 0;
	}
}
