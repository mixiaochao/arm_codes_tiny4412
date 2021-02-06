#ifndef TIME_H_
#define TIME_H_

#include <rtc.h>

#define TIME_X 200
#define TIME_Y 190
extern void disrtctime(rtc_time_t *time);


extern void time_change();
extern void time_add();
extern void  time_sub();
extern void tp_time_menu();
#endif
