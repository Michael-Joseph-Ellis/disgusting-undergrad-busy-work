#include "doublyLinkedSwap.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  int a[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233};

  Node * list = arrayToList(a, 13);
  Node * p = getNode(list, 11);

  int* preswap1_addr = &(p->value);
  int preswap1_val = p->value;
  int* preswap2_addr = &(p->next->value);
  int preswap2_val = p->next->value;

  swapWithNext(p);


  // This can be an ofstream as well or any other ostream
  stringstream buffer;

  // Save cout's buffer here
  streambuf *sbuf = cout.rdbuf();

  // Redirect cout to our stringstream buffer or any other ostream
  cout.rdbuf(buffer.rdbuf());

  printForwards(list);
  printBackwards(getTail(list));

  int fwd[13];
  int rev[13];
  int a_swapped[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 233, 144};
  int a_swappedRev[] = {144, 233, 89, 55, 34, 21, 13, 8, 5, 3, 2, 1, 1};

  for (int i=0; i<13; i++)
  {
    buffer >> fwd[i];
  }

  for (int i=0; i<13; i++)
  {
    buffer >> rev[i];
  }

  p = getNode(list, 11);

  int* postswap1_addr = &(p->value);
  int postswap1_val = p->value;
  int* postswap2_addr = &(p->next->value);
  int postswap2_val = p->next->value;

  // When done redirect cout to its old self
  cout.rdbuf(sbuf);

  //ASSERT_THAT(fwd, ElementsAreArray(a_swapped));
  for (int i=0; i<13; i++)
  {
    if (fwd[i] != a_swapped[i])
    {
      cout << "Mismatch at position " << i << ": expected/correct value " << a_swapped[i] << ", actual value when testing " << fwd[i] << ".\n";
      return 1;
    }
  }
  //ASSERT_THAT(rev, ElementsAreArray(a_swappedRev));
  for (int i=0; i<13; i++)
  {
    if (rev[i] != a_swappedRev[i])
    {
      cout << "Mismatch at position " << i << ": expected/correct value " << a_swappedRev[i] << ", actual value when testing " << rev[i] << ".\n";
      return 1;
    }
  }

  //ASSERT_EQ(preswap1_addr, postswap2_addr);
  if (preswap1_addr != postswap2_addr)
  {
    cout << "preswap1_addr: " << preswap1_addr << " and postswap2_addr " << postswap2_addr << " should be equal.\n";
    return 1;
  }
  //ASSERT_EQ(preswap2_addr, postswap1_addr);
  if (preswap2_addr != postswap1_addr)
  {
    cout << "preswap2_addr: " << preswap2_addr << " and postswap1_addr " << postswap1_addr << " should be equal.\n";
    return 1;
  }
  //ASSERT_EQ(preswap1_val, postswap2_val);
  if (preswap1_val != postswap2_val)
  {
    cout << "preswap1_val: " << preswap1_val << " and postswap2_val " << postswap2_val << " should be equal.\n";
    return 1;
  }
  //ASSERT_EQ(preswap2_val, postswap1_val);
  if (preswap2_val != postswap1_val)
  {
    cout << "preswap2_val: " << preswap2_val << " and postswap1_val " << postswap1_val << " should be equal.\n";
    return 1;
  }
  cout << "Passed" << endl;
  return 0;
}