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

int strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2) {
		if ((*s1 - *s2) != 0) {
			return *s1 - *s2;
		}
		s1++;
		s2++;	
	} 

	return 0;
}

void raise(void)
{
	
}
