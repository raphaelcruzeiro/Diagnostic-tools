#include "stringhelpers.h"

void remove_whitespace(char *src, int len)
{
    char* dest = src;
    while(*src != '\0') {
        if (!isspace(*src))
            *dest++ = *src;
        src++;
    }
    *dest = 0;
}

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

int is_empty(const char* str)
{
    while(*str != '\0') {
        if (!isspace(*str)) return 0;
        str++;
    }

    return 1;
}
