#include <stdio.h>
#include <stdlib.h>

#include "synAna.h"
#include "lexAna.h"
#include "restrictions.h"

FILE* f=NULL;
C_List* cl =NULL;
type temp_type = 0;

//The function is used just after one node_ptr was assigned meomory. 
void nodeInit(node_ptr root){
    root->flag=-1;
    root->chil_num=0;
    root->fa_node =NULL;
    for(int i =0;i<CHILD_NUM_MAX;i++){
        root->chil_nodes[i]=NULL;
    }
}

void showParseTree(node_ptr input){
    switch(input->flag){
        case -1:
            fprintf(stderr,"Empty parse tree!\n");
            break;
        case 0://The input node is a terminal node.
            printf("[%d]\n",input->value.kind);
            break;
        case 1://The input node is a nonterminal node.
            printf("[%c,%d]\n",input->value.nonTermi,input->chil_num);
            for (int i = 0; i < input->chil_num; i++){
                showParseTree(input->chil_nodes[i]);
            }
            break;
        default:
            fprintf(stderr,"Unkown flag of the node_ptr!\n");
    }
}

void addToParseTree_Ter(node_ptr root){//Add the new terminal node to tree.
    node_ptr new_node_ptr = malloc(sizeof(node));
    nodeInit(new_node_ptr);
    new_node_ptr->flag=0;
    root->chil_nodes[root->chil_num++] = new_node_ptr;
    new_node_ptr->fa_node=root;
    new_node_ptr->value.kind=temp_type;
}

node_ptr addToParseTree_NonTer(node_ptr root,char nonTe){
    if(root->flag==-1){//if the root of the tree is lost
        root->value.nonTermi=nonTe;
        root->flag=1;
        return root;
    }
    else{//add children of the root
        node_ptr new_node_ptr = malloc(sizeof(node));
        nodeInit(new_node_ptr);
        new_node_ptr->flag=1;
        root->chil_nodes[root->chil_num++] = new_node_ptr;
        new_node_ptr->fa_node=root;
        new_node_ptr->value.nonTermi=nonTe;
        return new_node_ptr;
    }
}

int eat(type what,node_ptr root){
    if(what==temp_type){
        addToParseTree_Ter(root);
        token* temp_token = malloc(sizeof(token));
        temp_type = lexAna(f,temp_token,cl);
    }
    else{
        return -1;
    }
    return 0;
}

void S(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'S');
    //R(temp);
    O(temp);
}

void R(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'R');
    
}

void O(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'O');
    switch (temp_type){
        case VOID:
            eat(VOID,temp);
            eat(MAIN,temp);
            eat(L_PAR,temp);
            eat(VOID,temp);
            eat(R_PAR,temp);
            eat(L_BRACE,temp);
            M(temp);
            eat(R_BRACE,temp);
            break;
        default:
            fprintf(stderr,"O syntactic error!\n");
    }
}

int W(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'W');
    if(Q(temp)==-1){
        return -1;
    }
    if(eat(L_BRACE,temp)==-1){
        return -1;
    }
    M(temp);
    if(eat(R_BRACE,temp)==-1){
        return -1;
    }
}

void Y(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'Y');
}

int Q(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'Q');
    P(temp);
    eat(L_PAR,temp);
    P(temp);
    eat(R_PAR,temp);
}

int M(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'M');
    T(temp);
    H(temp);
}

void P(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'P');
    switch (temp_type){
    case INT:
        eat(INT,temp);
        eat(ID,temp);
        break;
    case VOID:
        eat(VOID,temp);
        break;
    default:
        fprintf(stderr,"P syntactic error!\n");
    }
}

void Z(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'Z');
}

int T(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'T');
    switch (temp_type){
        case IF:
            I(temp);
            break;
        case WHILE:
            F(temp);
            break;
        case INT:
            eat(INT,temp);
            eat(ID,temp);
            eat(SEMI,temp);
            break;
        case VOID:
            eat(VOID,temp);
            eat(ID,temp);
            eat(SEMI,temp);
            break; 
        case ID:
            eat(ID,temp);
            eat(SIGNAL_EQUAL,temp);
            A(temp);
            eat(SEMI,temp);
            break;
        case INPUT:
            eat(INPUT,temp);
            eat(L_PAR,temp);
            eat(R_PAR,temp);
            break;
        case OUTPUT:
            eat(OUTPUT,temp);
            eat(L_PAR,temp);
            A(temp);
            eat(R_PAR,temp);
            break;
        default:
            return -1;
    }
    return 0;
}

int H(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'H');
    if(T(temp)==-1){
        return -1;
    }
    if(H(temp)==-1){
        return -1;
    }
    return 0;
}

void F(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'F');
    eat(WHILE,temp);
    eat(L_PAR,temp);
    V(temp);
    eat(R_PAR,temp);
    eat(L_BRACE,temp);
    M(temp);
    eat(R_BRACE,temp);
}

void V(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'V');
    A(temp);
    switch (temp_type){
        case MORE_EQUAL:
            eat(MORE_EQUAL,temp);
            A(temp);
            break;
        case LESS_EQUAL:
            eat(LESS_EQUAL,temp);
            A(temp);
            break;
        case EQUAL:
            eat(EQUAL,temp);
            A(temp);
            break;
        default:
            fprintf(stderr,"V syntactic error!\n");
    }
}

void I(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'I');
    eat(IF,temp);
    eat(L_PAR,temp);
    V(temp);
    eat(R_PAR,temp);
    eat(L_BRACE,temp);
    M(temp);
    eat(R_BRACE,temp);
    eat(ELSE,temp);
    eat(L_BRACE,temp);
    M(temp);
    eat(R_BRACE,temp);
}


void A(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'A');
    C(temp);
    B(temp);
}

void B(node_ptr root){//return 1 means that the synaxic part is matched with NULL.
    node_ptr temp = addToParseTree_NonTer(root,'B');
    switch(temp_type){
        case ADD:
            eat(ADD,temp);
            C(temp);
            B(temp);
            break;
        case SUB:
            eat(SUB,temp);
            C(temp);
            B(temp);
            break;
        default:
    }
}

void C(node_ptr root){
    node* temp = addToParseTree_NonTer(root,'C');
    E(temp);
    D(temp);
}

void D(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'D');
    switch(temp_type){
        case MUL:
            eat(MUL,temp);
            E(temp);
            D(temp);
            break;
        case DIV:
            eat(DIV,temp);
            E(temp);
            D(temp);
            break;
        default:
    }
}

void E(node_ptr root){
    node_ptr temp = addToParseTree_NonTer(root,'E');
    switch (temp_type){
        case ID:
            eat(ID,temp);
            break;
        case C_NUM:
            eat(C_NUM,temp);
            break;
        case L_PAR:
            eat(L_PAR,temp);
            A(temp);
            eat(R_PAR,temp);
            break;
        default:
            fprintf(stderr,"E syntactic error!\n");
            return;
    }
}

void synAna(FILE* ff,node_ptr root,C_List* cll){
    f = ff;
    cl = cll;
    type temp=-1;

    token* temp_token;
    temp_token = malloc(sizeof(token));
    token_clear(temp_token); 
    
    lexAna(f,temp_token,cl);
    temp_type = temp_token->kind_num;

    S(root);
}