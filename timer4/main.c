#include <mmu.h>
#include <timer4.h>
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
#define TIMER4INT 73

	timer4_init(3000);
	
	irq_request_cpu0(TIMER4INT, do_timer4, 0);

	return 0;
}

