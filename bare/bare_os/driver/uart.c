#include <uart.h>
#include <stdarg.h>

void uart0_init(void)
{
	/*将串口所连接的GPA0和GPA1设置成串口专用*/
	GPA0CON &= ~0xff;
	GPA0CON |= 0x22;

	/*设置通信的协议为8N1*/
	ULCONn = 0x3;

	/*设置数据的收发方式为polling方式*/
	UCONn = 0x5;

	/*禁用FIFO模式，选择非FIFO模式*/
	UFCONn = 0x0; 

	/*禁用MODEM模式*/	
	UMCONn = 0x0;

	/*设置波特率为115200*/
	UBRDIVn = 53;
	UFRACVALn = 4;

	/*移植的bootloader的时钟初始化没有以下关于串口的这两个时钟寄存器的设置*/
	CLK_SRC_PERIL0 = 0x66666;              
	CLK_DIV_PERIL0 = 0x77777;
}

void uputchar(int ch)
{
	while (!(UTRSTATn&0x2)) {
		;
	}

	UTXHn = ch;

	if (ch == '\n') {
		uputchar('\r');
	}
}


int  ugetchar(void)
{
	int c;

	while (!(UTRSTATn&0x1)) {
		;
	}

	c = URXHn;

	if (c == '\r') {
		c = '\n';		
	}

	uputchar(c);

	return c;
}

char * ugets(char *buf)
{
	int c;
	char *tmp = buf;

	while ((c = ugetchar()) != '\n') {
		*buf++ = c;
	}

	*buf = '\0';

	return tmp;
}

void uputs(const char *buf)
{
	while (*buf) {
		uputchar(*buf);
		buf++;
	}
}

void uputs_(const char *buf)
{
	uputs(buf);
	uputchar('\n');
}

void itox(int n, char *buf)
{
	int i;

	if (n < 16) {
		if (n < 10) {
			buf[0] = n + '0';
		} else {
			buf[0] = n - 10 + 'a';
		}
		buf[1] = '\0';

		return;
	}

	itox(n/16, buf);

	for (i = 0; buf[i] != '\0'; i++);

	if (n%16 < 10) {
		buf[i] = n%16 + '0';
	} else {
		buf[i] = n%16 - 10 + 'a';
	}

	buf[i+1] = '\0';

	return;
}

void itoa(int n, char *buf)
{
	int i;
	if (n < 10) {
		buf[0] = n + '0';
		buf[1] = '\0';
		return;
	}

	itoa(n/10, buf);

	for (i = 0; buf[i] != '\0'; i++);

	buf[i] = n%10 + '0';
	buf[i+1] = '\0';

	return;
}

//%x, %d, %c, %s
int  uprintf(const char *fmt, ...)
{
	va_list va;

	int val;
	char buf[64];

	va_start(va, fmt);	

	while (*fmt) {
		if (*fmt == '%') {
			fmt++;
			switch (*fmt) {
			case 'c':
				uputchar(va_arg(va, int));
				break;
			case 's':
				uputs(va_arg(va, char *));
				break;
			case 'd':
				val = va_arg(va, int);
				if (val < 0) {
					uputchar('-');
					val = 0-val;
				}
				itoa(val, buf);
				uputs(buf);
				break;
			case 'x':
				val = va_arg(va, int);
				itox(val, buf);
				uputs(buf);
				break;
			}
		} else {
			uputchar(*fmt);
		}
	
		fmt++;
	}

	va_end(va);

	return 0;
}















