#include "../headers/insertionSort.h"

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