#include <stdio.h>
#include <stdlib.h>
#include "lexAna.h"
/*
    假设我当前目录下有一文件“test1.cmm”，
    在当前目录下打开终端，输入“mcc test1.cmm”，
    就会在当前目录下产生可执行文件“test1.exe”
    在终端中输入“./test1.exe”，
    就能够运行这个可执行文件。
*/

int main(int argc,char *argv[]){
    //打开文件
    FILE * f = fopen(argv[1],"r");
    if(f == NULL){
        fprintf(stderr,"Opening process failed.\n");
        return 0;
    }
    //得到中间代码...
        //词法和语法分析
    token* temp_token;//tempor arily store one token which is gotten from function lexAna()
    temp_token = malloc(sizeof(token));
    
    C_List* cl;
    cl = malloc(sizeof(list_len));
    C_List_init(cl);

    int ii =0 ;
    while(!feof(f)&&!ferror(f)){
        lexAna(f,temp_token,cl);
        if(temp_token->kind_num!=0)printf("%d\t%s\t%d\n",++ii,temp_token->va,temp_token->kind_num);
    }

    showC_List(cl);

        //语义分析
        //中间代码生成
    //关闭文件
    free(cl);
    free(temp_token);
    fclose(f);
    //生成可执行文件
    printf("\nexe was created!\n");
    //执行可执行文件
    
    return 0;
}