#include <uart.h>
#include <display.h>

#define WAIT_BUFFER_EMPTY while(!(UTRSTATn&0x2))
#define WAIT_BUFFER_FULL  while(!(UTRSTATn&0x1))

int stdout_flag = 1;
void uart0_init(void)
{
	GPA0CON &= ~0xff;
	GPA0CON |= 0x22;	

	ULCONn = 0x3;
	UCONn = (0x1 << 2) | (0x1 << 0);		
	UFCONn = 0;
	UMCONn = 0;

	UBRDIVn = 53;
	UFRACVALn = 4;

	CLK_SRC_PERIL0 &= ~0xf;
	CLK_SRC_PERIL0 |= 0x6;

	CLK_DIV_PERIL0 &= ~0xf;
	CLK_DIV_PERIL0 |= 0x7;	
}

void uputchar(int c)
{
	WAIT_BUFFER_EMPTY;

	UTXHn = c;	

	if(c == '\n'){
		uputchar('\r');
	}

//#define STDOUT
//#ifdef STDOUT
	if(stdout_flag == 1)
		lcd_stdout(c);
//#endif 
}


int ugetchar(void)
{	
	int c;
	
	WAIT_BUFFER_FULL;

	c = URXHn;

	if(c == '\r'){
		c = '\n';
	}

	uputchar(c);

	return c;
}

void uputs_(const char *str)
{
	while(*str){
		uputchar(*str++);
	}	
}

void uputs(const char *str)
{
	uputs_(str);
	uputchar('\n');
}

char *ugets(char *buf)
{
	int c;
	char *tmp = buf;

	while((c = ugetchar()) != '\n'){
		*buf++ = c;
	}

	*buf = '\0';

	return tmp;
} 

static void itod(unsigned int num, char *buf)
{
	int i;

	if(num < 10){
		buf[0] = num + '0';
		buf[1] = '\0';
		return;
	}

	itod(num/10, buf);

	for(i = 0; buf[i] != '\0'; i++);

	buf[i] = num%10 + '0';
	buf[i+1] = '\0';
}

//abcdef --> "abcdef"
static void itox(unsigned int num, char *buf)
{
	int i;

	if(num < 16){
		if(num > 9){
			buf[0] = num - 10 + 'a';
		}else{
			buf[0] = num + '0';
		}

		buf[1] = '\0';

		return;
	}

	itox(num/16, buf);

	for(i = 0; buf[i] != '\0'; i++);

	if((num%16) > 9){
		buf[i] = num%16 - 10 + 'a';
	}else{
		buf[i] = num%16 + '0';
	}	

	buf[i+1] = '\0';
}

int uprintf(const char *fmt, ...)
{
	int hex;
	char buf[16];

	uva_list pa;

	uva_start(pa, fmt);	

	while(*fmt){
		
		if(*fmt != '%'){
			uputchar(*fmt);
		}else{
			fmt++;
			switch(*fmt){
				case 'c':
					uputchar(uva_arg(pa, int));
					break;
				case 's':
					uputs_(uva_arg(pa, char *));
					break;
				case 'd':
					hex = uva_arg(pa, int);
					if(hex < 0){
						uputchar('-');
						hex = 0 - hex;
					}	
					itod(hex, buf);
					uputs_(buf);				
					break;
				case 'x':
					hex = uva_arg(pa, int);
					itox(hex, buf);
					uputs_(buf);	
					break;
				default:
					break;
			}	
		}

		fmt++;
	}

	uva_end(pa);

	return 0;
}









