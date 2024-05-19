#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

struct Node {
    int iPayload;
    Node* ptrNext = nullptr;
    Node* ptrPrev = nullptr;
};

Node* createNode(int iValue) {
    return new Node{iValue, nullptr, nullptr};
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
        cout << "Lista vazia." << endl;
        return;
    }
    cout << "Payload: ";
    while (ptrNode) {
        cout << ptrNode->iPayload << " ";
        ptrNode = ptrNode->ptrNext;
    }
    cout << endl;
}

void swapValue(Node* ptrNode1, Node* ptrNode2) {
    int iTemp = ptrNode1->iPayload;
    ptrNode1->iPayload = ptrNode2->iPayload;
    ptrNode2->iPayload = iTemp;
}

void bubbleSort(Node** ptrHead, int iLength) 
{
    Node* current = *ptrHead;
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
    {
        current = *ptrHead; // Reinicializa o ponteiro current 
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++)
        {
            if (current->iPayload > current->ptrNext->iPayload)
            {
                swapValue(current, (current->ptrNext));
            }
            current = current->ptrNext;
        }
    }
}

void optimizationBubbleSort(Node** ptrHead, int iLength) 
{
    Node* current = *ptrHead;
    bool bUnordered = false;
    
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
    {
        current = *ptrHead; // Reinicializa o ponteiro current no início de cada iteração
        bUnordered = false;
        
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++)
        {
            if (current->iPayload > current->ptrNext->iPayload)
            {
                swapValue(current, (current->ptrNext));
                bUnordered = true;
            }
            current = current->ptrNext;
        }

        if (!bUnordered) {
            break;
        }
    }
}

int main() {
    Node* ptrHead = nullptr;

    int iSize = 10;
    for (int iIndex = 0; iIndex < iSize; iIndex++) {
        insertEnd(&ptrHead, rand() % 100 + 1);
    }

    cout << "Lista desorganizada: " << endl;
    displayList(ptrHead);

    bubbleSort(&ptrHead, iSize);
    cout << "Lista após o Bubble Sort: " << endl;
    displayList(ptrHead);

    deleteList(&ptrHead);
    ptrHead = nullptr;

    for (int iIndex = 0; iIndex < 10; iIndex++) {
        insertEnd(&ptrHead, rand() % 100 + 1);
    }

    cout << "\nNova lista desorganizada para teste otimizado: " << endl;
    displayList(ptrHead);

    optimizationBubbleSort(&ptrHead, iSize);
    cout << "Lista após o Bubble Sort Otimizado: " << endl;
    displayList(ptrHead);

    deleteList(&ptrHead);
}