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
    char *modelname;
    int cachesize;
    int cpucores;
    int coreid;
    double cpuMHz;
};

struct cpuinfo {
    int processors;
    struct processor *procs;
};

void addprocessor(struct cpuinfo *info, struct processor *proc);
void get_meminfo(struct meminfo *info);
void get_cpuinfo(struct cpuinfo *info);

#endif
