#ifndef SYNANA_H
#define SYNANA_H

#include "C_List.h"

#define CHILD_NUM_MAX 100

//terminal symbols
typedef enum {INT=1,VOID,MAIN,IF,ELSE,WHILE,BREAK,RETURN,INPUT,OUTPUT,
ADD,SUB,MUL,DIV,LESS,MORE,SIGNAL_EQUAL,LESS_EQUAL,MORE_EQUAL,EQUAL,SEMI,
L_PAR,R_PAR,L_BRACE,R_BRACE,ID,C_NUM}type;

//non-terminal symbols and their production methods
/*
    expression: E ::= 
*/

struct node_
{
    type kind;
    struct node_* chil_nodes[CHILD_NUM_MAX];
    struct node_* fa_node;
    
};

typedef struct node_ node;
typedef node* node_ptr;

node_ptr synAna(int input,C_List* cl);

#endif