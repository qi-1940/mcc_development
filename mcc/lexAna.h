#ifndef LEXANA_H
#define LEXANA_H

#include "global.h"

typedef union{
    char valu[token_max+1];
    int va_posi;
}va;

typedef struct{
    va val;
    int kind_num;
}token;//the return of the lexical function

void token_clear(token*);
void token_crea(C_List* cl,token* t,char* input);

char get(FILE*);//Get a char.Skip the possible blankspaces.
char getc_er(FILE*);//Get a char safely.

type lexAna(FILE* f,token*,C_List*);

#endif
