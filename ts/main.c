#include <mmu.h>
#include <irq.h>
#include <iic.h>
#include <tp.h>

void do_unde(void)
{

}

void do_svc(u32 imme)
{

}

int main(void)
{
	
	rebuild_vectors_table();
	
	tp_int_init();


	return 0;
}

