#ifndef UART_H_
#define UART_H_

#include <comm.h>

#define GPA0CON	*((u32 *)0x11400000)

#define ULCONn		*((u32 *)0x13800000) 
#define UCONn 		*((u32 *)0x13800004) 
#define UFCONn		*((u32 *)0x13800008) 
#define UMCONn		*((u32 *)0x1380000C) 
#define UTRSTATn	*((u32 *)0x13800010) 
#define UERSTATn	*((u32 *)0x13800014) 
#define UFSTATn 	*((u32 *)0x13800018) 
#define UMSTATn 	*((u32 *)0x1380001C) 
#define UTXHn 		*((u32 *)0x13800020) 
#define URXHn 		*((u32 *)0x13800024) 
#define UBRDIVn 	*((u32 *)0x13800028) 
#define UFRACVALn 	*((u32 *)0x1380002C) 
#define UINTPn 		*((u32 *)0x13800030) 
#define UINTSPn 	*((u32 *)0x13800034) 
#define UINTMn 		*((u32 *)0x13800038) 

extern void uart0_init(void);
extern void uputchar(int c);
extern int ugetchar(void);
extern void uputs_(const char *str);
extern void uputs(const char *str);
extern char *ugets(char *buf);
extern int uprintf(const char *fmt, ...);

typedef char * uva_list;

#define uva_start(pa, num) (pa = (char *)(&num) + sizeof(num))

#define uva_arg(pa, type)  ({\
				type val;\
				val = *((type *)pa);\
				pa += 4;\
				val;})
#define uva_end(pa)	(pa = NULL)

#endif
