#include "daemon.h"
#include "info.h"
#include "serializer.h"
#include "comm.h"
#include <string.h>
#include <syslog.h>

void startDaemon(FILE *config)
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

    openlog("diagnostics_tool", LOG_NDELAY, LOG_USER);
    syslog(LOG_INFO, "Daemon running...");

    syslog(LOG_DEBUG, "Opened conf file. %d", config);

    char line[100];

    char login[50];
    char password[50];
    
    while(fgets(line, 100, config) != NULL) {
        syslog(LOG_DEBUG, "loop");
        char *delimiter = ":";
        char *label = strtok(line, delimiter);
        char *value = strtok(NULL, delimiter);

        delete_char(value, '\n', strlen(value));

        syslog(LOG_DEBUG, "Getting auth info...");        

        if (strcmp(label, "login") != 0) {
            strcpy(login, value);
        }
        else if (strcmp(label, "password") != 0) {
            strcpy(password, value);
        }
    }
    
    syslog(LOG_DEBUG, "Got authentication information.");

    while (1) {
        struct diagnostics d;
        get_diagnostics(&d);

        char xml[2048];
        serialize(&d, login, password, &xml);

        post(&xml);

        syslog(LOG_INFO, "Posting...");

        sleep(60);
    }

    exit(EXIT_SUCCESS);
}
