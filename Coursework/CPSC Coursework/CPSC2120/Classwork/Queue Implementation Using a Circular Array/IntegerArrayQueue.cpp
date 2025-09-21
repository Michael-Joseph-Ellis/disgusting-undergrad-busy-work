/*
 * Name: Michael Joseph Ellis
 * Date Submitted: Feb 11, 2025
 * Class Section: 001
 * Assignment Name: Queue Implementation Using a Circular Array
 */

#include "IntegerArrayQueue.h"

// enqueue function: adds an element to the queue if it is not full
bool IntegerArrayQueue::enqueue(int value)
{
    if ((back + 2) % size == front) {
        return false; //queue is full, cannot enqueue
    }
    
    // move back index forward in a circular manner
    back = (back + 1) % size;
    array[back] = value;
    
    return true;
}

// dequeue function: removes and returns the front element if the queue is not empty
int IntegerArrayQueue::dequeue()
{
    if ((back + 1) % size == front) {
        return 0; 
    }
    
    // retrieve the front value
    int value = array[front];
    
    // move front index forward in a circular manner
    front = (front + 1) % size;
    
    return value;
}