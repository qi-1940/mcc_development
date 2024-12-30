#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexAna.h"
#include "C_List.h"

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

void token_clear(token * t){
    for(int i=0;i<token_max+1;i++){
        t->val.valu[i]='\0';
    }
    t->val.va_posi = -1;
    t->kind_num = 0;
}
void token_crea(C_List* cl,token* t,char* input){
    if(strcmp(input,"int")==0)t->kind_num = 1;
    else if(strcmp(input,"void")==0)t->kind_num = 2;
    else if(strcmp(input,"main")==0)t->kind_num = 3;
    else if(strcmp(input,"if")==0)t->kind_num = 4;
    else if(strcmp(input,"else")==0)t->kind_num = 5;
    else if(strcmp(input,"while")==0)t->kind_num = 6;
    else if(strcmp(input,"break")==0)t->kind_num = 7;
    else if(strcmp(input,"return")==0)t->kind_num = 8;
    else if(strcmp(input,"input")==0)t->kind_num = 9;
    else if(strcmp(input,"output")==0)t->kind_num = 10;
    else if(strcmp(input,"+")==0)t->kind_num = 11;
    else if(strcmp(input,"-")==0)t->kind_num = 12;
    else if(strcmp(input,"*")==0)t->kind_num = 13;
    else if(strcmp(input,"/")==0)t->kind_num = 14;
    else if(strcmp(input,"<")==0)t->kind_num = 15;
    else if(strcmp(input,">")==0)t->kind_num = 16;
    else if(strcmp(input,"=")==0)t->kind_num = 17;
    else if(strcmp(input,"<=")==0)t->kind_num = 18;
    else if(strcmp(input,">=")==0)t->kind_num = 19;
    else if(strcmp(input,"==")==0)t->kind_num = 20;
    else if(strcmp(input,";")==0)t->kind_num = 21;
    else if(strcmp(input,"(")==0)t->kind_num = 22;
    else if(strcmp(input,")")==0)t->kind_num = 23;
    else if(strcmp(input,"{")==0)t->kind_num = 24;
    else if(strcmp(input,"}")==0)t->kind_num = 25;
    else ;
    if(t->kind_num<=25&&t->kind_num>=1)
        strcpy(t->val.valu,input);
    else{
        t->kind_num=isalpha(input[0])?26:27;
        t->val.va_posi = addToC_List(cl,input);
    }
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
    char temp = getc_er(f);
    while(feof(f)==0 && ferror(f)==0 && isspace((int)temp)){
        if(feof(f)!=0){
            fprintf(stderr,"File is empty!\n");
            return '\0';
        }
        if(ferror(f)!=0){
            fprintf(stderr,"File reading process failed!\n");
            return '\0';
        }
        temp = getc_er(f);
    }
    return temp;
}
char getc_er(FILE* f){
    if(!feof(f)&&!ferror(f)){
        return getc(f);
    }
    else if(feof(f)){
        fprintf(stderr,"File went to the end but the program still wants to get a charater!\n");
        return EOF;
    }
    else{
        fprintf(stderr,"The process of reading file meets problems!\n");
        return EOF;
    }

}

/*
    The lexAna() function return one token 
    from a file indicator 
    every time it is called.
*/
void lexAna(FILE * f,token* output,C_List* cl){
    char temp;
    if((temp=getc(f))==EOF)return;
    ungetc(temp,f);
    temp = get(f);

    token_clear(output);            
    char te[token_max]={'\0'};//Memory one token temporarily and return it to "output".
    int i=0;//Serving 'te'.

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
            te[i++] = temp;
            while((temp = getc_er(f))>='a'&& temp<='z'){
                te[i++] = temp;
            }
            switch(temp){
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
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    te[i++] = temp;
                    while((temp =  getc_er(f))&&(isalpha(temp)||isdigit(temp))){
                        te[i++] = temp;
                    }
                default:
                    ungetc(temp,f);
                    token_crea(cl,output,te);
                    break; 
            }
            break;
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
            te[i++] = temp;
            while((temp = getc_er(f))&&(isalpha(temp)||isdigit(temp))){
                te[i++] = temp;
            }
            ungetc(temp,f);
            token_crea(cl,output,te);
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            te[i++] = temp;
            while(isdigit(temp =  getc_er(f))){
                te[i++] = temp;
            }
            ungetc(temp,f);
            token_crea(cl,output,te);
            break;
        case '<':
        case '>':
        case '=':
            te[i++] = temp ;
            if((temp = getc_er(f))==EOF){
                token_crea(cl,output,te);
                break;
            }
            if(temp == '=' )te[i++] = temp;
            else ungetc(temp,f);
            token_crea(cl,output,te);
            break;
        case '/':
            te[i++] = temp;
            if((temp = getc_er(f))=='*'){
                while( getc_er(f)!='*');
                if( getc_er(f)=='/')break;
            }
            else{
                ungetc(temp,f);
                token_crea(cl,output,te);
                break;
            }
            break;
        case ';':
        case '+':
        case '-':
        case '*':
        case '(':
        case ')':
        case '{':
        case '}':
            te[0] = temp;
            token_crea(cl,output,te);
            break;
        default:
            fprintf(stderr,"\nThe input character can not be recognized!\n");
    }
}