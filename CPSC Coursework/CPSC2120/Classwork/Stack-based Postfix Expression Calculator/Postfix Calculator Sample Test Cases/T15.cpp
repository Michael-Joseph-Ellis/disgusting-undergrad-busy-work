#include <string>
#include <iostream>

using namespace std;

int calculatePostfixExpression(string expression[], int length);

int main()
{
    string exp1[] = {"+"};
    string exp2[] = {"-"};
    string exp3[] = {"*"};
    string exp4[] = {"/"};
    string exp5[] = {"%"};
    string exp1a[] = {"1", "+"};
    string exp2a[] = {"1", "-"};
    string exp3a[] = {"1", "*"};
    string exp4a[] = {"1", "/"};
    string exp5a[] = {"1", "%"};

    //ASSERT_EQ(calculatePostfixExpression(exp1,1), 0);
    if (calculatePostfixExpression(exp1,1) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp1,1) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp2,1), 0);
    if (calculatePostfixExpression(exp2,1) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp2,1) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp3,1), 0);
    if (calculatePostfixExpression(exp3,1) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp3,1) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp4,1), 0);
    if (calculatePostfixExpression(exp4,1) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp4,1) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp5,1), 0);
    if (calculatePostfixExpression(exp5,1) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp5,1) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp1a,2), 0);
    if (calculatePostfixExpression(exp1a,2) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp1a,2) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp2a,2), 0);
    if (calculatePostfixExpression(exp2a,2) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp2a,2) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp3a,2), 0);
    if (calculatePostfixExpression(exp3a,2) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp3a,2) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp4a,2), 0);
    if (calculatePostfixExpression(exp4a,2) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp4a,2) << ".\n";
        return 1;
    }
    //ASSERT_EQ(calculatePostfixExpression(exp5a,2), 0);
    if (calculatePostfixExpression(exp5a,2) != 0)
    {
        cout << "expected/correct value 0, actual value when testing " << calculatePostfixExpression(exp5a,2) << ".\n";
        return 1;
    }
    cout << "Passed" << endl;
    return 0;
}