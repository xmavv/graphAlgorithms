#include "iostream"
#include "stdio.h"
#include "iostream"
#include "time.h"
#include "cstdlib"
using namespace std;

#ifndef GRAPHALGORITHMS_UTILITIES_H
#define GRAPHALGORITHMS_UTILITIES_H


class Utilities {
    double PCFreq = 0.0;
    __int64 start = 0;
public:
    static int* split(string str, int size);
    void startCounter();
    double getCounter();
};


#endif //GRAPHALGORITHMS_UTILITIES_H
