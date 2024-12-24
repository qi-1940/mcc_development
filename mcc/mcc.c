#include <stdio.h>
#include <stdlib.h>
#include "lexAna.h"
#include "synAna.h"
#include "C_List.h"

/*
    Usage:
    假设我当前目录下有一文件“test1.cmm”，
    meanwhile,"mcc" is in the current directory,
    (in Windows)在当前目录下打开终端，输入“mcc test1.cmm”，
    就会在当前目录下产生可执行文件“test1.exe”
    在终端中输入“test1.exe”，
    就能够运行这个可执行文件。
*/

int main(int argc,char *argv[]){
    //打开文件
    FILE * f = fopen(argv[1],"r");
    if(f == NULL){
        fprintf(stderr,"Opening process failed.\n");
        return 0;
    }
    if(argc!=2){
        fprintf(stderr,"Input parameters' fault!\n");
        return 0;
    }
    //得到中间代码...
        //词法和语法分析
    token* temp_token;//This temporarily stores one token which is gotten from the function lexAna().
    temp_token = malloc(sizeof(token));
    
    C_List* cl;
    cl = malloc(sizeof(list_len));
    C_List_init(cl);

    int ii =0 ;
    while(!feof(f)&&!ferror(f)){
        lexAna(f,temp_token,cl);
        if(temp_token->kind_num!=0)
            if(temp_token->kind_num!=26 && temp_token->kind_num!= 27)
                printf("%d\t%s\t\t%d\n",++ii,temp_token->val.valu,temp_token->kind_num);
            else
                printf("%d\t%d\t\t%d\n",++ii,temp_token->val.va_posi,temp_token->kind_num);
    }

    showC_List(cl);

        //语义分析
        //中间代码生成
    //生成可执行文件
    printf("\nexe was created!\n");

    //关闭文件
    free(cl);
    free(temp_token);

    /*
        If do not ignore the line below,error will be thrown out in ubuntu,which 
        will do not happen in windows.
    */
    //fclose(f);
    return 0;
}