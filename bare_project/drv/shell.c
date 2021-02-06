#include <shell.h>
#include <uart.h>
#include <string.h>
#include <led.h>
#include <buzzer.h>
#include <wdt.h>
int ledctrl(int argc,char *argv[])
{
//	if(strcmp("1",argv[1]))

	//int i;
	//for(i=0;i<3;i++)
	//	uprintf("argv[%d] = %s\n",i,argv[i]);
	int val = atoi(argv[1]);
	if((val<0&&val>5) || argc != 3)
	{

		uprintf("%s\n","led command is error");
		uprintf("%s\n","led help:led <num> <on/off>");
		return 0;
	}
	if(!strcmp(argv[2],"on"))
	{
		led_on(val);
	}
	else if(!strcmp(argv[2],"off"))
	{
		led_off(val);
	}else
	{
		uprintf("%s\n","led command is error");
		uprintf("%s\n","led help:led <num> <on/off>");
		return 0;
	}
//	uprintf("led on/off!!\n");
	return 1;
}
MYCMD(led, "led help: led 1 on\n");

int buzzerctrl(int argc,char *argv[])
{

	//int i;
	//for(i=0;i<3;i++)
	//	uprintf("argv[%d] = %s\n",i,argv[i]);
	if(!strcmp(argv[1],"on"))
	{
		buzzer_didi();
	}
	else if(!strcmp(argv[1],"off"))
	{
		buzzer_close();
	}
	else
	{
		uprintf("%s\n","buzzer command is error");
		uprintf("%s\n","buzzer help:buzzer <on/off>");
		return 0;
	}
	//uprintf("buzzer on/off!!\n");
	return 1;
}
MYCMD(buzzer, "buzzer help: nothing!\n");


int lsctrl(int argc,char *argv[])
{
	uprintf("gobang\n");
	uprintf("time\n");
	uprintf("gallery\n");
	uprintf("led\n");
	uprintf("wathdog\n");
	uprintf("buzzer\n");
	uprintf("calendar\n");
	uprintf("ADC\n");
	return 1;
}
MYCMD(ls, "ls help: nothing!\n");

#if 1
int resetctrl(int argc,char *argv[])
{
	wdt_init(5000);
	uprintf("after 5 second the system will reset...\n");
	return 1;
}
MYCMD(reset, "reset help: nothing!\n");

#endif
