#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "daemon.h"
#include "info.h"
#include "comm.h"
#include "serializer.h"
#include "stringhelpers.h"

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        if (strcmp("--init-daemon", argv[i]) == 0) {
            FILE *f;
            if (f = fopen(".conf", "r")) {
                startDaemon(f);
            } else {
                printf("No configuration file present. Use --config.\n");
                exit(0);
            }
        }
        else if (strcmp("--config", argv[i]) == 0) {
            printf("Enter your login: ");
            char login[50];
            scanf("%s", login);
            printf("Enter your password: ");
            char password[50];
            scanf("%s", password);

            FILE *config = fopen(".conf", "w");
            char content[150];
            fprintf(config, "login:%s\n", login);
            fprintf(config, "password:%s\n", password);
            fclose(config);
            exit(0);
        }
        else if (strcmp("--test-connection", argv[i]) == 0) {
            FILE *config = fopen(".conf", "rt");

            char line[100];

            char login[50];
            char password[50];

             while(fgets(line, 100, config) != NULL) {
                 char *delimiter = ":";
                 char *label = strtok(line, delimiter);
                 char *value = strtok(NULL, delimiter);

                 delete_char(value, '\n', strlen(value));

                 if (strcmp(label, "login") != 0) {
                     strcpy(login, value);
                 }
                 else if (strcmp(label, "password") != 0) {
                     strcpy(password, value);
                 }
             }

             struct diagnostics d;
             get_diagnostics(&d);

             char xml[2048];
             serialize(&d, login, password, &xml);

             post(&xml);

             exit(0);
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
    struct cpustat st;
    get_stat(&st);

    int total = st.user + st.nice + st.system + st.idle + st.iowait + st.irq + st.softirq;
    double load = (total - st.idle) / (total / 100.0);
    printf("Total:%d\nIdle:%d\n", total, st.idle);
    printf("System load:%f%%\n", load);

    return 0;
}
