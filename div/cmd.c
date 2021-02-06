#include <cmd.h>
#include <uart.h>

void do_led(void)
{
	uprintf("call %s\n", __func__);	
}
DEFINE_CMD(led, do_led, "control led cmd");


void do_beep(void)
{
	uprintf("call %s\n", __func__);	
}
DEFINE_CMD(beep, do_beep, "control beep cmd");



void find_cmd_and_excute(const char *buf)
{
	cmd_t *p = &_misec_start;
	while (p < &_misec_end) {
		if (strcmp(buf, p->name) == 0) {
			p->func();
			return;
		}
		p++;
	}
	
	uprintf("command: %s not find!\n", buf);	
}
