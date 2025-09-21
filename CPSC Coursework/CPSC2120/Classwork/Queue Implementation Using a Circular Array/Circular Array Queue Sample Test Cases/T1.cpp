#include "IntegerArrayQueue.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  int v[] = {1, 3, 6, 10, 15};
  int f = 0;
  int b = 4;

  IntegerArrayQueue queue;

  queue.enqueue(1);
  queue.enqueue(3);
  queue.enqueue(6);
  queue.enqueue(10);
  queue.enqueue(15);


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

  for (int i=0; i<5; i++)
  {
    buffer >> vals[i];
  }

  for (int i=5; i<10; i++)
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
    cout << "expected/correct value for front 0, actual value when testing " << front << ".\n";
    return 1;
  }
  //ASSERT_EQ(b, back);
  if (b != back)
  {
    cout << "expected/correct value for back 4, actual value when testing " << back << ".\n";
    return 1;
  }
  cout << "Passed" << endl;
  return 0;
}