#include "../headers/time_measure.h"

using namespace std;
using namespace chrono;

int measureExecutionTime(function<void()> func) {
    // Tempo de início
    auto timeStart = high_resolution_clock::now();
    
    func(); // Execução da função
    
    // Tempo de fim
    auto timeStop = high_resolution_clock::now();
    
    int timeDuration = duration_cast<microseconds>(timeStop - timeStart).count();
    return timeDuration;
}