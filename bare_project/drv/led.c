#include <led.h>
#include <uart.h>
#include <display.h>
#include <lcd.h>

int led_flag = 0xf;

void led_on(int num)
{
	GPM4DAT &= ~(1<<(num-1));
}

void led_off(int num)
{
	GPM4DAT |= 1<<(num-1);
}
void all_led_on()
{
	GPM4DAT &= 0x0f;
}
void all_led_off()
{
	GPM4DAT |= 0x0f;
}
void led_init()
{
	GPM4CON |= 0x1111;//设置GPM4CON0～GPM4CON4为输出 
	all_led_off();
}

void led_control(int x,int y)
{

	if(x>=80&&x<180&&y>=150&&y<250)
	{
		if(led_flag & 1)
		{
			uprintf("led1 on");
			led_on(1);
			display_string(90,400,"*****",COL(211,92,21),0,4);
			display_string(90,400," ON  ",0xffffff,0,4);
		}
		else
		{
			uprintf("led1 off");
			led_off(1);
			
			display_string(90,400,"*****",COL(211,92,21),0,4);
			display_string(90,400," OFF ",0xffffff,0,4);
		}
		led_flag ^= 1;
	}
	else if(x>=250&&x<350&&y>=150&&y<250)
	{
		if(led_flag & 2)
		{
			uprintf("led2 on");
			led_on(2);
			display_string(280,400,"*****",COL(211,92,21),0,4);
			display_string(280,400," ON  ",0xffffff,0,4);
		}
		else
		{
			uprintf("led2 off");
			led_off(2);
			display_string(280,400,"*****",COL(211,92,21),0,4);
			display_string(280,400," OFF ",0xffffff,0,4);
		}
		led_flag ^=2;
	}
	if(x>=430&&x<530&&y>=150&&y<250)
	{
		if(led_flag & 4)
		{
			uprintf("led3 on");
			led_on(3);
			display_string(450,400,"*****",COL(211,92,21),0,4);
			display_string(450,400," ON  ",0xffffff,0,4);
		}
		else
		{
			uprintf("led3 off");
			led_off(3);
			display_string(450,400,"*****",COL(211,92,21),0,4);
			display_string(450,400," OFF ",0xffffff,0,4);
		}
		led_flag ^= 4;
	}
	if(x>=630&&x<720&&y>=150&&y<250)
	{
		if(led_flag & 8)
		{
			uprintf("led4 on");
			led_on(4);
			display_string(650,400,"*****",COL(211,92,21),0,4);
			display_string(650,400," ON  ",0xffffff,0,4);
		}
		else
		{
			uprintf("led4 off");
			led_off(4);
			display_string(650,400,"*****",COL(211,92,21),0,4);
			display_string(650,400," OFF ",0xffffff,0,4);
		}
		led_flag ^= 8;
	}
}

