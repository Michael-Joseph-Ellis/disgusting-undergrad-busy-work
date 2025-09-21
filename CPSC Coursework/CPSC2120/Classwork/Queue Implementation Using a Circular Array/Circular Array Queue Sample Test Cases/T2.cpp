#include "IntegerArrayQueue.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  int v[] = {9, 16, 25, 36, 49, 64};
  int f = 2;
  int b = 7;

  IntegerArrayQueue queue;

  queue.enqueue(1);
  queue.enqueue(4);
  queue.enqueue(9);
  queue.enqueue(16);
  queue.dequeue();
  queue.enqueue(25);
  queue.enqueue(36);
  queue.enqueue(49);
  queue.enqueue(64);
  queue.dequeue();


  // This can be an ofstream as well or any other ostream
  stringstream buffer;

  // Save cout's buffer here
  streambuf *sbuf = cout.rdbuf();

  // Redirect cout to our stringstream buffer or any other ostream
  cout.rdbuf(buffer.rdbuf());

  queue.printArrayQueue();

  int vals[6];
  int front, back;
  string skip;

  for (int i=0; i<2; i++)
  {
    buffer >> skip;
  }

  for (int i=2; i<8; i++)
  {
    buffer >> vals[i-2];
  }

  for (int i=8; i<10; i++)
  {
    buffer >> skip;
  }

  buffer >> skip;
  buffer >> front;

  buffer >> skip;
  buffer >> back;

  // When done redirect cout to its old self
  cout.rdbuf(sbuf);

  //ASSERT_THAT(v, ElementsAreArray(vals));
  for (int i=0; i<6; i++)
  {
    if (v[i] != vals[i])
    {
      cout << "Mismatch at position " << i << ": expected/correct value " << v[i] << ", actual value when testing " << vals[i] << ".\n";
      return 1;
    }
  }
  //ASSERT_EQ(f, front);
  if (f != front)
  {
    cout << "expected/correct value for front 2, actual value when testing " << front << ".\n";
    return 1;
  }
  //ASSERT_EQ(b, back);
  if (b != back)
  {
    cout << "expected/correct value for back 7, actual value when testing " << back << ".\n";
    return 1;
  }
  cout << "Passed" << endl;
  return 0;
}