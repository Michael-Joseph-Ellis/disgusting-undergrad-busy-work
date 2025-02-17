/*
 * Name: Michael Joseph Ellis 
 * Date Submitted: 2/24/2025
 * Lab Section: 004
 * Assignment Name: Searching and Sorting
 */

 #pragma once

 #include <vector>
 #include <algorithm>
 
 // Linear Search - Iterates through the vector to find the target.
 template <class T>
 int linearSearch(const std::vector<T>& data, T target) {
     for (size_t i = 0; i < data.size(); i++){
         if (data[i] == target) {
             return i;
         }
     }
     return -1;
 }
 
 // Binary Search - Requires sorted input and uses divide-and-conquer.
 template <class T>
 int binarySearch(const std::vector<T>& data, T target) {
     int left = 0, right = data.size() - 1;
     
     while (left <= right) {
         int mid = left + (right - left) / 2;
         
         if (data[mid] == target) {
             return mid;  // Found the target
         }
         else if (data[mid] < target) {
             left = mid + 1;  // Search right half
         }
         else {
             right = mid - 1; // Search left half
         }
     }
     return -1;  // Target not found
 }
 