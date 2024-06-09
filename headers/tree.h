#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "doublyLinkedList.h"

using std::cout;
using std::endl;
using std::cerr;

Node* createNode(int);
Node* createTreeByArray(int[], int);
Node* insertNode(Node*, int);
void destroyTree(Node*);
void deleteNode(Node*);
Node* lesserLeaf(Node*);
Node* higherLeaf(Node*);
void printTree(Node*);

#endif // TREE_H
