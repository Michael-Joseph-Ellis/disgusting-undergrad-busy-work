#include "IntegerArrayQueue.h"

using namespace std;

int main()
{
    int val;

    IntegerArrayQueue queue;

    queue.enqueue(2);
    queue.enqueue(4);
    queue.enqueue(8);
    queue.dequeue();
    queue.enqueue(16);
    queue.enqueue(32);
    queue.enqueue(64);
    queue.dequeue();
    queue.enqueue(128);
    queue.enqueue(256);
    queue.enqueue(512);
    val = queue.dequeue();


    //ASSERT_EQ(val, 8);
    if (val != 8)
    {
        cout << "expected/correct value for val 8, actual value when testing " << val << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}