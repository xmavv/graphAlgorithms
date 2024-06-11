#include "../Headers/PriorityQueue.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <queue>
#include <algorithm>

void PriorityQueue::swap(int i, int j) {
    swap(heap[i], heap[j]);
    swap(indices[heap[i]], indices[heap[j]]);
}

void PriorityQueue::heapifyDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(i, smallest);
        heapifyDown(smallest);
    }
}

void PriorityQueue::heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (i && heap[i] < heap[parent]) {
        swap(i, parent);
        heapifyUp(parent);
    }
}

PriorityQueue::PriorityQueue(int capacity) {
    this->capacity = capacity;
    size = 0;
    heap = new int[capacity];
    indices = new int[capacity];
    for (int i = 0; i < capacity; ++i)
        indices[i] = -1;
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
    delete[] indices;
}

void PriorityQueue::push(int element) {
    if (indices[element] != -1)
        return;

    heap[size] = element;
    indices[element] = size;
    heapifyUp(size);
    size++;
}

void PriorityQueue::pop() {
    indices[heap[0]] = -1;
    heap[0] = heap[--size];
    heapifyDown(0);
}

int PriorityQueue::top() {
    return heap[0];
}

bool PriorityQueue::empty() {
    return size == 0;
}

void PriorityQueue::decreaseKey(int element, int new_value) {
    int i = indices[element];
    heap[i] = new_value;
    heapifyUp(i);
}