#include "doublyLinkedSwap.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  int a[] = {2, 3, 5, 7, 11, 13, 17, 19};

  Node * list = arrayToList(a, 8);
  Node * p = getNode(list, 8);

  int* preswap1_addr = &(getTail(list)->prev->value);
  int preswap1_val = getTail(list)->prev->value;

  swapWithNext(p);


  // This can be an ofstream as well or any other ostream
  stringstream buffer;

  // Save cout's buffer here
  streambuf *sbuf = cout.rdbuf();

  // Redirect cout to our stringstream buffer or any other ostream
  cout.rdbuf(buffer.rdbuf());

  printForwards(list);
  printBackwards(getTail(list));

  int fwd[8];
  int rev[8];
  int a_swapped[] = {2, 3, 5, 7, 11, 13, 17, 19};
  int a_swappedRev[] = {19, 17, 13, 11, 7, 5, 3, 2};

  for (int i=0; i<8; i++)
  {
    buffer >> fwd[i];
  }

  for (int i=0; i<8; i++)
  {
    buffer >> rev[i];
  }

  p = getNode(list, 8);

  int* postswap1_addr = &(getTail(list)->prev->value);
  int postswap1_val = getTail(list)->prev->value;

  // When done redirect cout to its old self
  cout.rdbuf(sbuf);

  //ASSERT_THAT(fwd, ElementsAreArray(a_swapped));
  for (int i=0; i<8; i++)
  {
    if (fwd[i] != a_swapped[i])
    {
      cout << "Mismatch at position " << i << ": expected/correct value " << a_swapped[i] << ", actual value when testing " << fwd[i] << ".\n";
      return 1;
    }
  }
  //ASSERT_THAT(rev, ElementsAreArray(a_swappedRev));
  for (int i=0; i<8; i++)
  {
    if (rev[i] != a_swappedRev[i])
    {
      cout << "Mismatch at position " << i << ": expected/correct value " << a_swappedRev[i] << ", actual value when testing " << rev[i] << ".\n";
      return 1;
    }
  }

  //ASSERT_EQ(preswap1_addr, postswap1_addr);
  if (preswap1_addr != postswap1_addr)
  {
    cout << "preswap1_addr: " << preswap1_addr << " and postswap1_addr " << postswap1_addr << " should be equal.\n";
    return 1;
  }
  //ASSERT_EQ(preswap1_val, postswap1_val);
  if (preswap1_val != postswap1_val)
  {
    cout << "preswap1_val: " << preswap1_val << " and postswap1_val " << postswap1_val << " should be equal.\n";
    return 1;
  }
  cout << "Passed" << endl;
  return 0;
}