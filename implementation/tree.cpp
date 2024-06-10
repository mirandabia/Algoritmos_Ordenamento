#include "../headers/tree.h"

Node* createTreeByArray(int iArr[], int iSize)
{
    Node* ptrRoot = nullptr;
    
    for (int i = 0; i < iSize; i++)
    {
        ptrRoot = insertNode(ptrRoot, iArr[i]);
    }
    
    return ptrRoot;
}

Node* insertNode(Node* startingNode, int iData)
{
    if(startingNode == nullptr)
    {
        return createNode(iData);
    }
    
    if(iData < startingNode->iPayload)
    {
        startingNode->ptrPrev = insertNode(startingNode->ptrPrev, iData);
    }
    else
    {
        startingNode->ptrNext = insertNode(startingNode->ptrNext, iData);
    }
    
    return startingNode;
}

void destroyTree(Node* startingNode)
{
    if(startingNode == nullptr)
    {
        return;
    }
    
    destroyTree(startingNode->ptrPrev);
    destroyTree(startingNode->ptrNext);
    
    free(startingNode);
}

Node* deleteNode(Node* startingNode, int iData)
{
    if (startingNode == nullptr) return nullptr;
    
    if (iData < startingNode->iPayload) startingNode->ptrPrev = deleteNode(startingNode->ptrPrev, iData);
    else if (iData > startingNode->iPayload) startingNode->ptrNext = deleteNode(startingNode->ptrNext, iData);
    else
    {
        Node* ptrTemp = nullptr;
        
        if (startingNode->ptrPrev == nullptr)
        {
            ptrTemp = startingNode->ptrNext;
            free(startingNode);
            return ptrTemp;
        }
        else if (startingNode->ptrNext == nullptr)
        {
            ptrTemp = startingNode->ptrPrev;
            free(startingNode);
            return ptrTemp;            
        }
        
        ptrTemp = lesserLeaf(startingNode->ptrNext);
        
        startingNode->iPayload = ptrTemp->iPayload;
        
        startingNode->ptrNext = deleteNode(startingNode->ptrNext, ptrTemp->iPayload);
    }
    
    return startingNode;
}

Node* lesserLeaf(Node* startingNode)
{
    Node* ptrCurrent = startingNode;
 
    while (ptrCurrent && ptrCurrent->ptrPrev != nullptr) ptrCurrent = ptrCurrent->ptrPrev;
    
    return ptrCurrent;
}

Node* higherLeaf(Node* startingNode)
{
    Node* ptrCurrent = startingNode;
 
    while (ptrCurrent && ptrCurrent->ptrNext != nullptr) ptrCurrent = ptrCurrent->ptrNext;
    
    return ptrCurrent;
}

void printTree(Node* startingNode)
{
    if (startingNode == nullptr) return;
    
    printTree(startingNode->ptrPrev);
    cout << startingNode->iPayload << " ";
    printTree(startingNode->ptrNext);
}

Node* searchDFS(Node* startingNode, int iValue)
{
    if(startingNode == nullptr) return nullptr;
    else if(iValue == startingNode->iPayload) return startingNode;
    else if(iValue < startingNode->iPayload) return searchDFS(startingNode->ptrPrev, iValue);
    else return searchDFS(startingNode->ptrNext, iValue);
}

Node* searchBFS(Node* startingNode, int iValue) {
    if (startingNode == nullptr) return nullptr;

    DoublyLinkedList* ptrQueue = createList();
    pushList(ptrQueue, startingNode->iPayload);  // Armazenar o ponteiro do nó como inteiro

    while (!isEmpty(ptrQueue)) {
        Node* ptrCurrent = popList(ptrQueue);

        if (ptrCurrent->iPayload == iValue) {
            deleteList(ptrQueue);
            return ptrCurrent;
        }

        if (ptrCurrent->ptrPrev != nullptr) {
            pushList(ptrQueue, ptrCurrent->ptrPrev->iPayload);
        }

        if (ptrCurrent->ptrNext != nullptr) {
            pushList(ptrQueue, (int)ptrCurrent->ptrNext->iPayload);
        }
    }

    deleteList(ptrQueue);
    return nullptr;
}