#include <mmu.h>

static void mmu_enable(u32 *ttb)
{
	__asm__ __volatile__(


		"mcr p15, 0, %[ttb], c2, c0, 0\n\t"
		"mvn r0,#0\n\t"
		"mcr p15, 0, r0, c3, c0, 0\n\t"

		"mrc p15, 0, r0, c1, c0, 0\n\t"
		"orr r0,r0,#(0x1 << 13)\n\t"
		"orr r0,r0,#0x1\n\t"
		"mcr p15, 0, r0, c1, c0, 0"

		:
		:[ttb]"r"(ttb)
		:"r0"
	);
}

static void vector_map(u32 va_st, u32 va_ed, u32 pa, u32 *ttb)
{
	while(va_st < va_ed){
		create_descriptor(va_st, pa, ttb);
		va_st += 0x100000;
		pa    += 0x100000;	
	}
}

void init_ttb(u32 *ttb)
{
	vector_map(0x0, 0x8000000, 0x0, ttb);
	vector_map(0x8000000, 0x14000000, 0x8000000, ttb);
	vector_map(0x40000000, 0x80000000, 0x40000000, ttb );

	mmu_enable(ttb);
}
