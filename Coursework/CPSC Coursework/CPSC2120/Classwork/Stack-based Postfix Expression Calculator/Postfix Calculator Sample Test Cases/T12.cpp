#include <string>
#include <iostream>

using namespace std;

int calculatePostfixExpression(string expression[], int length);

int main()
{
    string exp[] = {"1", "2", "3", "+"};

    //ASSERT_EQ(calculatePostfixExpression(exp,4), 0);
    if (calculatePostfixExpression(exp,4) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp,4) << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}