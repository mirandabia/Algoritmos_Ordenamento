#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

struct Node {
    int iPayload;
    Node* ptrNext = nullptr;
    Node* ptrPrev = nullptr;
};

struct DoublyLinkedList {
    Node* ptrHead;
    Node* ptrTail;
};

Node* createNode(int);
void displayList(Node*);
void insertEnd(DoublyLinkedList*, int);
void deleteList(DoublyLinkedList*);
void swapValue(Node*, Node*);
bool isEmpty(DoublyLinkedList*);
DoublyLinkedList* createList();
DoublyLinkedList* createListByArray(int[], int);
Node* searchList(DoublyLinkedList*, int);
void pushList(DoublyLinkedList*, int);
Node* popList(DoublyLinkedList*);
DoublyLinkedList* copyList(DoublyLinkedList*);

#endif