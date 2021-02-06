#include <mmu.h>
#include <keyeint.h>
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

	irq_request_cpu0(KEY4INT, do_keys, 0);

	key_eint_init();

	return 0;
}

