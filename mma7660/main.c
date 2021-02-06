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
	
	i2c_mma_eint25_init();	

	return 0;
}

