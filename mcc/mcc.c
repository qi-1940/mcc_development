#include <stdio.h>
#include <stdlib.h>
#include "synAna.h"
#include "C_List.h"
#include "global.h"

/*
    Usage:
    Mcc is used to compile the file.
    By now,only lexical analysis and syntax analysis were realized.
    Suppose there is a file called "test.cmm" in the current working directory.
    Meanwhile,"mcc" is under the current directory,
    (in Windows)open the terminal and input "mcc test.cmm",
    (in Linux)open the terminal and input "./mcc test.cmm".
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
    FILE* f1 = fopen(argv[1],"r");
    if(f1 == NULL){
        fprintf(stderr,"Opening process failed.\n");
        return 0;
    }
    if(argc!=2){
        fprintf(stderr,"Input parameters' fault!\n");
        return 0;
    }
    //词法和语法分析
    object_ptr obj_p;
    obj_p =(object_ptr) malloc(sizeof(object));
    obj_p->f=f1;
    obj_p->root =(node_ptr) malloc(sizeof(node));
    nodeInit(obj_p->root);
    obj_p->cl =(C_List*) malloc(sizeof(C_List));
    C_List_init(obj_p->cl);

    if(!feof(f1)&&!ferror(f1)){
        synAna(obj_p);
    }

    showParseTree(obj_p->root);

    //showC_List(cl);

    //关闭文件
    free(obj_p->cl);
    free(obj_p->root);
    free(obj_p);
    /*
        If do not ignore the line below,error will be thrown out in ubuntu,which 
        will do not happen in windows.
    */
    //fclose(f);
    return 0;
}

