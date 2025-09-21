/*
 * Name: Michael Joseph Ellis 
 * Date Submitted: 2/24/2025
 * Lab Section: 004
 * Assignment Name: Searching and Sorting
 */

 #pragma once

 #include <vector>
 #include <cstdlib>  // use for rand()
 
 // Merge function for merge sort
 template <class T>
 void merge(std::vector<T>& lst, std::vector<T>& left, std::vector<T>& right) {
     size_t i = 0, j = 0, k = 0;

    // Merge the two halves into a sorted data
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) { 
            lst[k++] = left[i++]; 
        } else {
            lst[k++] = right[j++];
        }
    }
    while (i < left.size()) {
        lst[k++] = left[i++];
    }
    while (j < right.size()) { 
        lst[k++] = right[j++];
    }
}

// Merge Sort - Recursively divides and merges sorted halves
template <class T> 
std::vector<T> mergeSort(std::vector<T> lst) {
    // Base case: list is already sorted
    if (lst.size() <= 1) { 
        return lst;
    } 
    
    // dvide the list into two halves
    size_t mid = lst.size() / 2;
    std::vector<T> left(lst.begin(), lst.begin() + mid); // [begin, mid)
    std::vector<T> right(lst.begin() + mid, lst.end()); // [mid, end)

    // Recursively sort each half
    left = mergeSort(left); 
    right = mergeSort(right);
    
    merge(lst, left, right);
    return lst;
}

// Partition function for quicksort
template <class T>
// Returns the index of the pivot element
int partition(std::vector<T>& lst, int low, int high) { 
    int pivotIndex = low + rand() % (high - low + 1); 
    T pivot = lst[pivotIndex];
    std::swap(lst[pivotIndex], lst[high]); // Move pivot to end
    int i = low;

    for (int j = low; j < high; j++) {
        if (lst[j] < pivot) {
            std::swap(lst[i], lst[j]);
            i++;
        }
    }
    std::swap(lst[i], lst[high]); // Place pivot in correct position
    return i;
}

// QuickSort helper function
template <class T>
void quickSortHelper(std::vector<T>& lst, int low, int high) {
    if (low < high) { // Base case: list is already sorted
        int pivotIndex = partition(lst, low, high);
        quickSortHelper(lst, low, pivotIndex - 1);
        quickSortHelper(lst, pivotIndex + 1, high);
    }
}

// QuickSort - Uses partitioning with a random pivot
template <class T>
std::vector<T> quickSort(std::vector<T> lst) {
    quickSortHelper(lst, 0, lst.size() - 1);
    return lst;
}
