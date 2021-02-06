#include <vectors.h>
#include <tp.h>
#include <timer.h>
#include <irq.h>

int main(void)
{
	build_vectors();

	tp_int_init();

	irq_request_cpu0_(TIMER4, do_timer4, 0);
	
	timer4_init(20);

	return 0;
}
