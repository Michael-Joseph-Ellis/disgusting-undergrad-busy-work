#include "IntegerArrayQueue.h"

using namespace std;

int main()
{
    bool b;

    IntegerArrayQueue queue;

    queue.enqueue(2);
    queue.enqueue(4);
    queue.enqueue(8);
    queue.enqueue(16);
    queue.enqueue(32);
    queue.enqueue(64);
    queue.enqueue(128);
    queue.enqueue(256);
    queue.enqueue(512);
    b = queue.enqueue(1024);


    //ASSERT_EQ(b, false);
    if (b != false)
    {
        cout << "expected/correct value false, actual value when testing " << b << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}