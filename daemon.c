#include "daemon.h"
#include "info.h"
#include "serializer.h"
#include "comm.h"
#include <string.h>

void startDaemon()
{
    printf("Starting daemon...\n");

    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("Daemon successfully started!\n");
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }
    
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
    
    while (1) {
        struct diagnostics d;
        get_diagnostics(&d);

        char *xml;
        serialize(&d, login, password, xml);

        post(xml);

        freeXml(xml);
    
        sleep(60);
    }

    exit(EXIT_SUCCESS);
}
