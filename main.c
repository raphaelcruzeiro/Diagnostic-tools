#include <stdio.h>
#include "info.h"

int main(int argc, char *argv[])
{
    struct meminfo info;
    get_meminfo(&info);

    printf("Total memory: %d\n", info.memtotal);
    printf("Free memory: %d\n", info.memfree);

    return 0;
}
