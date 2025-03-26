#ifndef SYNANA_H
#define SYNANA_H

#include "global.h"

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
void O_case_VOID(node_ptr);
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
void synAna(object_ptr);
int eat(type,node_ptr);

#endif
