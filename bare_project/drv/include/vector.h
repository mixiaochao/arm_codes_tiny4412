#ifndef VECTOR_H_
#define VECTOR_H_

#include <comm.h>

#define HIGH_VECTOR_VA_BASE 	0xffff0000

#define TTB 			0x41000000
#define VECTOR_BASE 		0x41800000

extern void build_vectors_table(u32 high_vector_pa_base);
extern u8 _start, _end;

#endif
