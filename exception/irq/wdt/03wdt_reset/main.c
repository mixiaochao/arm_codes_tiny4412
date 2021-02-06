#include <mmu.h>
#include <wdt.h>
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

//	irq_request_cpu0(WDTID, do_wdt_timer, 0);

	wdt_reset_init(3000);

	return 0;
}

