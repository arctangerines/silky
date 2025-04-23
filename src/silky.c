#include "silky.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

// So this string library is supposed to be compatible with regular string
// functions so we just wanna return the buffer but have a region that comes
// before the string that contains meta data, classic malloc pattern
// NOTE: I think this needs to be packed but not sure so i'm not going to do it
__attribute__((packed)) struct silky
{
    size_t len;
};
typedef struct silky slk;

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
//FIXME: OK maybe we do need another member saying how much of the array is
// free
void
slkmemcpy(wchar_t* dest, wchar_t* src, size_t len)
{
    const wchar_t* srcstr = src;
    // this is what we return since it maintains the starting value
    // what we pass is a copy thonk
    wchar_t* deststr = dest;

    // destination string metadata
    struct silky* destmd = (struct silky*)dest - 1;
    // the new string is larger
    // I dont like this sectiuon actually, makes things too complex
    // this is bad we are removing this
    if (len > destmd->len)
    {
        destmd =
            realloc(destmd, sizeof(struct silky) + (sizeof(wchar_t) * len + 1));
        dest = (wchar_t*)(destmd + 1);
        deststr = dest;
    }

    // If we do it after, we are gonna be putting it at undefined behaviour
    // the while(len--) stops at 0 but it subtracts 1 more time, so it wraps
    deststr[len] = '\0';

    // more elegant and easier to digest
    while (len--)
    {
        *dest++ = *srcstr++;
    }
}

wchar_t*
slkinit(wchar_t* string)
{
    size_t len   = slklen(string);
    slk*   s     = malloc(sizeof(slk) + (sizeof(wchar_t) * (len + 1)));
    s->len       = len;
    wchar_t* str = (void*)(s + 1); // add then cast
}

int
main()
{
}
