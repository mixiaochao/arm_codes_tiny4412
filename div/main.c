#include <uart.h>
#include <cmd.h>

#define LEN 64

int main(void)
{
	char buf[LEN];

	int a = 200, b = 10;

	a /= b;

	uart0_init();

	uprintf("\na = %d\n", a);
	uprintf("+++++++++++++++++++++++++++++\n");
	uprintf("+                           +\n");
	uprintf("+ welcome to control device +\n");
	uprintf("+                           +\n");
	uprintf("+++++++++++++++++++++++++++++\n");

	while (1) {
		uputs("[CotexA9@mi]# ");
		ugets(buf);


		if (buf[0]) {
			if (strcmp("exit", buf) == 0) {
				break;
			}

			find_cmd_and_excute(buf);
		}
	}

	return 0;
}
