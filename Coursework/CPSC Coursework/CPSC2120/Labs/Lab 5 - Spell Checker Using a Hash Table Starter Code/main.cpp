/*
 * Name: Michael Joseph Ellis
 * Date Submitted: 3/3/2005
 * Lab Section: 004 
 * Assignment Name: Spell Checker Using a Hash Table
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
//  int main()
//  {
//      Stringset wordlist;
//      testStringset(wordlist);
//      return 0;
//  }
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 void loadStringset(Stringset& words, string filename) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.insert(word);
    }
    file.close();
}

vector<string> spellcheck(const Stringset& words, string word) {
    vector<string> alternatives;
    for (size_t i = 0; i < word.length(); ++i) { // for each character in word
        string modified = word;
        for (char c = 'a'; c <= 'z'; ++c) { // then for each letter in the alphabet
            if (c != word[i]) { // if the letter is not the same as the character in the word
                modified[i] = c;
                if (words.find(modified)) { // if the modified word is in the dictionary
                    alternatives.push_back(modified);
                }
            }
        }
    }
    return alternatives;
}