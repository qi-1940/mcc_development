#
# makefile for TINY
# Borland C Version
# K. Louden 2/3/98
#

CC = gcc 

OBJS = main.o util.o scan.o parse.o symtab.o analyze.o code.o cgen.o

tiny.exe: $(OBJS)
	$(CC)  -fPIC $(OBJS) -o tiny.exe

main.o: main.c globals.h util.h scan.h parse.h analyze.h cgen.h
	$(CC) -fPIC  -c main.c

util.o: util.c util.h globals.h
	$(CC) -fPIC -c util.c

scan.o: scan.c scan.h util.h globals.h
	$(CC) -fPIC -c scan.c

parse.o: parse.c parse.h scan.h globals.h util.h
	$(CC) -fPIC -c parse.c

symtab.o: symtab.c symtab.h
	$(CC) -fPIC -c symtab.c

analyze.o: analyze.c globals.h symtab.h analyze.h
	$(CC) -fPIC -c analyze.c

code.o: code.c code.h globals.h
	$(CC) -fPIC -c code.c

cgen.o: cgen.c globals.h symtab.h code.h cgen.h
	$(CC) -fPIC -c cgen.c

clean:
	rm *.o
	rm *.exe

tm.exe: tm.c
	$(CC) -fPIC tm.c -o tm.exe

tiny: tiny.exe

tm: tm.exe

all: tiny tm

