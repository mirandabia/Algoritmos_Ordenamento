#include "../headers/radixSort.h"
#include "../headers/insertionSort.h"

// Função para inserir um nó no final da lista
void append(Node** ptrHeadRef, int iPayload) {
    Node* ptrNewNode = new Node();
    ptrNewNode->iPayload = iPayload;
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
    int iMax = ptrHead->iPayload;
    Node* ptrNode = ptrHead;
    while (ptrNode != nullptr) {
        if (ptrNode->iPayload > iMax)
            iMax = ptrNode->iPayload;
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
        int iIndex = (ptrNode->iPayload / iExp) % 10;
        iCount[iIndex]++;
        ptrNode = ptrNode->ptrNext;
    }

    // Constrói o array de saída
    ptrNode = *ptrHead;
    while (ptrNode != nullptr) {
        int iIndex = (ptrNode->iPayload / iExp) % 10;
        append(&ptrOutput[iIndex], ptrNode->iPayload);
        ptrNode = ptrNode->ptrNext;
    }

    // Reconstrói a lista original com os nós ordenados
    *ptrHead = nullptr;
    for (int i = 0; i < 10; i++) {
        Node* ptrTempNode = ptrOutput[i];
        while (ptrTempNode != nullptr) {
            append(ptrHead, ptrTempNode->iPayload);
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