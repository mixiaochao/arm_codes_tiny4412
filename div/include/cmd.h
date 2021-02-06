#ifndef XCM_CMD_H_
#define XCM_CMD_H_

#include <lib.h>

typedef struct {
	char *name;
	void (*func)(void);
	char *help;
}cmd_t;


extern cmd_t _misec_start;
extern cmd_t _misec_end;

#define ATTRIBUTE __attribute__ ((unused, section(".misec")))

#define DEFINE_CMD(nam, fun, hel) \
	cmd_t cmd_##nam ATTRIBUTE = {\
		.name = #nam,\
		.func = fun,\
		.help = hel\
	      }

extern void find_cmd_and_excute(const char *buf);

#endif
