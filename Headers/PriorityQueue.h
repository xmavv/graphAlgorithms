#ifndef GRAPHALGORITHMS_PRIORITYQUEUE_H
#define GRAPHALGORITHMS_PRIORITYQUEUE_H
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <queue>
#include <algorithm>


class PriorityQueue {
public:
    PriorityQueue(int capacity);
    ~PriorityQueue();
    void push(int element);
    void pop();
    int top();
    bool empty() const;
    void decreaseKey(int element, int new_value);
    int extractMin();

private:
    void swap(int i, int j);
    void heapifyDown(int i);
    void heapifyUp(int i);

    std::pair<int, int>* heap;  // Pair to store (distance, vertex)
    int* indices;
    int capacity;
    int size;
};


#endif //GRAPHALGORITHMS_PRIORITYQUEUE_H
