#include <stdio.h>
#include <stdlib.h>

#include "lexAna.h"
#include "synAna.h"
#include "C_List.h"

/*
    Usage:
    假设我当前目录下有一文件“test.cmm”，
    meanwhile,"mcc" is under the current directory,
    (in Windows)在当前目录下打开终端，输入“mcc test.cmm”，
    (in Linux)Please input "./mcc test.cmm".
     
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


int main(int argc,char *argv[]){
    //打开文件
    FILE* f = fopen(argv[1],"r");
    if(f == NULL){
        fprintf(stderr,"Opening process failed.\n");
        return 0;
    }
    if(argc!=2){
        fprintf(stderr,"Input parameters' fault!\n");
        return 0;
    }

    //词法和语法分析

    //Parse tree's root node.
    node_ptr root;
    root = malloc(sizeof(node));
    nodeInit(root);
    
    C_List* cl;
    cl = malloc(sizeof(list_len));
    C_List_init(cl);


    if(!feof(f)&&!ferror(f)){
        synAna(f,root,cl);
    }

    showParseTree(root);

    //showC_List(cl);
    //语义分析

    //关闭文件
    free(cl);
    free(root);

    /*
        If do not ignore the line below,error will be thrown out in ubuntu,which 
        will do not happen in windows.
    */
    //fclose(f);
    return 0;
}