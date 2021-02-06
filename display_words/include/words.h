#ifndef XCM_WORDS_H_
#define XCM_WORDS_H_

#include <lib.h>

#define HIGH   97
#define WIDTH  13

extern void write_words(u32 x, u32 y, u8 wds[][97][13], u32 n);
extern u8 words[10][HIGH][WIDTH];


#endif
