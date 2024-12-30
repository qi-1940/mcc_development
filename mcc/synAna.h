#ifndef SYNANA_H
#define SYNANA_H

#include "C_List.h"
#include "restrictions.h"



//terminal symbols
typedef enum {INT=1,VOID,MAIN,IF,ELSE,WHILE,BREAK,RETURN,INPUT,OUTPUT,
ADD,SUB,MUL,DIV,LESS,MORE,SIGNAL_EQUAL,LESS_EQUAL,MORE_EQUAL,EQUAL,SEMI,
L_PAR,R_PAR,L_BRACE,R_BRACE,ID,C_NUM}type;

//non-terminal symbols and their production methods
/*
    grammar:

    (expression)E ::= C_NUM R
    R::=+ C_NUM R | NULL
*/

typedef union{
    char nonTermi;
    type kind;
}node_info;

struct node_
{
    int flag;//0 means terminals,1 means nonterminals,-1 means unkown
    node_info value;
    int chil_num;//how many children does the node have

    struct node_* chil_nodes[CHILD_NUM_MAX];
    struct node_* fa_node;
};
typedef struct node_ node;
typedef node* node_ptr;

void nodeInit(node_ptr root);
void showParseTree(node_ptr input);
void addToParseTree_Ter(node_ptr root,type input,int a,FILE* f,C_List* cl);
void addToParseTree_NonTer(node_ptr root,char nonTe);
void E(type input,node_ptr root,FILE* f,C_List* cl);
void synAna(node_ptr root,FILE* f,C_List* cl);

#endif