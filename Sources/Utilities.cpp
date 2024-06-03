#include "../Headers/Utilities.h"
#include "iostream"
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
