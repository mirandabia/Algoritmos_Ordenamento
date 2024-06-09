#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <functional>
#include <chrono>

int measureExecutionTime(std::function<void()> func);

#endif // TIME_MEASURE_H