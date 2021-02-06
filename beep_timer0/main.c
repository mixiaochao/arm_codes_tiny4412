#include <mmu.h>
#include <timer.h>
#include <irq.h>

void do_unde(void)
{

}

void do_svc(u32 imme)
{

}

int main(void)
{

	rebuild_vectors_table();		

	beep_set_hz(1);
//	irq_request_cpu0(TIMER4INT, do_timer4, 0);

	return 0;
}

