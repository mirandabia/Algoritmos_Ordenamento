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

void selectionSort(Node**, int);
void optimizedSelectionSort(Node**, int);

double mean(float*, int);
double var(float*, int, double);

int main()
{   
    // =============== Teste de Funcionalidade ===============
    Node* list1 = nullptr;
    Node* list2 = nullptr;

    // Popula as listas
    int iTestLength = 5;
    for (int iPos = 0; iPos < iTestLength; iPos++)
    {
        int iRandomVal = rand() %100 + 1;  // Gera um número aleatório entre 1 e 200
        insertEnd(&list1, iRandomVal);
        insertEnd(&list2, iRandomVal);
    }

    cout << "Lista desorganizada: " << endl;
    displayList(list1);
    
    cout << endl << "Selection Sort (Padrão): " << endl;
    selectionSort(&list1, iTestLength);
    displayList(list1);

    cout << endl << "Selection Sort (Otimizado): " << endl;
    optimizedSelectionSort(&list2, iTestLength);
    displayList(list2);

    cout << endl << endl;


    // =============== Análise Estátistica =============== 

    // Variáveis relativas ao registros de tempo
    int iAmountTests = 10000;
    float arrfTimeDefault[iAmountTests];
    float arrfTimeoptimized[iAmountTests];

    // Amostras da distribuição do tempo para organizar uma lista
    int iLength = 100;

    for (int iSample = 0; iSample < iAmountTests; iSample++) 
    {
        // Criação das listas
        Node* head1 = nullptr;
        Node* head2 = nullptr;

        // Popula as listas
        for (int iPos = 0; iPos < iLength; iPos++)
        {
            int iRandomVal = rand() %1000 + 1;  // Gera um número aleatório entre 1 e 1000
            insertEnd(&head1, iRandomVal);
            insertEnd(&head2, iRandomVal);
        }


        // Captura o tempo de ordenação do algoritmo padrão (Selection Sort)
        auto timeStart_1 = high_resolution_clock::now();
        selectionSort(&head1, iLength);
        auto timeStop_1 = high_resolution_clock::now();

        auto timeDuration_1 = duration_cast<microseconds>(timeStop_1 - timeStart_1);
        arrfTimeDefault[iSample] = (float) timeDuration_1.count(); // Tempo em microsegundos


        // Captura o tempo de ordenação do algoritmo otimizado (Selection Sort)
        auto timeStart_2 = high_resolution_clock::now();
        optimizedSelectionSort(&head2, iLength);
        auto timeStop_2 = high_resolution_clock::now();

        auto timeDuration_2 = duration_cast<microseconds>(timeStop_2 - timeStart_2);
        arrfTimeoptimized[iSample] = (float) timeDuration_2.count(); // Tempo em microsegundo


        // Limpando a memória alocada para as listas
        deleteList(&head1);
        deleteList(&head2);
    }


    // Dados - Algoritmo 1
    double mean_1 = mean(&arrfTimeDefault[0], iAmountTests);
    double variance_1 = var(&arrfTimeDefault[0], iAmountTests, mean_1);

    cout << "Dados do algoritimo padrão: " << endl;
    cout << "Média: " << mean_1 << endl; 
    cout << "Variância: " << variance_1 << endl; 
    cout << endl;

    // Dados - Algoritmo 2
    double mean_2 = mean(&arrfTimeoptimized[0], iAmountTests);
    double variance_2 = var(&arrfTimeoptimized[0], iAmountTests, mean_2);

    cout << "Dados do algoritimo otimizado: " << endl;
    cout << "Média: " << mean_2 << endl; 
    cout << "Variância: " << variance_2 << endl;

    return 0;
}


void swapValue(Node** Value_1, Node** Value_2) 
{
    int temp = (*Value_1)->iPayload;
    (*Value_1)->iPayload = (*Value_2)->iPayload;
    (*Value_2)->iPayload = temp;
}


void selectionSort(Node** ptrHead, int iLenght)
{   
    Node* ptrOut = *ptrHead;

    for (int iOuterLoop = 0; iOuterLoop < iLenght; iOuterLoop++) 
    {
        Node* ptrIn = ptrOut->ptrNext;

        for (int iInnerLoop = iOuterLoop + 1; iInnerLoop < iLenght; iInnerLoop++)
        {
            if (ptrOut->iPayload > ptrIn->iPayload)
            {
                swapValue(&ptrOut, &ptrIn);
            }
            ptrIn = ptrIn->ptrNext;
        }
        ptrOut = ptrOut->ptrNext;
    }
}

void optimizedSelectionSort(Node** ptrHead, int iLength)
{
    Node* ptrOut = *ptrHead;

    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++) 
    {
        Node* ptrMin = ptrOut;
        Node* ptrIn = ptrOut->ptrNext;

        for (int iInnerLoop = iOuterLoop + 1; iInnerLoop < iLength; iInnerLoop++)
        {
            if (ptrIn->iPayload < ptrMin->iPayload)
            {
                ptrMin = ptrIn;
            }
            ptrIn = ptrIn->ptrNext;
        }

        swapValue(&ptrOut, &ptrMin);
        ptrOut = ptrOut->ptrNext;
    }
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
