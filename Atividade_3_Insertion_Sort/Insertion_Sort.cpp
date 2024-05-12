#include <iostream>
#include <chrono>
#include <random>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

using std::cout;
using std::endl;

typedef struct Node 
{
    int iPayload; 
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void displayList(Node*);
void insertEnd(Node**, int);
void deleteList(Node**);
void swapValue(Node**, Node**);

void insertionSort(Node**);
double mean(float*, int);
double var(float*, int, double);

int main()
{
    Node* list1 = nullptr;
    int iTestLength = 15;
    for (int iPos = 0; iPos < iTestLength; iPos++)
    {
        int iRandomVal = rand() % 100 + 1;
        insertEnd(&list1, iRandomVal);
    }

    cout << "Lista desorganizada: " << endl;
    displayList(list1);

    cout << endl << "Insertion Sort:" << endl;
    insertionSort(&list1);
    displayList(list1);

    cout << endl << endl;
}

void insertionSort(Node** ptrHead)
{
    if (*ptrHead == nullptr || (*ptrHead)->ptrNext == nullptr)
        return;

    Node* sorted = nullptr;
    Node* current = *ptrHead;
    while (current != nullptr)
    {
        Node* next = current->ptrNext;
        // Desconecta o nó atual da lista original
        if (current->ptrPrev)
            current->ptrPrev->ptrNext = current->ptrNext;
        if (current->ptrNext)
            current->ptrNext->ptrPrev = current->ptrPrev;

        // Inserção na lista ordenada
        if (sorted == nullptr || sorted->iPayload >= current->iPayload)
        {
            current->ptrNext = sorted;
            current->ptrPrev = nullptr;
            if (sorted)
                sorted->ptrPrev = current;
            sorted = current;
        }
        else
        {
            Node* temp = sorted;
            while (temp->ptrNext != nullptr && temp->ptrNext->iPayload < current->iPayload)
            {
                temp = temp->ptrNext;
            }
            current->ptrNext = temp->ptrNext;
            current->ptrPrev = temp;
            if (temp->ptrNext)
                temp->ptrNext->ptrPrev = current;
            temp->ptrNext = current;
        }
        current = next;
        }
    *ptrHead = sorted;
}


Node* createNode(int iValue)
{
    Node* temp = (Node*)malloc(sizeof(Node)); // Manteve o uso de malloc
    temp->iPayload = iValue;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}


void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: não é possível realizar displayList" << endl;
        return;
    }
    
    // se receber um nó do meio, rejeito (um modo)
    if (node->ptrPrev != nullptr)
    {
        cout << "O elemento está no meio ou fim da lista: não é possível realizar displayList" << endl;
        return;
    }
    
    Node* temp = node;

    cout << "Payload: ";
    
    while (temp != nullptr)
    {
        cout <<  temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}


void insertEnd(Node** head, int iValue)
{
    Node* newNode = createNode(iValue);

    if (*head == nullptr) 
    {
        *head = newNode; 
        return;
    }
    
    Node* temp = *head;
    while (temp->ptrNext != nullptr)
    {
        temp = temp->ptrNext;
    }
    
    newNode->ptrPrev = temp;
    temp->ptrNext = newNode;
}


void deleteList(Node** head) 
{
    Node* current = *head;
    Node* next;

    while (current != nullptr) {
        next = current->ptrNext;
        free(current);
        current = next;
    }

    *head = nullptr;
}


double mean(float* ptrArrf, int iLength) {
    double llSoma = 0;

    for (int i = 0; i < iLength; i++)
    {
        llSoma +=  *(ptrArrf + i);
    } 

    double dMean = llSoma / static_cast<double>(iLength);

    return dMean;
}


double var(float* ptrArrf, int iLength, double dMean) {
    double llSoma = 0;

    for (int i = 0; i < iLength; i++)
    {
        double iDiff = *(ptrArrf + i) - dMean;
        
        llSoma += iDiff * iDiff;
    } 

    double dVar = llSoma / static_cast<double>(iLength);

    return dVar;
}
