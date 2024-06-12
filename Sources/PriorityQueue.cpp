#include <iostream>
#include <climits>
#include "../Headers/PriorityQueue.h"
using namespace std;

PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0) {
    heap = new pair<int, int>[capacity];
    indices = new int[capacity];
    fill(indices, indices + capacity, -1);
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
    delete[] indices;
}

void PriorityQueue::swap(int i, int j) {
    std::swap(heap[i], heap[j]);
    std::swap(indices[heap[i].second], indices[heap[j].second]);
}

void PriorityQueue::heapifyDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < size && heap[left].first < heap[smallest].first)
        smallest = left;
    if (right < size && heap[right].first < heap[smallest].first)
        smallest = right;

    if (smallest != i) {
        swap(i, smallest);
        heapifyDown(smallest);
    }
}

void PriorityQueue::heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (i && heap[i].first < heap[parent].first) {
        swap(i, parent);
        heapifyUp(parent);
    }
}

void PriorityQueue::push(int element) {
    heap[size] = {INT_MAX, element};
    indices[element] = size;
    size++;
    heapifyUp(size - 1);
}

void PriorityQueue::pop() {
    indices[heap[0].second] = -1;
    heap[0] = heap[--size];
    if (size > 0)
        heapifyDown(0);
}

int PriorityQueue::top() {
    return heap[0].second;
}

bool PriorityQueue::empty() const {
    return size == 0;
}

void PriorityQueue::decreaseKey(int element, int new_value) {
    int i = indices[element];
    heap[i].first = new_value;
    heapifyUp(i);
}

int PriorityQueue::extractMin() {
    int minElement = top();
    pop();
    return minElement;
}