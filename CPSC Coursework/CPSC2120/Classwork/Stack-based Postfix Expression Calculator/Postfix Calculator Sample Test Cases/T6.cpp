#include <string>
#include <iostream>

using namespace std;

int calculatePostfixExpression(string expression[], int length);

int main()
{
    string exp[] = {"13", "8", "+", "5", "-", "3", "*", "2", "/"};

    //ASSERT_EQ(calculatePostfixExpression(exp,9), 24);
    if (calculatePostfixExpression(exp,9) != 24)
    {
        cout << "expected/correct value 24, actual value when testing " << calculatePostfixExpression(exp,9) << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}