#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C_List.h"

int addToC_List(C_List* cl,char* input){//Return the position of input in C_List
    //If input has been in the C_List.
    for(int i=0;i<cl->total;i++){
        if(strcmp(cl->list[i],input)==0){
            return i;
        }
    }
    //New input.
    strcpy(cl->list[cl->total++],input);
    return cl->total-1 ; 
}
void C_List_init(C_List* cl){
    for(int i=0;i<list_len;i++){
        strcpy(cl->list[i],"");
    }
    cl->total = 0;
}
void showC_List(C_List* cl){
    printf("\nshowC_List:\n");
    for(int i=0;i<cl->total;i++){
        printf("%d\t%s\n",i,cl->list[i]);
    }
    printf("total=%d\n",cl->total);
}