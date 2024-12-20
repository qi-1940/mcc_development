#include<stdio.h>
/*
假设我当前目录下有一文件“test1.cmm”，
在当前目录下打开终端，输入“mcc test1.cmm”，
就会在当前目录下产生可执行文件“test1.exe”
在终端中输入“./test1.exe”，
就能够运行这个可执行文件。
*/
int main(int argc,char *argv[]){
    printf("Total %d\n",argc);
    //打开文件
    FILE * f = fopen(argv[1],"r");
    //得到中间代码
        //词法和语法分析
    char temp;
    while(!feof(f)&&(temp=fgetc(f) ) ){
        printf("%c\n",temp);
    }
        //语义分析
        //中间代码生成
    //关闭文件
    fclose(f);
    //生成可执行文件
    printf("exe was created!\n");
    //执行可执行文件
    
    return 0;
}