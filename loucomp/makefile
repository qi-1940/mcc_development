#
# makefile for TINY
# Borland C Version
# K. Louden 2/3/98
#

CC = gcc 

OBJS = main.o util.o scan.o parse.o symtab.o analyze.o code.o cgen.o

tiny.exe: $(OBJS)
	$(CC)   $(OBJS) -o tiny.exe

main.o: main.c globals.h util.h scan.h parse.h analyze.h cgen.h
	$(CC)  -c main.c

util.o: util.c util.h globals.h
	$(CC)  -c util.c

scan.o: scan.c scan.h util.h globals.h
	$(CC)  -c scan.c

parse.o: parse.c parse.h scan.h globals.h util.h
	$(CC)  -c parse.c

symtab.o: symtab.c symtab.h
	$(CC)  -c symtab.c

analyze.o: analyze.c globals.h symtab.h analyze.h
	$(CC)  -c analyze.c

code.o: code.c code.h globals.h
	$(CC)  -c code.c

cgen.o: cgen.c globals.h symtab.h code.h cgen.h
	$(CC)  -c cgen.c

clean:
	rm *.o
	rm *.exe

tm.exe: tm.c
	$(CC)  tm.c -o tm.exe

tiny: tiny.exe

tm: tm.exe

all: tiny tm

