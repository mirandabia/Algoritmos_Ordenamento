#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

struct Node {
    int iPayload;
    Node* ptrNext = nullptr;
    Node* ptrPrev = nullptr;
};

Node* createNode(int iValue) {
    Node* ptrNode = new Node; // Usando new em vez de malloc
    ptrNode->iPayload = iValue;
    return ptrNode;
}

void displayList(Node* ptrNode) {
    if (!ptrNode) {
        cout << "Lista vazia: não é possível realizar displayList" << endl;
        return;
    }
    
    cout << "Payload: ";
    while (ptrNode) {
        cout << ptrNode->iPayload << " ";
        ptrNode = ptrNode->ptrNext;
    }
    cout << endl;
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
        delete ptrCurrent; // Usando delete em vez de free
        ptrCurrent = ptrNext;
    }
    *ptrHead = nullptr;
}

void swapValue(Node* ptrNode1, Node* ptrNode2) {
    int iTemp = ptrNode1->iPayload;
    ptrNode1->iPayload = ptrNode2->iPayload;
    ptrNode2->iPayload = iTemp;
}

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

int main() {
    Node* ptrList1 = nullptr;
    Node* ptrList2 = nullptr;
    int iTestLength = 5;
    for (int i = 0; i < iTestLength; i++) {
        int iRandomVal = rand() % 100 + 1;
        insertEnd(&ptrList1, iRandomVal);
        insertEnd(&ptrList2, iRandomVal);
    }

    cout << "Lista desorganizada: " << endl;
    displayList(ptrList1);

    cout << endl << "Selection Sort (Padrão): " << endl;
    selectionSort(&ptrList1, iTestLength);
    displayList(ptrList1);

    cout << endl << "Selection Sort (Otimizado): " << endl;
    optimizedSelectionSort(&ptrList2, iTestLength);
    displayList(ptrList2);

    deleteList(&ptrList1);
    deleteList(&ptrList2);

    return 0;
}
