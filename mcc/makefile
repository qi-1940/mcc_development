mcc:mcc.o lexAna.o synAna.o C_List.o
	gcc -g -pthread C_List.o lexAna.o synAna.o mcc.o -o mcc
mcc.o:mcc.c lexAna.h synAna.h C_List.h
	gcc -g -pthread -c mcc.c
lexAna.o:lexAna.c lexAna.h C_List.h
	gcc -g -pthread -c lexAna.c
synAna.o:synAna.c synAna.h C_List.h
	gcc -g -pthread -c synAna.c
C_List.o:C_List.c C_List.h
	gcc -g -pthread -c C_List.c
