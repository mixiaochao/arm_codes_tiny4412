#ifndef STRING_H_
#define STRING_H_



extern int strlen(const char *s);
extern char *strcpy(char *dst,const char *src);
extern char *strcat(char *dst,const char *src);
extern int strcmp(const char *s1,const char *s2);	
extern char *itos(unsigned int num, char *buf);

extern int atoi(const char *str);
#endif
