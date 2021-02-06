#include <lib.h>

void delay(u32 n)
{
	int i,j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < 100000; j++) {
			;
		}
	}
}
