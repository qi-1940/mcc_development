#include <stdio.h>
#include <stdlib.h>

#include "synAna.h"
#include "lexAna.h"
#include "restrictions.h"

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
    if(input->flag==0){//if the input is at the lowest of the tree.
        printf("[%d,%d]\n",input->value.kind,input->chil_num);
        return;
    }
    else{
        printf("[%c,%d]\n",input->value.nonTermi,input->chil_num);
        for (int i = 0; i < input->chil_num; i++)
        {
            showParseTree(input->chil_nodes[i]);
        }
    }
}

void addToParseTree_Ter(node_ptr root,type input,int a,FILE* f,C_List* cl){
    if(a==1){
        token* temp_token;
        temp_token = malloc(sizeof(token));
        token_clear(temp_token); 
        lexAna(f,temp_token,cl);
        if(temp_token->kind_num!=input){
            fprintf(stderr,"Match error!\n");
            return;
        }
    }
    node_ptr new_node_ptr = malloc(sizeof(node));
    nodeInit(new_node_ptr);
    new_node_ptr->flag=0;
    root->chil_nodes[root->chil_num++] = new_node_ptr;
    new_node_ptr->fa_node=root;
    new_node_ptr->value.kind=input;
}

void addToParseTree_NonTer(node_ptr root,char nonTe){
    if(root->flag==-1){//if the root of the tree is lost
        root->value.nonTermi=nonTe;
        root->flag=1;
    }
    else{//add children of the root
        node_ptr new_node_ptr = malloc(sizeof(node));
        nodeInit(new_node_ptr);
        new_node_ptr->flag=1;
        root->chil_nodes[root->chil_num++] = new_node_ptr;
        new_node_ptr->fa_node=root;
        new_node_ptr->value.nonTermi=nonTe;
    }
}

void E(type input,node_ptr root,FILE* f,C_List* cl){
    switch (input){
        case C_NUM:
            addToParseTree_NonTer(root,'E');
            addToParseTree_Ter(root,C_NUM,0,f,cl);
            addToParseTree_Ter(root,ADD,1,f,cl);
            addToParseTree_Ter(root,C_NUM,1,f,cl);
            break; 
        default:
            fprintf(stderr,"Syntax error!\n");
    }
}

void R(type input,node_ptr root,FILE* f,C_List* cl){
    switch (input){
    case ADD:
        addToParseTree_NonTer(root,'R');
        addToParseTree_Ter(root,ADD,0,f,cl);
        addToParseTree_Ter(root,C_NUM,1,f,cl);
        R()
        break;
    
    default:
        break;
    }
}

void synAna(node_ptr root,FILE* f,C_List* cl){
    type temp=-1;

    token* temp_token;
    temp_token = malloc(sizeof(token));
    token_clear(temp_token); 
    
    lexAna(f,temp_token,cl);
    temp = temp_token->kind_num;

    E(temp,root,f,cl);
}