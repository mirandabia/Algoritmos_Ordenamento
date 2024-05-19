#include "../headers/doublyLinkedList.h"

Node* createNode(int iValue) {
    Node* newNode = new Node;
    newNode->iPayload = iValue;
    newNode->ptrNext = nullptr;
    newNode->ptrPrev = nullptr;
    return newNode;
}

void insertEnd(Node** ptrHead, int iValue) {
    Node* ptrNewNode = createNode(iValue);
    if (!*ptrHead) {
        *ptrHead = ptrNewNode;
    } else {
        Node* ptrTemp = *ptrHead;
        while (ptrTemp->ptrNext) {
            ptrTemp = ptrTemp->ptrNext;
        }
        ptrNewNode->ptrPrev = ptrTemp;
        ptrTemp->ptrNext = ptrNewNode;
    }
}

void deleteList(Node** ptrHead) {
    Node* ptrCurrent = *ptrHead;
    while (ptrCurrent) {
        Node* ptrNext = ptrCurrent->ptrNext;
        delete ptrCurrent;
        ptrCurrent = ptrNext;
    }
    *ptrHead = nullptr;
}

void displayList(Node* ptrNode) {
    if (!ptrNode) {
        std::cout << "Lista vazia." << std::endl;
        return;
    }
    std::cout << "Payload: ";
    while (ptrNode) {
        std::cout << ptrNode->iPayload << " ";
        ptrNode = ptrNode->ptrNext;
    }
    std::cout << std::endl;
}

void swapValue(Node* ptrNode1, Node* ptrNode2) {
    int iTemp = ptrNode1->iPayload;
    ptrNode1->iPayload = ptrNode2->iPayload;
    ptrNode2->iPayload = iTemp;
}