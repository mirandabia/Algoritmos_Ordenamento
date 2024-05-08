#include <iostream>
#include <chrono>
#include <random>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

using std::cout;
using std::endl;
using std::string;

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

void bubbleSort(Node**, int);
void optimizationBubbleSort(Node**, int);

double mean(float*, int);
double var(float*, int, double);
void changeArrayScale(float*, int, int);

int main()
{   
    // =============== Teste de Funcionalidade ===============
    Node* list1 = nullptr;
    Node* list2 = nullptr;

    // Popula as listas
    int iTestLength = 10;
    for (int iPos = 0; iPos < iTestLength; iPos++)
    {
        int iRandomVal = rand() %100 + 1;  // Gera um número aleatório entre 1 e 1000
        insertEnd(&list1, iRandomVal);
        insertEnd(&list2, iRandomVal);
    }

    cout << "Lista desorganizada: " << endl;
    displayList(list1);
    
    cout << endl << "Bubble Sort (Padrão): " << endl;
    bubbleSort(&list1, iTestLength);
    displayList(list1);

    cout << endl << "Bubble Sort (Otimizado): " << endl;
    optimizationBubbleSort(&list2, iTestLength);
    displayList(list2);

    cout << endl << endl;


    // =============== Análise Estátistica =============== 

    // Variáveis relativas ao registros de tempo
    int iAmountTests = 10000; // 10.000 testes
    float arrfTimeDefault[iAmountTests];
    float arrfTimeOptmized[iAmountTests];

    // Amostras da distribuição do tempo para organizar uma lista
    int iLength = 100;

    for (int iSample = 0; iSample < iAmountTests; iSample++) 
    {
        // Criação das listas
        Node* ptrHead1 = nullptr;
        Node* ptrHead2 = nullptr;

        // Popula as listas
        for (int iPos = 0; iPos < iLength; iPos++)
        {
            int iRandomVal = rand() %10000 + 1;  // Gera um número aleatório entre 1 e 10.000
            insertEnd(&ptrHead1, iRandomVal);
            insertEnd(&ptrHead2, iRandomVal);
        }


        // Captura o tempo de ordenação do algoritmo padrão (Bubble Sort)
        auto timeStart_1 = high_resolution_clock::now();
        bubbleSort(&ptrHead1, iLength);
        auto timeStop_1 = high_resolution_clock::now();

        auto timeDuration_1 = duration_cast<microseconds>(timeStop_1 - timeStart_1);
        arrfTimeDefault[iSample] = (float) timeDuration_1.count(); // Tempo em nanosegundos


        // Captura o tempo de ordenação do algoritmo otimizado (Bubble Sort)
        auto timeStart_2 = high_resolution_clock::now();
        optimizationBubbleSort(&ptrHead2, iLength);
        auto timeStop_2 = high_resolution_clock::now();

        auto timeDuration_2 = duration_cast<microseconds>(timeStop_2 - timeStart_2);
        arrfTimeOptmized[iSample] = (float) timeDuration_2.count(); // Tempo em nanosegundos


        // Limpando a memória alocada para as listas
        deleteList(&ptrHead1);
        deleteList(&ptrHead2);
    }


    // Dados - Algoritmo 1
    double mean_1 = mean(&arrfTimeDefault[0], iAmountTests);
    double variance_1 = var(&arrfTimeDefault[0], iAmountTests, mean_1);

    cout << "Dados do algoritimo padrão: " << endl;
    cout << "Média: " << mean_1 << endl; 
    cout << "Variância: " << variance_1 << endl;
    cout << endl;

    // Dados - Algoritmo 2
    double mean_2 = mean(&arrfTimeOptmized[0], iAmountTests);
    double variance_2 = var(&arrfTimeOptmized[0], iAmountTests, mean_2);

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


void bubbleSort(Node** ptrHead, int iLength) 
{
    Node* current = *ptrHead;
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
    {
        current = *ptrHead; // Reinicializa o ponteiro current no início de cada iteração
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++)
        {
            if (current->iPayload > current->ptrNext->iPayload)
            {
                swapValue(&current, &(current->ptrNext));
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
                swapValue(&current, &(current->ptrNext));
                bUnordered = true;
            }
            current = current->ptrNext;
        }

        if (!bUnordered) {
            break;
        }
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


void insertEnd(Node** ptrHead, int iValue)
{
    Node* newNode = createNode(iValue);

    if (*ptrHead == nullptr) 
    {
        *ptrHead = newNode; 
        return;
    }
    
    Node* temp = *ptrHead;
    while (temp->ptrNext != nullptr)
    {
        temp = temp->ptrNext;
    }
    
    newNode->ptrPrev = temp; // newnode aponta para o fim da lista
    temp->ptrNext = newNode; // antigo ultimo elemento aponta para o novo nó
}


void deleteList(Node** ptrHead) 
{
    Node* current = *ptrHead;
    Node* next;

    while (current != nullptr) {
        next = current->ptrNext;
        free(current); // Manteve o uso de free
        current = next;
    }

    *ptrHead = nullptr;
}


double mean(float* ptrArrf, int iLength) {
    double llSoma = 0; 

    for (int i = 0; i < iLength; i++)
    {
        llSoma +=  *(ptrArrf + i); 
    } 

    double dMean = llSoma / iLength; 

    return dMean;
}


double var(float* ptrArrf, int iLength, double dMean) {
    double llSoma = 0;

    for (int i = 0; i < iLength; i++)
    {
        double iDiff = *(ptrArrf + i) - dMean;
        
        llSoma += iDiff * iDiff;
    } 

    double dVar = llSoma / iLength;

    return dVar;
}