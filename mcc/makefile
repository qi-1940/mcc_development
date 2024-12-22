mcc:mcc.o lexAna.o synAna.o
	gcc -g -pthread lexAna.o synAna.o mcc.o -o mcc
mcc.o:mcc.c lexAna.h synAna.h
	gcc -g -pthread -c mcc.c
lexAna.o:lexAna.c lexAna.h
	gcc -g -pthread -c lexAna.c
synAna.o:synAna.c synAna.h
	gcc -g -pthread -c synAna.c
