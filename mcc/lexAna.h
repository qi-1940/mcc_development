#ifndef LEXANA_H
#define LEXANA_H

#define token_max 20
typedef struct{
    char va[token_max+1];
    int va_temp;
    int kind_num;
}token;//the return of the lexical function

void token_init(token*);
char get(FILE*);//Get a char.Skip the possible blankspaces.
void token_crea(token*,char*);
void lexAna(FILE*,token*);

#endif