#include "info.h"

void addprocessor(struct cpuinfo *info, struct processor *proc)
{
    if (!info->procs) {
        info->procs = (struct processor*) malloc(sizeof(struct processor));
        info->procs[0] = *proc;
        return;
    }

    int lenght = sizeof(struct processor)  * (sizeof(info->procs) / sizeof(struct processor));
    info->procs = (struct processor*) realloc(info->procs, sizeof(struct processor*) * 3 + lenght);
    info->procs [lenght] = *proc;
}

void get_meminfo(struct meminfo *info)
{
    FILE *meminfo = fopen("/proc/meminfo", "r");

    char line[180];

    while(fgets(line, 180, meminfo)) {
        char *delimiter = ":";
        char *label = strtok(line, delimiter);
        char *value = strtok(NULL, delimiter);

        int val = atoi(value);
        if(strcmp(label, "MemTotal") == 0) {
            info->memtotal = val;
        }
        else if(strcmp(label, "MemFree") == 0) {
            info->memfree = val;
        }
        else if(strcmp(label, "Buffers") == 0) {
            info->buffers = val;
        }
        else if(strcmp(label, "Cached") == 0) {
            info->cached = val;
        }
        else if(strcmp(label, "SwapCached") == 0) {
            info->swapcached = val;
        }
        else if(strcmp(label, "Active") == 0) {
            info->active = val;
        }
        else if(strcmp(label, "Inactive") == 0) {
            info->inactive = val;
        }
    }

    fclose(meminfo);
}

void get_cpuinfo(struct cpuinfo *info)
{
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");

    char line[180];

    while(fgets(line, 180, cpuinfo)) {
        struct processor proc;
        char *delimiter = ":";
        char *label = strtok(line, delimiter);
        char *val = strtok(NULL, delimiter);
        delete_char(val, '\n', strlen(val));
        delete_char(label, ' ', strlen(label));

        if(strcmp(label, "processor") == 0) {
            proc.processor = atoi(val);
        }
        else if(strcmp(label, "modelname") == 0) {
            proc.modelname = val;
        }
        else if(strcmp(label, "cpuMHz") == 0) {
            proc.cpuMHz = strtod(val, NULL);
        }
        else if(strcmp(label, "cachesize") == 0) {
            proc.cachesize = atoi(val);
        }

        addprocessor(info, &proc);
    }

    fclose(cpuinfo);
}
