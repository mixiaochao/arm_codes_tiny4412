#include <shell.h>
#include <uart.h>
#include <string.h>
#include <led.h>

int ledctrl(int argc,char *argv[])
{
//	if(strcmp("1",argv[1]))

	int i;
	for(i=0;i<3;i++)
		uprintf("argv[%d] = %s\n",i,argv[i]);
	int val = atoi(argv[1]);
	if(val<0&&val>5 || argv != 3)
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
	uprintf("led on/off!!\n");
	return 1;
}
MYCMD(led, "led help: led 1 on\n");





int buzzerctrl(int argc,char *argv[])
{
	uprintf("buzzer on/off!!\n");
	return 1;
}
MYCMD(buzzer, "buzzer help: nothing!\n");
	
