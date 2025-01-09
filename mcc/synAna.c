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

void eat(type what,node_ptr root){
    if(what==temp_type){
        addToParseTree_Ter(root);
        token* temp_token = malloc(sizeof(token));
        temp_type = lexAna(f,temp_token,cl);
    }
    else{
        fprintf(stderr,"Match error!\n");
    }
}

void S(node_ptr root){
    A(addToParseTree_NonTer(root,'S'));
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