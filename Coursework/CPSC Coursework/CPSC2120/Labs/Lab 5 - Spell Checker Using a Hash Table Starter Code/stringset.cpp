/*
 * Name: Michael Joseph Ellis
 * Date Submitted: 3/3/2005
 * Lab Section: 004 
 * Assignment Name: Spell Checker Using a Hash Table
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word) { 
    size_t h = hash<string>{}(word) % size; // hash function in every function needed to be implemented
    for (const auto& w : table[h]) {
        if (w == word) return;
    }
    table[h].push_back(word); 
    num_elems++;
    if (num_elems == size) expandTable(); // expand table if full
}

bool Stringset::find(string word) const { 
    size_t h = hash<string>{}(word) % size; 
    for (const auto& w : table[h]) {
        if (w == word) return true;
    }
    return false;
}

void Stringset::remove(string word) {
    size_t h = hash<string>{}(word) % size;
    table[h].remove(word);
    num_elems--;
}

void Stringset::expandTable() { // expand table by 2x
    size_t newSize = size * 2; 
    vector<list<string>> newTable(newSize); // create new table
    for (const auto& bucket : table) { // 
        for (const auto& word : bucket) {
            size_t h = hash<string>{}(word) % newSize;
            newTable[h].push_back(word);
        }
    }
    table = move(newTable);
    size = newSize;
}