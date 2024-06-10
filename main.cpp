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
#include <fstream>

using namespace std;
using namespace std::chrono;

void saveArray(int[], int, string);

int main()
{
    // =======================================================================
    // ================= Parte 1 - Algoritmos de Ordenamento =================
    // =======================================================================

    int iAmountOfTests = 100; // Quantidade de testes
    int iLength = 10000; // Tamanho das listas

    // Vetores para armazenar os tempos de execução
    int timeBubble[iAmountOfTests];
    int timeBubbleOptimized[iAmountOfTests];
    int timeIsertion[iAmountOfTests];
    int timeSelection[iAmountOfTests];
    int timeSelectionOptimized[iAmountOfTests];
    int timeRadix[iAmountOfTests];

    // Testes para os tempos de execução dos algoritmos de ordenamento
    for (int i = 0; i < iAmountOfTests; i++)
    {    
        DoublyLinkedList* ptrList = createList(); // Inicializa a lista corretamente
        
        // Popula a lista
        for (int iPos = 0; iPos < iLength; iPos++)
        {
            int iRandomVal = rand() % 100 + 1;  // Gera um número aleatório entre 1 e 100
            insertEnd(ptrList, iRandomVal);
        }

        for (int j = 0; j < 6; j++) // Loop para chamar cada função de ordenamento
        {
            DoublyLinkedList* listCopy = copyList(ptrList); // Copia a lista para não alterar a original
            Node* ptrCopy = listCopy->ptrHead; 

            switch (j) // Armazenar o tempo de execução no vetor apropriado
            {
                case 0: 
                    timeBubble[i] = (int) measureExecutionTime([&]() 
                    { bubbleSort(&ptrCopy, iLength); });
                    break;
                case 1: 
                    timeBubbleOptimized[i] = (int) measureExecutionTime([&]() 
                    { optimizationBubbleSort(&ptrCopy, iLength); });
                    break;
                case 2: 
                    timeIsertion[i] = (int) measureExecutionTime([&]() 
                    { insertionSort(&ptrCopy); });
                    break;
                case 3: 
                    timeSelection[i] = (int) measureExecutionTime([&]() 
                    { selectionSort(&ptrCopy, iLength); });
                    break;
                case 4: 
                    timeSelectionOptimized[i] = (int) measureExecutionTime([&]() 
                    { optimizedSelectionSort(&ptrCopy, iLength); });
                    break;
                case 5: 
                    timeRadix[i] = (int) measureExecutionTime([&]() 
                    { radixSort(&ptrCopy); });
                    break;
            }

            deleteList(listCopy); // Limpar a lista após cada teste
        }

        deleteList(ptrList); // Limpar a lista após cada teste
    }

    // Salvar os tempos de execução em arquivos

    saveArray(timeBubble, iAmountOfTests, "bubble.txt");
    saveArray(timeBubbleOptimized, iAmountOfTests, "bubbleOptimized.txt");
    saveArray(timeIsertion, iAmountOfTests, "insertion.txt");
    saveArray(timeSelection, iAmountOfTests, "selection.txt");
    saveArray(timeSelectionOptimized, iAmountOfTests, "selectionOptimized.txt");
    saveArray(timeRadix, iAmountOfTests, "radix.txt");

    // ==============================================================
    // ================= Parte 2 - Busca em Árvores =================
    // ==============================================================

    // Preenchimento da árvore e da lista
    int iSize = 10000;
    int arriValues[iSize];
    
    for (int i = 0; i < iSize; i++)
    {
        arriValues[i] = i+1;
    }

    // Criação da árvore binária de busca e da lista duplamente encadeada
    Node* root = nullptr;
    DoublyLinkedList* list = nullptr;
    
    // Medição de tempo de criação da árvore e da lista
    double timeCreateTree = measureExecutionTime([&]() 
    { root = createTreeByArray(arriValues, iSize); } );
    
    double timeCreateList = measureExecutionTime([&]() 
    { list = createListByArray(arriValues, iSize); } );

    // Medição de tempo de busca
    double timeSearchDFS = measureExecutionTime([&]() 
    { for (int i = 0; i < iSize; i++) { searchDFS(root, i); } });

    double timeSearchBFS = measureExecutionTime([&]() 
    { for (int i = 0; i < iSize; i++) { searchBFS(root, i); } });

    double timeSearchList = measureExecutionTime([&]() 
    { for (int i = 0; i < iSize; i++) { searchList(list, i); } });


    cout << "Tempo médio de criação da árvore: " << timeCreateTree << " microssegundos" << endl;
    cout << "Tempo médio de criação da lista: " << timeCreateList << " microssegundos" << endl;
    cout << endl;
    cout << "Tempo médio de busca em profundidade: " << timeSearchDFS/iSize << " microssegundos" << endl;
    cout << "Tempo médio de busca em largura: " << timeSearchBFS/iSize << " microssegundos" << endl;    
    cout << "Tempo médio de busca na lista: " << timeSearchList/iSize << " microssegundos" << endl;

    // Limpeza de memória
    destroyTree(root);
    deleteList(list);

    return 0;
}

// =======================================================================

void saveArray(int iArr[], int iSize, string sFileName)
{
    ofstream file;
    file.open("times outputs/"+ sFileName);

    for (int i = 0; i < iSize; i++)
    {
        file << iArr[i] << endl;
    }

    file.close();
}
