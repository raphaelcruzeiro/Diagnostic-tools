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

struct cpustat {
    int user;
    int nice;
    int system;
    int idle;
    int iowait;
    int irq;
    int softirq;
};

struct cpuinfo {
    int processors;
    struct processor procs[20];
};

struct diagnostics {
    long time;
    struct meminfo memory;
    struct cpustat cpustatus;
    struct cpuinfo cpu;
};

struct cpuinfo* cpuinfoMake();
void cpuinfoFree(struct cpuinfo* info);

void get_meminfo(struct meminfo *info);
void get_cpuinfo(struct cpuinfo *info);
void get_stat(struct cpustat *st);

void get_diagnostics(struct diagnostics *d);
void freeDiagnostics(struct diagnostics *d);

#endif
