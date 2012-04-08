#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <string.h>
#include <ctype.h>

void remove_whitespace(char *src, int len);
void delete_char(char *src, char c, int len);
int is_empty(const char* str);

#endif
