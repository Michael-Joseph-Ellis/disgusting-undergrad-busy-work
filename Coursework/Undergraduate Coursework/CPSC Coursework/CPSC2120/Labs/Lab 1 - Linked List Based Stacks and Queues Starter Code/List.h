/*
 * Name: Michael Joseph Ellis
 * Date Submitted: Feb 3, 2025
 * Lab Section: 003
 * Assignment Name: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List
{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name)
  {
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializing this list's instance variables
template <class T>
List<T>::List() : start(nullptr), mySize(0)
{ 
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List()
{
  Node<T>* current = start;
  while (current != nullptr) { // while there are still nodes in the list to delete 
    Node<T>* next = current->next; // store the next node in a temp variable (seen throughout code)
    delete current; // delete the current node (seen throughout code)
    current = next; // move to the next node (seen throughout code)
  }
}

//Return the size of this list
template <class T>
int List<T>::size()
{
  return mySize; 
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty()
{
  return mySize == 0;
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value)
{
  Node<T>* newNode = new Node<T>(value); // create a new node with value
  newNode->next = start; 
  start = newNode;
  mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value)
{
  Node<T>* newNode = new Node<T>(value); 
  if (start == nullptr) { 
    start = newNode;
  } else { // if there are already nodes in the list
    Node<T>* current = start;
    while (current->next != nullptr) { // find the last node in the list 
      current = current->next; // move to the next node (seen throughout code)
    }
    current->next = newNode; // insert the new node at the end of the list (seen throughout code)
  }
  mySize++;
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j)
{
  if (j == 0) {
    insertStart(value); // insert the value at the start of the list
    return;
  }

  Node<T>* newNode = new Node<T>(value);
  Node<T>* current = start;
  for (int i = 0; i < j - 1; ++i) { // find the node before the position to insert the new node
    current = current->next;
  }
  newNode->next = current->next; 
  current->next = newNode; // insert the new node at the position j
  mySize++;
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart()
{
  if (start != nullptr) {
    Node<T>* temp = start; // store the start node in a temp variable
    start = start->next; // move the start pointer to the next node
    delete temp; 
    mySize--;
  }
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd()
{
  if (start == nullptr) {
    return;
  }

  if (start->next == nullptr) { // if there is only one node in the list
    delete start;
    start = nullptr; // set the start pointer to nullptr
  } else {
    Node<T>* current = start;
    while (current->next->next != nullptr) { // find the second to last node in the list
      current = current->next;
    } 
    delete current->next; // delete the last node in the list
    current->next = nullptr; // set the next pointer of the second to last node to nullptr
  }
  mySize--;
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j)
{
  if (j == 0) {
    removeStart(); // simple remove the first node in the list
    return;
  }

  Node<T>* current = start;
  for (int i = 0; i < j - 1; ++i) { // find the node before the node to remove
    current = current->next; 
  }
  Node<T>* temp = current->next; // store the node to remove in a temp variable
  current->next = temp->next; // set the next pointer of the node before the node to remove to the node after the node to remove
  delete temp;
  mySize--;
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst()
{
  if (start == nullptr) {
    return T();
  }
  return start->value; 
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast()
{
  if (start == nullptr) {
    return T(); // return the default constructed value if the list is empty
  }
  Node<T>* current = start;
  while (current->next != nullptr) { // find the last node in the list
    current = current->next;
  }
  return current->value;
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j)
{
  Node<T>* current = start;
  for (int i = 0; i < j; ++i) { // find the node at position j
    current = current->next;
  }
  return current->value;
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key)
{
  Node<T>* current = start;
  for (int i = 0; i < mySize; ++i) {
    if (current->value == key) { // if the value of the current node is equal to the key
      return i;
    }
    current = current->next;
  }
  return -1; 
}
