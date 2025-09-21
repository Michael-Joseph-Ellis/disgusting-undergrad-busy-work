#include <string>
#include <iostream>

using namespace std;

int calculatePostfixExpression(string expression[], int length);

int main()
{
    string exp[] = {"21", "5", "-", "34", "2", "-", "*",
                    "3", "5", "+", "5", "11", "+", "*", "/"};

    //ASSERT_EQ(calculatePostfixExpression(exp,15), 4);
    if (calculatePostfixExpression(exp,15) != 4)
    {
        cout << "expected/correct value 4, actual value when testing " << calculatePostfixExpression(exp,15) << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}