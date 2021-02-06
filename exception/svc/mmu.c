#include <mmu.h>

/*
	ttb: 转换表的起始地址
	va_start: 要映射的虚拟起始
	va_end  : 要映射的虚拟结束
	pa	: 要映射的物理起始
*/
void section_map(u32 *ttb, u32 va_start, u32 va_end, u32 pa)
{
	while (va_start < va_end) {
		CREATE_DESCRIPTOR(ttb, va_start, pa);
		va_start += 0x100000;
		pa	 += 0x100000;
	}
}

/*对exynos4412上统一编址的地址做一对一线性映射*/
void init_global_map(u32 *ttb)
{
	memset(ttb, 0x0, 4096*4);

	section_map(ttb, 0x0, 0x0cd00000, 0x0);

	section_map(ttb, 0x0ce00000, 0x14000000, 0x0ce00000);

	section_map(ttb, 0x40000000, 0x80000000, 0x40000000);
}

void enable_mmu(u32 *ttb)
{
	__asm__ __volatile__(

		/*将转换表的起始地址写入C2*/
		"mcr p15, 0, %[ttb], c2, c0, 0\n\t"	

		/*设置所映射的内存域的权限为最大*/
		"mvn r0, #0\n\t"
		"mcr p15, 0, r0, c3, c0, 0\n\t"

		/*设置异常矢量基地址为高矢量地址，使能MMU*/
		"mrc p15, 0, r0, c1, c0, 0\n\t"
		"orr r0, r0, #(0x1 << 13)\n\t"
		"orr r0, r0, #0x1\n\t"
		"mcr p15, 0, r0, c1, c0, 0\n\t"

		:
		:[ttb]"r"(ttb)
		:"r0"
	);	
}

void rebuild_vectors_table(void)
{
	init_global_map(TTB);
	CREATE_DESCRIPTOR(TTB, 0xffff0000, 0x75000000);
	enable_mmu(TTB);
	memcpy((void *)0xffff0000, (void *)excep_start, excep_end - excep_start);
	
}
