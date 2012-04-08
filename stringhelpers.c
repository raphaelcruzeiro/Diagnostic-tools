#include "stringhelpers.h"

void delete_char(char *src, char c, int len)
{
    char *dest;
    int i;

    if(!c) return;

    if(len <= 0) len = 1024;

    dest = src;

    for(i = 0; i < len && *src != 0; i++, src++) {
        if(*src != c)
            *dest++ = *src;
    }

    *dest = 0;

    return;
}

