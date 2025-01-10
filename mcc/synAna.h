#ifndef SYNANA_H
#define SYNANA_H

#include "C_List.h"
#include "restrictions.h"

//terminal symbols
typedef enum {EOF_=0,INT=1,VOID=2,MAIN=3,IF=4,ELSE=5,WHILE=6
,BREAK=7,RETURN=8,INPUT=9,OUTPUT=10,
ADD=11,SUB=12,MUL=13,DIV=14,LESS=15,MORE=16,SIGNAL_EQUAL=17
,LESS_EQUAL=18,MORE_EQUAL=19,EQUAL=20,SEMI=21,
L_PAR=22,R_PAR=23,L_BRACE=24,R_BRACE=25,ID=26,C_NUM=27}type;

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
void O(node_ptr);
int W(node_ptr);
int Q(node_ptr);
int M(node_ptr);
int P(node_ptr);
void Z(node_ptr);
int T(node_ptr);
int H(node_ptr);
void F(node_ptr);
void V(node_ptr);
void I(node_ptr);
void synAna(FILE*,node_ptr,C_List*);
int eat(type,node_ptr);

#endif