#include <mmu.h>
#include <irq.h>
#include <i2c.h>

void do_unde(void)
{

}

void do_svc(u32 imme)
{

}

int main(void)
{
	rebuild_vectors_table();		

	i2c_pending_test();	

	return 0;
}

