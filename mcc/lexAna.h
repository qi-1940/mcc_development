#ifndef LEXANA_H
#define LEXANA_H


#define list_len 40
#define cl_len 15
#define token_max 50

typedef union{
    char valu[token_max+1];
    int va_posi;
}va;

typedef struct {
    char list[list_len][cl_len];
    int total;
}C_List;
int addToC_List(C_List*,char*);//Return the position of input in C_List
void C_List_init(C_List*);
void showC_List(C_List*);

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