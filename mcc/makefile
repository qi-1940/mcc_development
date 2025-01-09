mcc:mcc.o lexAna.o synAna.o C_List.o
	gcc -g C_List.o lexAna.o synAna.o mcc.o -o mcc
mcc.o:mcc.c lexAna.h synAna.h C_List.h
	gcc -g -c mcc.c
lexAna.o:lexAna.c lexAna.h C_List.h restrictions.h
	gcc -g -c lexAna.c
synAna.o:synAna.c synAna.h C_List.h restrictions.h
	gcc -g -c synAna.c
C_List.o:C_List.c C_List.h restrictions.h
	gcc -g -c C_List.c
