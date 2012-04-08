#include "info.h"

void get_meminfo(struct meminfo *info)
{
    FILE *meminfo = fopen("/proc/meminfo", "r");

    char line[180];

    while(fgets(line, 180, meminfo)) {
        char *delimiter = ":";
        char *label = strtok(line, delimiter);
        char *value = strtok(NULL, delimiter);
        delete_char(value, '\n', strlen(value));
        delete_char(value, 'k', strlen(value));
        delete_char(value, 'B', strlen(value));
        delete_char(value, ' ', strlen(value));
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
