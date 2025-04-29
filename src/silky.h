#ifndef SILKY_H
#define SILKY_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * NOTE: Reading some GNU docs, and other relevant info on strings and chars
 * and whatnot, it's in general better to use char* if we cant make any asurance
 * about the types (meaning utf8, utf16, utf32) that we will be reading, so
 * goodbye wchar_t, you were too inconsistent for me...
 */

struct silky;

uint8_t
slkcmp(char* str1, wchar_t* str2);

char*
slkcat(char* str1, char* str2);

void
slkfree(char* str);

size_t
slkgetlen(char* str);

// size_t
// slklen(char* str);

char*
slkmemcpy(char* dest, char* src, size_t len);

char*
slkinit(char* string);

#endif // SILKY_H
