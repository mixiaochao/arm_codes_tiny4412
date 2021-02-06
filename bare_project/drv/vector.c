#include <vector.h>
#include <mmu.h>
#include <lib.h>

void build_vectors_table(u32 high_vector_pa_base)
{
	create_descriptor(HIGH_VECTOR_VA_BASE, high_vector_pa_base, ((u32 *)TTB));

	init_ttb((u32 *)TTB);		

	mymemcpy((void *)HIGH_VECTOR_VA_BASE, (void *)&_start, (&_end - &_start) + 1);
}
