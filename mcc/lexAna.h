#ifndef LEXANA_H
#define LEXANA_H

#include "C_List.h"

#define token_max 50

typedef union{
    char valu[token_max+1];
    int va_posi;
}va;

typedef struct{
    va val;
    int kind_num;
}token;//the return of the lexi cal function
void token_clear(token*);
void token_crea(C_List*,token*,char*);

char get(FILE*);//Get a char.Skip the possible blankspaces.
char getc_er(FILE*);

void lexAna(FILE*,token*,C_List*);

#endif