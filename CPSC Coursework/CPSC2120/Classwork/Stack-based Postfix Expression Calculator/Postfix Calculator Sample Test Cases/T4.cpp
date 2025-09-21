#include <string>
#include <iostream>

using namespace std;

int calculatePostfixExpression(string expression[], int length);

int main()
{
    string exp[] = {"22", "5", "/"};

    //ASSERT_EQ(calculatePostfixExpression(exp,3), 4);
    if (calculatePostfixExpression(exp,3) != 4)
    {
        cout << "expected/correct value 4, actual value when testing " << calculatePostfixExpression(exp,3) << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}