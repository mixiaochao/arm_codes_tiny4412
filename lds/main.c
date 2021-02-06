#include <led.h>

extern int __life_start__[];
extern int __life_end__[];

int a0 __attribute__((unused,section(".life"))) = 200;
int a1 __attribute__((unused,section(".life"))) = 201;
int a2 __attribute__((unused,section(".life"))) = 202;
int a3 __attribute__((unused,section(".life"))) = 203;
int a4 __attribute__((unused,section(".life"))) = 204;
int a5 __attribute__((unused,section(".life"))) = 205;
int a6 __attribute__((unused,section(".life"))) = 206;
int a7 __attribute__((unused,section(".life"))) = 207;

int main(void)
{
	int *p = __life_start__;

	while (p < __life_end__) {
		printf("%d\n", *p++);	
	}

	return 0;
}
