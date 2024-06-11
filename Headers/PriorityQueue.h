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
    int* heap;
    int* indices;
    int size;
    int capacity;
    void swap(int i, int j);
    void heapifyDown(int i);
    void heapifyUp(int i);
public:
    explicit PriorityQueue(int capacity);
    ~PriorityQueue();
    void push(int element);
    void pop();
    int top();
    bool empty();
    void decreaseKey(int element, int new_value);
};


#endif //GRAPHALGORITHMS_PRIORITYQUEUE_H
