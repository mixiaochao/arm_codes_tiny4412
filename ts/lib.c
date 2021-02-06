#include <lib.h>

void *memcpy(void *dest, const void *src, u32 n)
{
	char *dst = dest;
	const char  *sour = src;

	while (n--) {
		*dst++ = *sour++;
	}

	return dest;
}

void *memset(void *s, int c, u32 n)
{
	char *src = s;

	while (n--) {
		*src++ = c;
	}

	return s;
}


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
	while (*s1) {
		if ((*s1 - *s2) != 0) {
			return *s1 - *s2;
		}
		s1++;
		s2++;	
	} 

	return 0;
}


