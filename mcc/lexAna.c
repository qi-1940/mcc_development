#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexAna.h"
/*
    words and tokens' list:
    words,kind number,valve
    int,1,-
    void,2,-
    main,3,-
    if,4,-
    else,5,-
    while,6,-
    break,7,-
    return,8,-
    input,9,-
    output,10,-
    +,11,-
    -,12,-
    *,13,-
    /,14,-
    <,15,-
    >,16,-
    =,17,-
    <=,18,-
    >=,19,-
    ==,20,-
    ;,21,-
    (,22,-
    ),23,-
    {,24,-
    },25,-
    identifiers,26,indicator in tokens' list
    const_nums,27,indicator in num list
*/



void token_init(token* t){
    t = malloc(sizeof(token));
    for(int i=0;i<token_max;i++){
        t->va[i]='\0';
    }
    t->va_temp = 0;
    t->kind_num = 0;
}

void token_crea(token* t,char* input){
    strcpy(t->va,input);
    if(strcmp(input,"int"))t->kind_num = 1;
    else if(strcmp(input,"void"))t->kind_num = 2;
    else if(strcmp(input,"main"))t->kind_num = 3;
    else if(strcmp(input,"if"))t->kind_num = 4;
    else if(strcmp(input,"else"))t->kind_num = 5;
    else if(strcmp(input,"while"))t->kind_num = 6;
    else if(strcmp(input,"break"))t->kind_num = 7;
    else if(strcmp(input,"return"))t->kind_num = 8;
    else if(strcmp(input,"input"))t->kind_num = 9;
    else if(strcmp(input,"output"))t->kind_num = 10;
    else if(strcmp(input,"+"))t->kind_num = 11;
    else if(strcmp(input,"-"))t->kind_num = 12;
    else if(strcmp(input,"*"))t->kind_num = 13;
    else if(strcmp(input,"/"))t->kind_num = 14;
    else if(strcmp(input,"<"))t->kind_num = 15;
    else if(strcmp(input,">"))t->kind_num = 16;
    else if(strcmp(input,"="))t->kind_num = 17;
    else if(strcmp(input,"<="))t->kind_num = 18;
    else if(strcmp(input,">="))t->kind_num = 19;
    else if(strcmp(input,"=="))t->kind_num = 20;
    else if(strcmp(input,";"))t->kind_num = 21;
    else if(strcmp(input,"("))t->kind_num = 22;
    else if(strcmp(input,")"))t->kind_num = 23;
    else if(strcmp(input,"{"))t->kind_num = 24;
    else if(strcmp(input,"}"))t->kind_num = 25;
}

char get(FILE *f){//Get a char.Skip the possible blankspaces.
    if(feof(f)!=0){
        fprintf(stderr,"File is empty!\n");
        return '\0';
    }
    if(ferror(f)!=0){

        fprintf(stderr,"File reading process failed!\n");
        return '\0';
    }
    char temp = getc(f);
    while(feof(f)==0 && ferror(f)==0 && isspace((int)temp)){
        if(feof(f)!=0){
            fprintf(stderr,"File is empty!\n");
            return '\0';
        }
        if(ferror(f)!=0){
            fprintf(stderr,"File reading process failed!\n");
            return '\0';
        }
        temp = getc(f);
    }
    return temp;
}

/*
    The lexAna() function return one token 
    from a file indicator 
    every time it is called.
*/
void lexAna(FILE * f,token* output){
    char te[token_max];//Memory one token temporarily and return it.
    int i=0;
    char temp = get(f);
    switch(temp){
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            *te = temp;
            i++;
            while(isalpha(temp = getc(f))){
                te[i++] = temp;
            }
            ungetc(temp,f);
            token_crea(output,te);
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
    }
}