// In a single C file add #define SILKY_IMPL

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// FIXME: I kinda lowkey highkey hate that its a single header library
#ifndef SILKY_H

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

size_t
slklen(wchar_t* str);

wchar_t*
slkmemcpy(wchar_t* dest, wchar_t* src, size_t len);

wchar_t*
slkinit(wchar_t* string);
#define SILKY_H

#endif // SILKY_H

#ifdef SILKY_IMPL
// So this string library is supposed to be compatible with regular string
// functions so we just wanna return the buffer but have a region that comes
// before the string that contains meta data, classic malloc pattern
// NOTE: I think this needs to be packed but not sure so i'm not going to do it
struct silky
{
    size_t len;
    // Extra spaces in the alloc'd string
    // functions to apply to this: slklen, it should update the value
    // slkmemcpy
    size_t extra;
};

/// String comparison function
uint8_t
slkcmp(wchar_t* str1, wchar_t* str2)
{
    struct silky* s1 = (struct silky*)str1 - 1;
    struct silky* s2 = (struct silky*)str2 - 1;
    if (s1->len != s2->len) return 0;
    for (size_t i = 0; i < s1->len; i++)
    {
        if (str1[i] != str2[i]) return 0;
    }
    return 1;
}

/// Convert from wide char string to a chill normal guy (char) string
char*
slkwctochar(wchar_t* str)
{
    struct silky* s       = (struct silky*)str - 1;
    char*         charstr = malloc(sizeof(char) * s->len + 1);
    charstr[s->len]       = '\0';
    for (size_t i = 0; i < s->len; i++)
    {
        charstr[i] = (char)(str[i]);
    }
    return charstr;
}

/// Concat 2 silky strings together
///
/// it doesn't meow
///
/// FIXME: I think i need to find a way to use memcpy on this
wchar_t*
slkcat(wchar_t* str1, wchar_t* str2)
{
    // STEP: Get lens
    struct silky* str1md = (struct silky*)str1 - 1;
    size_t        len1   = str1md->len;
    struct silky* str2md = (struct silky*)str2 - 1;
    size_t        len2   = str2md->len;

    // STEP: malloc a new silky+str adding the 2 lens
    struct silky* s =
        malloc(sizeof(struct silky) + (sizeof(wchar_t) * (len1 + len2 + 1)));
    // STEP: memcpy(?) to the new str
    // XXX: perhaps we can use memcpy and an offset
    wchar_t* str     = (wchar_t*)(s + 1);
    s->len           = len1 + len2;
    str[len1 + len2] = '\0';
    for (size_t i = 0; i < len1; i++)
    {
        str[i] = str1[i];
    }
    for (size_t lenlen = len1; lenlen < len1 + len2; lenlen++)
        for (size_t i = 0; i < len2; i++)
        {
            str[len1 + i] = str2[i];
        }
    return str;
}
/// Free the silky string
///
/// yk, its free
void
slkfree(wchar_t* str)
{
    struct silky* s = (struct silky*)str - 1;
    free(s);
}

/// Get the length of a string
size_t
slkgetlen(wchar_t* str)
{
    struct silky* s = (struct silky*)str - 1;
    return s->len;
}

/// Get the length of a string by looping, internal use only
size_t
slklen(wchar_t* str)
{
    wchar_t* strc;
    /* So pretty clever pattern thats very common
     * Since with pointer arithmetic you can do ++ or add + 1 and the pointer
     * will move 1 n sized place (the n depends of type it points to)
     * so if its a char itll move 1 byte if its a long long int, the pointer
     * will move 8 bytes
     * but if you subtract the ending pointer with the starting pointer
     * it will not give you the bytes it moved,
     * it will give you the number of PLACES it moved
     */
    for (strc = str; *strc != '\0'; strc++);
    return strc - str;
}

// Implementation of silk mem copy
// FIXME: OK maybe we do need another member saying how much of the array is
// free
wchar_t*
slkmemcpy(wchar_t* dest, wchar_t* src, size_t len)
{
    wchar_t*       deststr = dest;
    const wchar_t* srcstr  = src;

    // more elegant and easier to digest
    while (len--)
    {
        *deststr++ = *srcstr++;
    }
    return dest;
}

/// Create a new silky string
///
/// NOTE: Kinda wanna change it to slkmake
wchar_t*
slkinit(wchar_t* string)
{
    size_t        len = slklen(string);
    struct silky* s =
        malloc(sizeof(struct silky) + (sizeof(wchar_t) * (len + 1)));
    s->len       = len;
    wchar_t* str = (wchar_t*)(s + 1); // add then cast
    slkmemcpy(str, string, len);
    return str;
}
#endif //SILKY_IMPL
