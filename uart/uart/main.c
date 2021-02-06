#include <uart.h>

#define LEN 512

int main(void)
{
	char buf[LEN];

	uart0_init();
	uprintf("%d %x %c%c%c  %s", -2017, 0xabcdef, 'y', 'o', 'u', "give a string:");
	uputs_(ugets(buf));

	return 0;
}
