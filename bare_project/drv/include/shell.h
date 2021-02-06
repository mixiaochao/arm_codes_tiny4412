#ifndef SHELL_H_
#define SHELL_H_

#define MYSECTION __attribute__ ((unused, section(".millet")))

typedef struct{
	char *name;
	int (*func)(int ,char**);
	char *help;
}cmd_t;

#define MYCMD(N, H)   cmd_t  N MYSECTION = {\
												.name = #N,\
												.func = N##ctrl,\
												.help = H\
						}

#endif
