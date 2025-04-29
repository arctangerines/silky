#include "silky.h"
//TODO: Check that nothing works by just looking for nul and actually
// handles things with length

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
slkcmp(char* str1, wchar_t* str2)
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

/// Concat 2 silky strings together
///
/// it doesn't meow
///
/// FIXME: I think i need to find a way to use memcpy on this
char*
slkcat(char* str1, char* str2)
{
    // STEP: Get lens
    struct silky* str1md = (struct silky*)str1 - 1;
    size_t        len1   = str1md->len;
    struct silky* str2md = (struct silky*)str2 - 1;
    size_t        len2   = str2md->len;

    // STEP: malloc a new silky+str adding the 2 lens
    struct silky* s =
        malloc(sizeof(struct silky) + (sizeof(char) * (len1 + len2 + 1)));
    // STEP: memcpy(?) to the new str
    // XXX: perhaps we can use memcpy and an offset
    char* str     = (char*)(s + 1);
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
/// Get the length of a string
size_t
slkgetlen(char* str)
{
    struct silky* s = (struct silky*)str - 1;
    return s->len;
}

/// Get the length of a string by looping, internal use only
size_t
slklen(char* str)
{
    char* strc;
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
char*
slkmemcpy(char* dest, char* src, size_t len)
{
    char*       deststr = dest;
    const char* srcstr  = src;

    // more elegant and easier to digest
    while (len--)
    {
        *deststr++ = *srcstr++;
    }
    return dest;
}

/// Free the silky string
///
/// yk, it's free
void
slkfree(char* str)
{
    struct silky* s = (struct silky*)str - 1;
    free(s);
}


/// Create a new silky string
///
/// NOTE: Kinda wanna change it to slkmake
///TODO: we should perhaps allocate a buffer of a bigger size than just the string
/// so we dont have to alloc so much?
char*
slkinit(char* string)
{
    size_t        len = slklen(string);
    struct silky* s =
        malloc(sizeof(struct silky) + (sizeof(char) * (len + 1)));
    s->len       = len;
    char* str = (char*)(s + 1); // add then cast
    slkmemcpy(str, string, len);
    return str;
}
