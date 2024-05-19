#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

struct Node 
{
    int iPayload; 
    Node* ptrNext;
    Node* ptrPrev;
};

Node* createNode(int iValue) 
{
    Node* ptrNode = new Node;
    ptrNode->iPayload = iValue;
    ptrNode->ptrNext = nullptr;
    ptrNode->ptrPrev = nullptr;
    
    return ptrNode;
}

void displayList(Node* ptrNode) 
{
    if (ptrNode == nullptr)
    {
        cout << "Lista vazia: não é possível realizar displayList" << endl;
        return;
    }
    
    if (ptrNode->ptrPrev != nullptr)
    {
        cout << "O elemento está no meio ou fim da lista: não é possível realizar displayList" << endl;
        return;
    }
    
    Node* ptrTemp = ptrNode;
    cout << "Payload: ";
    while (ptrTemp != nullptr)
    {
        cout << ptrTemp->iPayload << " ";
        ptrTemp = ptrTemp->ptrNext;
    }
    cout << endl;
}

void insertEnd(Node** ptrHead, int iValue)
{
    Node* ptrNewNode = createNode(iValue);
    if (*ptrHead == nullptr) 
    {
        *ptrHead = ptrNewNode; 
        return;
    }
    
    Node* ptrTemp = *ptrHead;
    while (ptrTemp->ptrNext != nullptr)
    {
        ptrTemp = ptrTemp->ptrNext;
    }
    
    ptrNewNode->ptrPrev = ptrTemp;
    ptrTemp->ptrNext = ptrNewNode;
}

void deleteList(Node** ptrHead) 
{
    Node* ptrCurrent = *ptrHead;
    Node* ptrNext = nullptr;

    while (ptrCurrent != nullptr) 
    {
        ptrNext = ptrCurrent->ptrNext;
        delete ptrCurrent; // Usando delete ao invés de free
        ptrCurrent = ptrNext;
    }

    *ptrHead = nullptr;
}

void insertionSort(Node** ptrHead)
{
    if (*ptrHead == nullptr || (*ptrHead)->ptrNext == nullptr)
        return;

    Node* ptrSorted = nullptr;
    Node* ptrCurrent = *ptrHead;
    while (ptrCurrent != nullptr)
    {
        Node* ptrNext = ptrCurrent->ptrNext;
        if (ptrCurrent->ptrPrev)
            ptrCurrent->ptrPrev->ptrNext = ptrCurrent->ptrNext;
        if (ptrCurrent->ptrNext)
            ptrCurrent->ptrNext->ptrPrev = ptrCurrent->ptrPrev;

        if (ptrSorted == nullptr || ptrSorted->iPayload >= ptrCurrent->iPayload)
        {
            ptrCurrent->ptrNext = ptrSorted;
            ptrCurrent->ptrPrev = nullptr;
            if (ptrSorted)
                ptrSorted->ptrPrev = ptrCurrent;
            ptrSorted = ptrCurrent;
        }
        else
        {
            Node* ptrTemp = ptrSorted;
            while (ptrTemp->ptrNext != nullptr && ptrTemp->ptrNext->iPayload < ptrCurrent->iPayload)
            {
                ptrTemp = ptrTemp->ptrNext;
            }
            ptrCurrent->ptrNext = ptrTemp->ptrNext;
            ptrCurrent->ptrPrev = ptrTemp;
            if (ptrTemp->ptrNext)
                ptrTemp->ptrNext->ptrPrev = ptrCurrent;
            ptrTemp->ptrNext = ptrCurrent;
        }
        ptrCurrent = ptrNext;
    }
    *ptrHead = ptrSorted;
}

int main()
{
    Node* ptrList1 = nullptr;
    int iTestLength = 15;
    for (int iPos = 0; iPos < iTestLength; iPos++)
    {
        int iRandomVal = rand() % 100 + 1;
        insertEnd(&ptrList1, iRandomVal);
    }

    cout << "Lista desorganizada: " << endl;
    displayList(ptrList1);

    cout << endl << "Insertion Sort:" << endl;
    insertionSort(&ptrList1);
    displayList(ptrList1);

    deleteList(&ptrList1);

    return 0;
}
