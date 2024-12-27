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

/*
    Features of the language C--:
    1.大小写敏感
    2.只支持int和void类型
    4.空格包含空白、回车符、换行符和制表符
    5.语言的表达式包括整数上的算数表达式和整数间比较的布尔表达式
    6.分号分隔，花括号包含多条语句序列
    7.程序由函数声明和变量声明组成，必须先声明后使用
    程序的最后一个声明必须是主入口函数声明void main(void)
    8.输入函数int input(void)，输出函数void output(int)分别实现从标准输入设备（键盘）
    读入一个整数值和将一个整数值和换行符打印到标准输出设备（屏幕）；
    9.支持if-else、while和return控制语句；
    10. C--语言不支持数组和递归函数。
*/

/*
    The grammar of C--:

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