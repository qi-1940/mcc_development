mcc:mcc.o lexAna.o synAna.o
	gcc -g mcc.o lexAna.o synAna.o -o mcc
mcc.o:mcc.c lexAna.h synAna.h
	gcc -c mcc.c
lexAna.o:lexAna.c lexAna.h
	gcc -c lexAna.c
synAna.o:synAna.c synAna.h
	gcc -c synAna.c
