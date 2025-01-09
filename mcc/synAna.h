#ifndef SYNANA_H
#define SYNANA_H

#include "C_List.h"
#include "restrictions.h"

//terminal symbols
typedef enum {EOF_=0,INT=1,VOID,MAIN,IF,ELSE,WHILE,BREAK,RETURN,INPUT,OUTPUT,
ADD,SUB,MUL,DIV,LESS,MORE,SIGNAL_EQUAL,LESS_EQUAL,MORE_EQUAL,EQUAL,SEMI,
L_PAR,R_PAR,L_BRACE,R_BRACE,ID,C_NUM}type;

//non-terminal symbols and their production methods
/*
    grammar:

    S(beginning) ::= A
    A ::= C_NUM A_
    A_ ::= ADD C_NUM A_ | EOF
    
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

void nodeInit(node_ptr);
void showParseTree(node_ptr);
void addToParseTree_Ter(node_ptr);
node_ptr addToParseTree_NonTer(node_ptr,char);
void S(node_ptr);
void A(node_ptr);
void B(node_ptr);
void C(node_ptr);
void D(node_ptr);
void E(node_ptr);
void synAna(FILE*,node_ptr,C_List*);
void eat(type,node_ptr);

#endif