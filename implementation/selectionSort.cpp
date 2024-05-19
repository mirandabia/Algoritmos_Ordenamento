#include "../headers/selectionSort.h"

void selectionSort(Node** ptrHead, int iLength) {
    Node* ptrOut = *ptrHead;
    for (int i = 0; i < iLength; i++) {
        Node* ptrMin = ptrOut;
        for (Node* ptrIn = ptrOut->ptrNext; ptrIn; ptrIn = ptrIn->ptrNext) {
            if (ptrIn->iPayload < ptrMin->iPayload) {
                ptrMin = ptrIn;
            }
        }
        swapValue(ptrOut, ptrMin);
        ptrOut = ptrOut->ptrNext;
    }
}

void optimizedSelectionSort(Node** ptrHead, int iLength) {
    Node* ptrOut = *ptrHead;
    for (int i = 0; i < iLength - 1; i++) {
        Node* ptrMin = ptrOut;
        for (Node* ptrIn = ptrOut->ptrNext; ptrIn; ptrIn = ptrIn->ptrNext) {
            if (ptrIn->iPayload < ptrMin->iPayload) {
                ptrMin = ptrIn;
            }
        }
        if (ptrMin != ptrOut) {
            swapValue(ptrOut, ptrMin);
        }
        ptrOut = ptrOut->ptrNext;
    }
}