all: diagnostics_tool

CC = gcc
CFLAGS = -g -Wall -ansi
LIBS = -lssl -lxml2
INCLUDE = -I/usr/include/libxml2

diagnostics_tool: main.o info.o stringhelpers.o daemon.o comm.o serializer.o
	$(CC) -o diagnostics_tool main.o info.o stringhelpers.o daemon.o comm.o serializer.o $(LIBS)

main.o: main.c info.h daemon.h comm.h
	$(CC) $(CFLAGS) -c main.c

info.o: info.c info.h stringhelpers.h
	$(CC) $(CFLAGS) -c info.c

stringhelpers.o: stringhelpers.c stringhelpers.h
	$(CC) $(CFLAGS) -c stringhelpers.c

daemon.o: daemon.c daemon.h
	$(CC) $(CFLAGS) -c daemon.c

comm.o: comm.c comm.h
	$(CC) $(CFLAGS) -c comm.c

serializer.o: serializer.c serializer.h info.h
	$(CC) $(CFLAGS) $(INCLUDE) -c serializer.c
