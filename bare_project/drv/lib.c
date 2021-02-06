
void *mymemcpy(void *dest, const void *src, int n)
{
	char *dst = dest;
	const char *sou = src;

	while(n--){
		*dst++ = *sou++;
	}

	return dest;
}

