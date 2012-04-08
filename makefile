all: diagnostics_tool

CC = gcc
INCLUDE = 
CFLAGS = -g -Wall -ansi

diagnostics_tool: main.o info.o stringhelpers.o
	$(CC) -o diagnostics_tool main.o info.o stringhelpers.o

main.o: main.c info.h
	$(CC) $(CFLAGS) -c main.c

info.o: info.c info.h stringhelpers.h
	$(CC) $(CFLAGS) -c info.c

stringhelpers.o: stringhelpers.c stringhelpers.h
	$(CC) $(CFLAGS) -c stringhelpers.c
