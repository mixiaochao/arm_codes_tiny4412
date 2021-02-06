#include <lib.h>
#include <mmu.h>

int main(void)
{
	u32 *ttb = (void *)0x76000000;
	u32 *pa = (void *)0x62001230;

	*pa = 0x95273856;

	init_global_map(ttb);
	CREATE_DESCRIPTOR(ttb, 0xfff01230, 0x62001230);
	CREATE_DESCRIPTOR(ttb, 0xabc01230, 0x62001230);
	CREATE_DESCRIPTOR(ttb, 0xcba01230, 0x62001230);

	enable_mmu(ttb);

	printf("*pa = %#x\n", *pa);
	printf("*(u32 *0xfff01230) = %#x\n", *((u32 *)0xfff01230));
	printf("*(u32 *0xabc01230) = %#x\n", *((u32 *)0xabc01230));
	printf("*(u32 *0xcba01230) = %#x\n", *((u32 *)0xcba01230));
	

	return 0;
}

