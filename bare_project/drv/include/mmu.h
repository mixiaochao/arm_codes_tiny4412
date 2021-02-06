#ifndef MMU_H_
#define MMU_H_

#include <comm.h>

#define create_descriptor(va, pa, ttb) \
			ttb[va>>20] = ((pa&0xfff00000) | 0x2)


extern void init_ttb(u32 *ttb);

#endif

