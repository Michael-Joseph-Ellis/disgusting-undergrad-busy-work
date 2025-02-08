#include <string>
#include <iostream>

using namespace std;

int calculatePostfixExpression(string expression[], int length);

int main()
{
    string exp[] = {"5"};

    //ASSERT_EQ(calculatePostfixExpression(exp,1), 5);
    if (calculatePostfixExpression(exp,1) != 5)
    {
        cout << "expected/correct value 5, actual value when testing " << calculatePostfixExpression(exp,1) << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}