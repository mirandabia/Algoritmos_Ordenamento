#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

struct Node {
    int iPayload;
    Node* ptrNext = nullptr;
    Node* ptrPrev = nullptr;
};

Node* createNode(int);
void displayList(Node*);

void insertEnd(Node**, int);

void deleteList(Node**);

void swapValue(Node*, Node*);

#endif