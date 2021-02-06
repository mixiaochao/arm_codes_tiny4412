#ifndef XCM_UART_H_
#define XCM_UART_H_

#include <lib.h>

#define GPA0CON 	*((volatile u32 *)0x11400000)

#define UART0BASE	0x13800000

#define ULCONn		*((volatile u32 *)(UART0BASE + 0x0000)) 
#define UCONn 		*((volatile u32 *)(UART0BASE + 0x0004)) 
#define UFCONn		*((volatile u32 *)(UART0BASE + 0x0008)) 
#define UMCONn		*((volatile u32 *)(UART0BASE + 0x000C)) 
#define UTRSTATn	*((volatile u32 *)(UART0BASE + 0x0010)) 
#define UERSTATn	*((volatile u32 *)(UART0BASE + 0x0014)) 
#define UFSTATn 	*((volatile u32 *)(UART0BASE + 0x0018)) 
#define UMSTATn 	*((volatile u32 *)(UART0BASE + 0x001C)) 
#define UTXHn 		*((volatile u32 *)(UART0BASE + 0x0020)) 
#define URXHn 		*((volatile u32 *)(UART0BASE + 0x0024)) 
#define UBRDIVn 	*((volatile u32 *)(UART0BASE + 0x0028)) 
#define UFRACVALn 	*((volatile u32 *)(UART0BASE + 0x002C)) 
#define UINTPn 		*((volatile u32 *)(UART0BASE + 0x0030)) 
#define UINTSPn 	*((volatile u32 *)(UART0BASE + 0x0034)) 
#define UINTMn 		*((volatile u32 *)(UART0BASE + 0x0038)) 

extern void uart0_init(void);
extern void uputchar(int ch);
extern int  ugetchar(void);
extern char *ugets(char *buf);
extern void uputs(const char *buf);
extern void uputs_(const char *buf);
extern int  uprintf(const char *fmt, ...);

#endif
