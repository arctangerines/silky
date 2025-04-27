// In a single C file add #define SILKY_IMPL

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#ifndef SILKY_H
#define SILKY_H

enum chartype
{
    WCHAR,
    CHAR,
};
struct silky;

uint8_t
slkcmp(wchar_t* str1, wchar_t* str2);

char*
slkwctochar(wchar_t* str);

wchar_t*
slkcat(wchar_t* str1, wchar_t* str2);

void
slkfree(wchar_t* str);

size_t
slkgetlen(wchar_t* str);

// size_t
// slklen(wchar_t* str);

wchar_t*
slkmemcpy(wchar_t* dest, wchar_t* src, size_t len);

wchar_t*
slkinit(wchar_t* string);

#endif // SILKY_H
