#include "minHeap.h"
#include <stdexcept> // for exception handling will remove this later probably

// Helper function to move a node up to maintain min-heap property
void minHeap::siftUp(int pos) {
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (heap[pos] < heap[parent]) {
            swap(heap[pos], heap[parent]);
            pos = parent;
        } else {
            break;
        }
    }
}

// Helper function to move a node down to maintain min-heap property
void minHeap::siftDown(int pos) {
    int size = heap.size();
    while (2 * pos + 1 < size) {
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        int smallest = left;

        if (right < size && heap[right] < heap[left]) {
            smallest = right;
        }

        if (heap[pos] > heap[smallest]) {
            swap(heap[pos], heap[smallest]);
            pos = smallest;
        } else {
            break;
        }
    }
}

// Constructor that builds the heap from a vector using bottom-up heapify
minHeap::minHeap(vector<int> data) {
    heap = data;
    int size = heap.size();
    for (int i = (size / 2) - 1; i >= 0; i--) {
        siftDown(i);
    }
}

// Insert value into the heap
void minHeap::insert(int value) {
    heap.push_back(value);
    siftUp(heap.size() - 1);
}

// Remove and return the minimum element (root) from the heap
int minHeap::removeMin() {
    if (heap.empty()) {
        throw out_of_range("Heap is empty");
    }

    int minVal = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        siftDown(0);
    }
    return minVal;
}
