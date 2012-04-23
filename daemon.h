#ifndef DAEMON_H
#define DEAMON_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void startDaemon(FILE *config);

#endif
