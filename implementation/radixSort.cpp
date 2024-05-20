#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int iData;
    Node* ptrNext;
    Node* ptrPrev;
};

// Função para inserir um nó no final da lista
void append(Node** ptrHeadRef, int iData) {
    Node* ptrNewNode = new Node();
    ptrNewNode->iData = iData;
    ptrNewNode->ptrNext = nullptr;
    ptrNewNode->ptrPrev = nullptr;

    if (*ptrHeadRef == nullptr) {
        *ptrHeadRef = ptrNewNode;
    } else {
        Node* ptrLast = *ptrHeadRef;
        while (ptrLast->ptrNext != nullptr) {
            ptrLast = ptrLast->ptrNext;
        }
        ptrLast->ptrNext = ptrNewNode;
        ptrNewNode->ptrPrev = ptrLast;
    }
}

// Função para encontrar o maior número na lista
int getMax(Node* ptrHead) {
    int iMax = ptrHead->iData;
    Node* ptrNode = ptrHead;
    while (ptrNode != nullptr) {
        if (ptrNode->iData > iMax)
            iMax = ptrNode->iData;
        ptrNode = ptrNode->ptrNext;
    }
    return iMax;
}

// Função para fazer a ordenação por contagem na lista com base em iExp
void countSort(Node** ptrHead, int iExp) {
    Node* ptrOutput[10] = {nullptr};
    int iCount[10] = {0};
    Node* ptrNode = *ptrHead;

    // Preenche as contagens
    while (ptrNode != nullptr) {
        int iIndex = (ptrNode->iData / iExp) % 10;
        iCount[iIndex]++;
        ptrNode = ptrNode->ptrNext;
    }

    // Constrói o array de saída
    ptrNode = *ptrHead;
    while (ptrNode != nullptr) {
        int iIndex = (ptrNode->iData / iExp) % 10;
        append(&ptrOutput[iIndex], ptrNode->iData);
        ptrNode = ptrNode->ptrNext;
    }

    // Reconstrói a lista original com os nós ordenados
    *ptrHead = nullptr;
    for (int i = 0; i < 10; i++) {
        Node* ptrTempNode = ptrOutput[i];
        while (ptrTempNode != nullptr) {
            append(ptrHead, ptrTempNode->iData);
            ptrTempNode = ptrTempNode->ptrNext;
        }
    }
}

// Função para ordenar a lista usando Radix Sort
void radixSort(Node** ptrHead) {
    int iMax = getMax(*ptrHead);
    for (int iExp = 1; iMax / iExp > 0; iExp *= 10) {
        countSort(ptrHead, iExp);
    }
}

// Função para imprimir a lista
void printList(Node* ptrNode) {
    while (ptrNode != nullptr) {
        cout << ptrNode->iData << " ";
        ptrNode = ptrNode->ptrNext;
    }
    cout << endl;
}

int main() {
    Node* ptrHead = nullptr;
    append(&ptrHead, 170);
    append(&ptrHead, 45);
    append(&ptrHead, 75);
    append(&ptrHead, 90);
    append(&ptrHead, 802);
    append(&ptrHead, 24);
    append(&ptrHead, 2);
    append(&ptrHead, 66);

    cout << "Lista original:\n";
    printList(ptrHead);

    radixSort(&ptrHead);

    cout << "Lista ordenada:\n";
    printList(ptrHead);

    return 0;
}
