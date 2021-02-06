#ifndef XCM_MMU_H_
#define XCM_MMU_H_

#include <lib.h>

/*
	TTB是段映射的转换表的起始地址
	VA是要映射的虚拟地址
	PA是要映射的物理地址
*/
#define CREATE_DESCRIPTOR(TTB, VA, PA)\
			TTB[VA>>20] = ((PA&0xfff00000) | 0x2)

/*
	ttb是转换表的起始地址
	va_start, va_end代表将要被映射的虚拟起始地址和结束地址
	pa是被映射到的物理起始地址
	  
*/
extern void section_map(u32 *ttb, u32 va_start, u32 va_end, u32 pa);
extern void init_global_map(u32 *ttb);
extern void enable_mmu(u32 *ttb);


#endif
