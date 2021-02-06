#include <lib.h>
#include <mmu.h>


void do_unde(void)
{
	printf("undefined exception is occur...\n");
}

int main(void)
{

	rebuild_vectors_table();		


	__asm__ __volatile__(
		
		".word 0x54546411\n\t"
		".word 0x45967111\n\t"
		".word 0x77777777\n\t"
	);

	printf("come back to main...\n");

	return 0;
}

