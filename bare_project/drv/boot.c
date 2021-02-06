#include <display.h>
#include <lcd.h>
#include <boot.h>
#include <uart.h>
#include <timer.h>
#include <tp.h>
#include <isr.h>
#include <key.h>
#include <led.h>
#include <rtc.h>
#include <shell.h>
#include <string.h>
static char cmd[128];
extern int stdout_flag;
extern int points;
extern int num;
int boot_flag = 0;

char buf[12]={};
char buf2[12]={};
char buf3[12]={};
char *argv[5];
int argc = 0;
static void str_parse(char *cmd)
{
	int i ;
	for(i = 0;cmd[i] != '\0';i++)
	{
		if(cmd[i] == ' ')
			argc++;		
	}
	argc++;

	if(argc == 1)
	{
		argv[0] = cmd;
		argv[1] = "\0";
		argv[2] = "\0";
	}

	if(argc == 2)
	{
		char *p = buf;
		argv[0] = buf;
		while(*cmd != ' ')
		{
			*p = *cmd;
			p++;
			cmd++;
		}
		*p = '\0';
		cmd++;
		
		char *p2 = buf2;
		argv[1] = buf2;
		while(*cmd != '\0')
		{
			*p2 = *cmd;
			 p2++;
			 cmd++;
		}
		*p2 = '\0';
	}

	if(argc == 3)
	{
		char *p = buf;
		argv[0] = buf;
		while(*cmd != ' ')
		{
			*p = *cmd;
			p++;
			cmd++;
		}
		*p = '\0';
		cmd++;
		
		char *p2 = buf2;
		argv[1] = buf2;
		while(*cmd != ' ')
		{
			*p2 = *cmd;
			 p2++;
			 cmd++;
		}
		*p2 = '\0';
		cmd++;

		char *p3 = buf3;
		argv[2] = buf3;
		while(*cmd != '\0')
		{
			*p3 = *cmd;
			p3++;
			cmd++;
		}
		*p3 = '\0';
	}
}


extern cmd_t millet_start, millet_end;

static void boot_loader()
{
	clean_screen(0x000000);//清除0x52000000
	cmd_t *p = &millet_start;
	while(1)
	{
		uprintf("[Cortex@007]# ");
		argv[0] = "\0";
		argv[1] = "\0";
		argv[2] = "\0";
		argc = 0;
		ugets(cmd);
		str_parse(cmd);
		for(p = &millet_start; p < &millet_end; p++)
		{
			
			if(!strcmp(argv[0], p->name))
			{	
				p->func(argc,argv);
			}
		}
//		uprintf("%s\n",cmd);
		if(!strcmp(argv[0],"quit"))
	//	if(cmd[0] == 'q')
			break;
	}
	TINT_CSTAT |= (1 << 0);//enable timer0
	boot_view();
	boot_flag = 1;
}

void boot_view()
{
	clean_screen(0x000000);
	
	display_string(0,0,"The system is starting ...",0xffffff,-1,0);
	display_string(0,22,"Initializing the MMU ...",0xffffff,-1,0);

	rtc_time_t time = {
		.yea = 15,
		.mon = 10,
		.date = 15,
//		.week = 1,
		.hor  = 13,
		.min  = 52,
		.sec  = 0
	};
	tp_int_init();//初始化触摸屏
	timer0_init(500);
	display_string(0,44,"Initializing the timer is completed",0xffffff,-1,0);
	led_init();
	setrtctime(&time);	
	eint_key();
	display_string(0,66,"Initializing the key is completed",0xffffff,-1,0);

	display_string(100,100,"+-------------------------------------------------+",0xffffff,-1,0);
	display_string(100,122,"|  Welcome to 007System. The development of system|",0xffffff,-1,0);
	display_string(100,144,"|is based on ARM architecture.Thanks for Mr Mi and|",0xffffff,-1,0);
	display_string(100,166,"|my classmates which give our help.This system is |",0xffffff,-1,0);
	display_string(100,188,"|only used for study and communication.           |",0xffffff,-1,0);
	display_string(100,210,"|  The development team members are Songze Lee    |",0xffffff,-1,0);
	display_string(100,232,"|Shuchao Wang, Ning Cheng and Rui Ma.             |",0xffffff,-1,0);
	display_string(100,254,"+-------------------------------------------------+",0xffffff,-1,0);


	display_string(0,280,"5 seconds after entering the 007System......",0xffffff,-1,0);
	display_string(0,302,"If you touch the monitor with more than three fingers,",0xffffff,-1,0);
	display_string(0,324,"the system will enter the shell command line mode.",0xffffff,-1,0);
	while(1)
	{
		if(points >= 2)
		{
		//	printf("points:%d",points);
			TINT_CSTAT &= ~(1 << 0);//disable timer0
			num = 0;
			points = 0;
			boot_loader();
		}
		if (num > 10)
			break;
	}
	boot_flag = 1;
	stdout_flag = 0;
	rtc_tic_init(1000);
}
