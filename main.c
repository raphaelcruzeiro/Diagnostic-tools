#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "daemon.h"
#include "info.h"

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        if (strcmp("--init-daemon", argv[i]) == 0) {
            startDaemon();
        }
    }

    struct meminfo info;
    get_meminfo(&info);

    printf("Total memory: %d\n", info.memtotal);
    printf("Free memory: %d\n", info.memfree);

    struct cpuinfo *cinfo;
    cinfo = cpuinfoMake();
    get_cpuinfo(cinfo);
    printf("Processor number: %d\n", cinfo->processors);

    for(i = 0; i < cinfo->processors; i++) {
        printf("Model name: %s\n", cinfo->procs[i].modelname);
        printf("Frequency: %f MHz\n", cinfo->procs[i].cpuMHz);
    }

    cpuinfoFree(cinfo);
    return 0;
}
