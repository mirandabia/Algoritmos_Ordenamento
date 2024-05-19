#include "../headers/bubbleSort.h"

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