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

    return 0;
}
