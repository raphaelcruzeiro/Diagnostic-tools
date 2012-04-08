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

struct processor {
    int processor;
    char modelname[60];
    int cachesize;
    int cpucores;
    int coreid;
    double cpuMHz;
};

struct cpuinfo {
    int processors;
    struct processor procs[20];
};

struct cpuinfo* cpuinfoMake();
void cpuinfoFree(struct cpuinfo* info);

void get_meminfo(struct meminfo *info);
void get_cpuinfo(struct cpuinfo *info);

#endif
