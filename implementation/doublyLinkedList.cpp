#include "../headers/doublyLinkedList.h"

Node* createNode(int iValue) {
    Node* newNode = new Node;
    newNode->iPayload = iValue;
    newNode->ptrNext = nullptr;
    newNode->ptrPrev = nullptr;
    return newNode;
}

void insertEnd(DoublyLinkedList* ptrList, int iValue) {
    Node* ptrNewNode = createNode(iValue);
    if (!ptrList->ptrHead) {
        ptrList->ptrHead = ptrNewNode;
        ptrList->ptrTail = ptrNewNode;
    } else {
        ptrNewNode->ptrPrev = ptrList->ptrTail;
        ptrList->ptrTail->ptrNext = ptrNewNode;
        ptrList->ptrTail = ptrNewNode;
    }
}

void deleteList(DoublyLinkedList* ptrList) {
    Node* ptrCurrent = ptrList->ptrHead;
    while (ptrCurrent != nullptr) {
        Node* ptrNext = ptrCurrent->ptrNext;
        delete ptrCurrent;
        ptrCurrent = ptrNext;
    }
    delete ptrList;
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

DoublyLinkedList* createList() {
    DoublyLinkedList* ptrList = new DoublyLinkedList();
    ptrList->ptrHead = nullptr;
    ptrList->ptrTail = nullptr;
    return ptrList;
}

DoublyLinkedList* createListByArray(int iArr[], int iSize) {
    DoublyLinkedList* ptrList = createList();
    for (int i = 0; i < iSize; i++) {
        insertEnd(ptrList, iArr[i]);
    }
    return ptrList;
}

void pushList(DoublyLinkedList* ptrList, int iPayload) {
    Node* ptrNewNode = new Node();
    ptrNewNode->iPayload = iPayload;
    ptrNewNode->ptrNext = nullptr;
    ptrNewNode->ptrPrev = ptrList->ptrTail;
    
    if (ptrList->ptrTail != nullptr) {
        ptrList->ptrTail->ptrNext = ptrNewNode;
    } else {
        ptrList->ptrHead = ptrNewNode;
    }
    
    ptrList->ptrTail = ptrNewNode;
}

Node* popList(DoublyLinkedList* ptrList) {
    if (isEmpty(ptrList)) return nullptr;
    Node* ptrTemp = ptrList->ptrHead;
    ptrList->ptrHead = ptrList->ptrHead->ptrNext;
    
    if (ptrList->ptrHead != nullptr) {
        ptrList->ptrHead->ptrPrev = nullptr;
    } else {
        ptrList->ptrTail = nullptr;
    }
    
    return ptrTemp;
}

bool isEmpty(DoublyLinkedList* ptrList) {
    return ptrList->ptrHead == nullptr;
}

Node* searchList(DoublyLinkedList* ptrList, int iValue) {
    Node* ptrCurrent = ptrList->ptrHead;
    while (ptrCurrent != nullptr) {
        if (ptrCurrent->iPayload == iValue) {
            return ptrCurrent;
        }
        ptrCurrent = ptrCurrent->ptrNext;
    }
    return nullptr;
}