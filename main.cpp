#include "headers/doublyLinkedList.h"
#include "headers/bubbleSort.h"
#include "headers/selectionSort.h"
#include "headers/insertionSort.h"
#include "headers/radixSort.h"
#include "headers/tree.h"
#include "headers/time_measure.h"

#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

int main()
{
    // =======================================================================
    // ================= Parte 1 - Algoritmos de Ordenamento =================
    // =======================================================================

    int iAmountOfTests = 100; // Quantidade de testes
    int iLength = 10000; // Tamanho das listas
    int iExecutionTime;

    for (int i = 0; i < iAmountOfTests; i++)
    {    
        DoublyLinkedList* ptrList = createList(); // Inicializa a lista corretamente
        
        // Popula a lista
        for (int iPos = 0; iPos < iLength; iPos++)
        {
            int iRandomVal = rand() % 100 + 1;  // Gera um número aleatório entre 1 e 100
            insertEnd(ptrList, iRandomVal);
        }

        Node* ptrHead = ptrList->ptrHead; 

        // Captura o tempo inicial
        auto timeStart_1 = chrono::high_resolution_clock::now();

        // ------ Seleciona o algoritmo de ordenação ------ 
        // bubbleSort(&ptrHead, iLength);
        // optimizationBubbleSort(&ptrHead, iLength);
        // selectionSort(&ptrHead, iLength);
        // optimizedSelectionSort(&ptrHead, iLength);
        // insertionSort(&ptrHead);
        radixSort(&ptrHead);
        // ------ Seleciona o algoritmo de ordenação ------ 

        // Captura o tempo após a ordenação
        auto timeStop_1 = high_resolution_clock::now();

        // Calcula o tempo de execução em microsegundos
        auto timeDuration_1 = duration_cast<microseconds>(timeStop_1 - timeStart_1);
        iExecutionTime = (int) timeDuration_1.count(); 

        // Limpando a memória alocada para as listas
        deleteList(ptrList);

        // Exibe o tempo de execução
        cout << iExecutionTime << endl;
    }

    // ==============================================================
    // ================= Parte 2 - Busca em Árvores =================
    // ==============================================================

    return 0;
}
