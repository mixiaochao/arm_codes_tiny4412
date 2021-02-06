#include <iic.h>
#include <tp.h>

void do_tp(void)
{
	int i;
	char data[32];

	EXT_INT41_PEND = EXT_INT41_PEND;

	if (read_data(data, sizeof(data)) == -2) 
	{
		if (read_data(data, sizeof(data)) == -2)
		{
			printf("no ack\n");	
			return;
		}
	}

	if (data[2] <= 0)
		return;

	printf("points=%d: ", data[2]);
	for (i = 0; i < data[2]; i++)
	{
		printf("(x%d=%d,y%d=%d); ", i, ((data[i*6+3]&0xf)<<8)|\
		data[i*6+4], i, ((data[i*6+5]&0xf)<<8)|data[i*6+6]);
	}

	printf("\n\n%d\n", (data[3]>>6)&0x3);

	printf("\n\n");
}
