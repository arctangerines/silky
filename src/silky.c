#include "silky.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// TODO: Function to convert from wchar_t to char and vice versa
// TODO: Function to compare strings


// TODO: Function to concatenate
wchar_t*
slkcat(wchar_t* str1, wchar_t* str2)
{
    // STEP: Get lens
    // STEP: malloc a new silky+str adding the 2 lens
    // STEP: memcpy(?) to the new str
}

enum chartype
{
    WCHAR,
    CHAR,
};
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


size_t
slklen(wchar_t* string)
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
    for (strc = string; *strc != '\0'; strc++);
    return strc - string;
}

// Implementation of silk mem copy
// FIXME: OK maybe we do need another member saying how much of the array is
// free
wchar_t*
slkmemcpy(wchar_t* dest, wchar_t* src, size_t len)
{
    wchar_t* deststr= dest;
    const wchar_t* srcstr = src;

    // more elegant and easier to digest
    while (len--)
    {
        *deststr++ = *srcstr++;
    }
    return dest;
}

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

int
main()
{
    wchar_t* mystr = slkinit(L"heyo");
    free((struct silky*)mystr - 1);
}
