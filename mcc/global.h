#ifndef GLOBAL_H
#define GLOBAL_H

#define token_max 50
#define list_len 40
#define cl_len 15
#define CHILD_NUM_MAX 100

//terminal symbols
typedef enum {EOF_=0,INT=1,VOID=2,MAIN=3,IF=4,ELSE=5,WHILE=6
,BREAK=7,RETURN=8,INPUT=9,OUTPUT=10,
ADD=11,SUB=12,MUL=13,DIV=14,LESS=15,MORE=16,SIGNAL_EQUAL=17
,LESS_EQUAL=18,MORE_EQUAL=19,EQUAL=20,SEMI=21,
L_PAR=22,R_PAR=23,L_BRACE=24,R_BRACE=25,ID=26,C_NUM=27}type;

//node's type
typedef enum { TERMINAL=0,NONTERMINAL=1,UNKOWN=-1}type_of_node;

typedef union{
    char nonTermi;
    type kind;
}node_info;

struct node_
{
    type_of_node flag;
    node_info value;
    int chil_num;//How many children does the node has.

    struct node_* chil_nodes[CHILD_NUM_MAX];
    struct node_* fa_node;
};//The node of the parse tree.
typedef struct node_ node;
typedef node* node_ptr;

typedef struct {
    char list[list_len][cl_len];
    int total;
}C_List;

typedef struct{
        FILE* f;//The source code file.
        node_ptr root;//Root of the parse tree.
        C_List* cl;
}object;//For each file which is complied by mcc,this struct stores its core information.
typedef object* object_ptr;

#endif
