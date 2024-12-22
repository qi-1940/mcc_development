#ifndef LEXANA_H
#define LEXANA_H


#define list_len 40
#define cl_len 15
#define token_max 50

typedef struct{
    char va[token_max+1];
    int va_temp;
    int kind_num;
}token;//the return of the lexi cal function
void token_clear(token*);
void token_crea(token*,char*);

typedef struct {
    char list[list_len][cl_len];
    int total;
    int temp_posi;
}C_List;
int addToC_List(C_List*,char*);
void C_List_init(C_List*);
void showC_List(C_List*);

char get(FILE*);//Get a char.Skip the possible blankspaces.
char getc_er(FILE*);

void lexAna(FILE*,token*,C_List*);

#endif