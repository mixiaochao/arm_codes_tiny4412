#include <lib.h>
#include <mmu.h>

#define DEFINE_FUNC(N) \
		void func_##N(void)\
		{\
			printf("svc %d\n", N);\
		}

DEFINE_FUNC(9527);
DEFINE_FUNC(3856);
DEFINE_FUNC(7788);

void do_unde(void)
{

}

void do_svc(u32 imme)
{
	switch (imme) {
		case 9527:
			func_9527();
			break;
		case 3856:
			func_3856();
			break;
		case 7788:
			func_7788();
			break;
		default:
			break;
	}

}

int main(void)
{

	rebuild_vectors_table();		


	__asm__ __volatile__(
		
		".word 0x54546411\n\t"
		".word 0x45967111\n\t"
		".word 0x77777777\n\t"
		"svc #9527\n\t"
		"swi #3856\n\t"
		"swi #7788\n\t"
	);

	printf("come back to main...\n");

	return 0;
}

