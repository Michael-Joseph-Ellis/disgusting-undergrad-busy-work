/*
 * Name: Michael Joseph Ellis
 * Date Submitted: 4/21/2025
 * Lab Section: 004 
 * Assignment Name: Water Jugs
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph() 
{
  int maxA = 3;
  int maxB = 4;

  for (int a = 0; a <= maxA; ++a) {
      for (int b = 0; b <= maxB; ++b) {
          state current = make_pair(a, b);
          
          // Fill A
          state next = make_pair(maxA, b);
          nbrs[current].push_back(next);
          edge_label[{current, next}] = "Fill A";

          // Fill B
          next = make_pair(a, maxB);
          nbrs[current].push_back(next);
          edge_label[{current, next}] = "Fill B";

          // Empty A
          next = make_pair(0, b);
          nbrs[current].push_back(next);
          edge_label[{current, next}] = "Empty A";

          // Empty B
          next = make_pair(a, 0);
          nbrs[current].push_back(next);
          edge_label[{current, next}] = "Empty B";

          // Pour A -> B
          int pourAtoB = min(a, maxB - b);
          next = make_pair(a - pourAtoB, b + pourAtoB);
          nbrs[current].push_back(next);
          edge_label[{current, next}] = "Pour A->B";

          // Pour B -> A
          int pourBtoA = min(b, maxA - a);
          next = make_pair(a + pourBtoA, b - pourBtoA);
          nbrs[current].push_back(next);
          edge_label[{current, next}] = "Pour B->A";
      }
  }

  // Add edges from goal states (a + b == 5) to virtual goal node (-1, -1)
  for (int a = 0; a <= maxA; ++a) {
      for (int b = 0; b <= maxB; ++b) {
          if (a + b == 5) {
              nbrs[{a, b}].push_back({-1, -1});
              edge_label[{{a, b}, {-1, -1}}] = "Goal Reached";
          }
      }
  }
}

// int main(void)
// {
//   build_graph();

//   state start = make_pair(0,0);
  
//   for (int i=0; i<5; i++)
//     nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
//   search (start);
//   if (visited[make_pair(-1,-1)]) 
//     print_path (start, pred[make_pair(-1,-1)]);
//   else
//     cout << "No path!\n";
  
//   return 0;
// }
