#include <string.h>

int strlen(const char *s)
{
	int ret;
	while(*s != '\0')
	{
		ret++;
	}
	return ret;
}


char *strcpy(char *dst,const char *src)
{
	char *p = dst;
	while(*src != '\0')
	{
		*dst = *src;
		src++;
		dst++;
	}
	*dst = '\0';

	return p;
}
char *strcat(char *dst,const char *src)
{
	char *p = dst;
	while(*dst != '\0')
	{
		dst++;
	}
	while(*src != '\0')
	{
		*dst = *src;
		src++;
		dst++;
	}
	*dst = '\0';
	return p;
}


int strcmp(const char *s1,const char *s2)	
{
	while(*s1 && *s2)
	{
		if(*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			break;
	}
	return *s1 - *s2;
}
char *itos(unsigned int num, char *buf)
{
	int i;
	char *p = buf;
	if(num < 10){
		buf[0] = num + '0';
		buf[1] = '\0';
		return p;
	}

	itos(num/10, buf);

	for(i = 0; buf[i] != '\0'; i++);

	buf[i] = num%10 + '0';
	buf[i+1] = '\0';
	return p;
}

int atoi(const char *str)
{
	int sum = 0;
	while(*str)
	{
		sum = sum*10+*str -'0';
		str++;
	}
	return sum;
}
