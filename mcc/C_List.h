#ifndef C_LIST_H
#define C_LIST_H

#include "restrictions.h"

typedef struct {
    char list[list_len][cl_len];
    int total;
}C_List;
int addToC_List(C_List*,char*);//Return the position of input in C_List
void C_List_init(C_List*);
void showC_List(C_List*);

#endif