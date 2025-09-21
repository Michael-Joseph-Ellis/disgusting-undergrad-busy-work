#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;

// Helper function: checks if two words differ by exactly one character
bool oneLetterDiff(const string &a, const string &b) {
    int diff = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) ++diff;
        if (diff > 1) return false;
    }
    return diff == 1;
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
    unordered_set<string> wordSet;
    ifstream file("wordlist05.txt");
    string word;

    // Load all valid 5-letter words into a set
    while (file >> word) {
        if (word.length() == 5)
            wordSet.insert(word);
    }
    file.close();

    // If either start or target word is not in the list, there's no path
    if (wordSet.find(s) == wordSet.end() || wordSet.find(t) == wordSet.end()) {
        steps = 0;
        p.clear();
        return;
    }

    // Build adjacency list: connect words that differ by one letter
    unordered_map<string, vector<string>> graph;
    for (const string &w : wordSet) {
        for (int i = 0; i < w.size(); ++i) {
            string temp = w;
            for (char c = 'a'; c <= 'z'; ++c) {
                temp[i] = c;
                if (temp != w && wordSet.find(temp) != wordSet.end()) {
                    graph[w].push_back(temp);
                }
            }
        }
    }

    // Perform BFS to find the shortest path
    unordered_map<string, string> pred; // predecessor map
    unordered_map<string, int> dist;    // distance from source
    queue<string> q;

    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        string curr = q.front(); q.pop();
        if (curr == t) break;

        for (const string &neighbor : graph[curr]) {
            if (dist.find(neighbor) == dist.end()) {
                dist[neighbor] = dist[curr] + 1;
                pred[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    // If target wasn't reached, there's no valid ladder
    if (dist.find(t) == dist.end()) {
        steps = 0;
        p.clear();
        return;
    }

    // Reconstruct the path from target to source
    steps = dist[t];
    string curr = t;
    while (curr != s) {
        p.push_back(curr);
        curr = pred[curr];
    }
    p.push_back(s);
    reverse(p.begin(), p.end());
}
//modified the main a little bit 
// int main() {
//     string startWord, targetWord;
//     int steps;
//     vector<string> path;

//     cout << "Enter the start word (5 letters): ";
//     cin >> startWord;
//     cout << "Enter the target word (5 letters): ";
//     cin >> targetWord;

//     wordLadder(startWord, targetWord, steps, path);

//     if (steps == 0) {
//         cout << "No valid ladder found." << endl;
//     } else {
//         cout << "Steps: " << steps << endl;
//         cout << "Path: ";
//         for (const string &word : path) {
//             cout << word << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }
