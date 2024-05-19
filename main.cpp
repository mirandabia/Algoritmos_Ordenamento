#include "headers/doublyLinkedList.h"
#include "headers/bubbleSort.h"
#include "headers/selectionSort.h"
#include "headers/insertionSort.h"

#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

int main()
{
    int iAmountOfTests = 1000;
    int iLength = 1000;
    int iExecutionTime;

    for (int i = 0; i < iAmountOfTests; i++)
    {    
        Node* ptrHead = nullptr;
        
        // Popula as listas
        for (int iPos = 0; iPos < iLength; iPos++)
        {
            int iRandomVal = rand() % (iLength * 10) + 1;  // Gera um número aleatório entre 1 e 10.000
            insertEnd(&ptrHead, iRandomVal);
        }

        // Captura o tempo inicial
        auto timeStart_1 = chrono::high_resolution_clock::now();

        // ------ Seleciona o algoritmo de ordenação ------ 
        bubbleSort(&ptrHead, iLength);
        // optimizationBubbleSort(&ptrHead, iLength);
        // selectionSort(&ptrHead, iLength);
        // optimizedSelectionSort(&ptrHead, iLength);
        // insertionSort(&ptrHead);
        // ------ Seleciona o algoritmo de ordenação ------ 

        // Captura o tempo após a ordenação
        auto timeStop_1 = high_resolution_clock::now();

        // Calcula o tempo de execução em nanosegundos
        auto timeDuration_1 = duration_cast<microseconds>(timeStop_1 - timeStart_1);
        iExecutionTime = (int) timeDuration_1.count(); 

        // Limpando a memória alocada para as listas
        deleteList(&ptrHead);

        // Exibe o tempo de execução
        cout << iExecutionTime << endl;
    }
}