#ifndef LEXANA_H
#define LEXANA_H

#define token_max 20

const struct{
    char va[token_max+1];
    int va_temp;
    int kind_num;
}token_;//the return of the lexical function
typedef struct token_ token;

void token_init(token* t);
char get(FILE*,char*);//Get a char.Skip the possible blankspaces.
void token_crea(token* t,char* input);
void lexAna(FILE * f,token* output);


#endif