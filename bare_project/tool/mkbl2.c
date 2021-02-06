#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//./a.out  u-boot.bin bl2.bin
int main (int argc, char *argv[])
{
	FILE		*fp;
	unsigned char	src;
	char		*Buf, *a;
	int		BufLen;
	int		nbytes, fileLen;
	unsigned int	checksum = 0;
	int		i;

	if (argc != 3)
	{
		printf("Usage: mkbl1 <source file> <destination file> \n");
		return -1;
	}

	BufLen = 14336;
	Buf = (char *)malloc(BufLen);
	memset(Buf, 0x00, BufLen);

	fp = fopen(argv[1], "rb");
	if( fp == NULL)
	{
		printf("source file open error\n");
		free(Buf);
		return -1;
	}

	nbytes = fread(Buf, 1, BufLen, fp);

	if ( nbytes < 0 )
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	fclose(fp);

	for(i = 0;i < (14 * 1024) - 4;i++)
	{
		checksum += (unsigned char)(Buf[i]);
	}
	*(unsigned int*)(Buf+i) = checksum;

	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a	= Buf;
	nbytes	= fwrite( a, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);
	fclose(fp);

	return 0;
}
