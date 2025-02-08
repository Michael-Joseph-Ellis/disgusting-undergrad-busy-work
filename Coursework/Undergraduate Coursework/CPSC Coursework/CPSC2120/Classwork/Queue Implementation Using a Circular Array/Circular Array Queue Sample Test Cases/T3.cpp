#include "IntegerArrayQueue.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  int v[] = {64, 81, 100, 121, 144};
  int f = 7;
  int b = 1;

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
  queue.dequeue();
  queue.enqueue(81);
  queue.enqueue(100);
  queue.enqueue(121);
  queue.dequeue();
  queue.dequeue();
  queue.dequeue();
  queue.enqueue(144);
  queue.dequeue();


  // This can be an ofstream as well or any other ostream
  stringstream buffer;

  // Save cout's buffer here
  streambuf *sbuf = cout.rdbuf();

  // Redirect cout to our stringstream buffer or any other ostream
  cout.rdbuf(buffer.rdbuf());

  queue.printArrayQueue();

  int vals[5];
  int front, back;
  string skip;

  for (int i=0; i<2; i++)
  {
    buffer >> vals[i+3];
  }

  for (int i=2; i<7; i++)
  {
    buffer >> skip;
  }

  for (int i=7; i<10; i++)
  {
    buffer >> vals[i-7];
  }

  buffer >> skip;
  buffer >> front;

  buffer >> skip;
  buffer >> back;

  // When done redirect cout to its old self
  cout.rdbuf(sbuf);

  //ASSERT_THAT(v, ElementsAreArray(vals));
  for (int i=0; i<5; i++)
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
    cout << "expected/correct value for front 7, actual value when testing " << front << ".\n";
    return 1;
  }
  //ASSERT_EQ(b, back);
  if (b != back)
  {
    cout << "expected/correct value for back 1, actual value when testing " << back << ".\n";
    return 1;
  }
  cout << "Passed" << endl;
  return 0;
}