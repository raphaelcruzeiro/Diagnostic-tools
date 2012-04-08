#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <stdlib.h>
#include "stringhelpers.h"

struct meminfo {
    int memtotal;
    int memfree;
    int buffers;
    int cached;
    int swapcached;
    int active;
    int inactive;
};

void get_meminfo(struct meminfo *info);

#endif
