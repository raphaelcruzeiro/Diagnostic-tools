#include "info.h"

struct cpuinfo* cpuinfoMake()
{
    struct cpuinfo* info = malloc(sizeof(struct cpuinfo));
    return info;
}

void cpuinfoFree(struct cpuinfo* info)
{
    free(info);
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
    int count = 0;
    info->processors = 0;
    int gotProc, gotModel, gotMHz, gotCache;
    gotProc = gotModel = gotMHz = gotCache = 0;
    struct processor *proc = 0;
    while(fgets(line, 180, cpuinfo)) {
        char *delimiter = ":";
        char *label = strtok(line, delimiter);
        char *val = strtok(NULL, delimiter);
        if (val) {
            if(!proc)
                proc = malloc(sizeof(struct processor));
            delete_char(val, '\n', strlen(val));
            remove_whitespace(label, strlen(label));

            if(strcmp(label, "processor") == 0) {
                proc->processor = atoi(val);
                info->processors++;
                gotProc = 1;
            }
            else if(strcmp(label, "modelname") == 0) {
                strcpy(proc->modelname, val);
                gotModel = 1;
            }
            else if(strcmp(label, "cpuMHz") == 0) {
                proc->cpuMHz = strtod(val, NULL);
                gotMHz =1;
            }
            else if(strcmp(label, "cachesize") == 0) {
                proc->cachesize = atoi(val);
                gotCache = 1;
            }

            if(gotProc && gotModel && gotMHz && gotCache)  {
                info->procs[count] = *proc;
                count++;
                gotProc = gotModel = gotMHz = gotCache = 0;
                continue;
            }
        }
    }
    fclose(cpuinfo);
}

void get_stat(struct cpustat *st)
{
    FILE *_stat = fopen("/proc/stat", "r");
    char line[180];
    while(fgets(line, 180, _stat)) {
        char *delimiter = " ";
        char *cpu = strtok(line, delimiter);
        char *slice = 0;
    	int pos = 0;
        while(slice = strtok(NULL, delimiter)) {
            int val = atoi(slice);
            switch(pos) {
                case 0:
                    st->user = val;
                    break;
                case 1:
                    st->nice = val;
                    break;
                case 2:
                    st->system = val;
                    break;
                case 3:
                    st->idle = val;
                    break;
                case 4:
                    st->iowait = val;
                    break;
                case 5:
                    st->irq = val;
                    break;
                case 6:
                    st->softirq = val;
                    break;
            }
            pos++;
        }
        return;
    }
}
