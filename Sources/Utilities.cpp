#include "../Headers/Utilities.h"
#include "iostream"
#include "windows.h"
using namespace std;

int *Utilities::split(string str, int size) {
    string word;
    int i = 0;
    auto* array = new int [size];

    for (auto x : str) {
        if (x == ' ') {
            array[i] = stoi(word);
            i++;
            word = "";
        } else {
            word = word + x;
        }
    }
    array[i] = stoi(word);

    return array;
}

void Utilities::startCounter() {
    PCFreq = 0.0;
    start = 0;

    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    start = li.QuadPart;
}

double Utilities::getCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-start)/PCFreq;
}