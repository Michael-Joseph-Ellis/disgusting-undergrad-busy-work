/*
 * Name: Michael Joseph Ellis
 * Date Submitted: 3/13/2025
 * Assignment Name: Single-Word Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

int main()
{
    vector<string> words;
    vector<string> anagrams;
    string inputWord;
    words=loadWordlist("wordlist.txt");
    cout << "Find single-word anagrams for the following word: ";
    cin >> inputWord;
    anagrams = anagram(inputWord, words);
    for (int i=0; i<anagrams.size(); i++)
    {
        cout << anagrams[i] << endl;
    }
    return 0;
}

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(std::getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Implement this function
vector<string> anagram(string word, vector<string> wordlist)
{
    unordered_map<string, vector<string>> anagram_map;
    
    // Helper function to create a sorted key from a word
    auto getSortedKey = [](const string& s) {
        string key = s;
        sort(key.begin(), key.end());
        return key;
    };
    
    // Populate the unordered_map with words from the wordlist
    for (const string& w : wordlist)
    {
        string sorted_key = getSortedKey(w);
        anagram_map[sorted_key].push_back(w);
    }
    
    // Get the anagrams of the input word
    string input_key = getSortedKey(word);
    if (anagram_map.find(input_key) != anagram_map.end())
    {
        return anagram_map[input_key];
    }
    else
    {
        return {}; // Return empty vector if no anagrams are found
    }
}