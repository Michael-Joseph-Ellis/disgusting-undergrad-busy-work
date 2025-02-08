/*
 * Name: Michael Joseph Ellis
 * Date Submitted: Feb 11, 2025
 * Class Section: 001
 * Assignment Name: Stack-based Postfix Expression Calculator
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string
int calculatePostfixExpression(string expression[], int length) {
    if (length == 0) return 0;

    stack<int> operands;

    for (int i = 0; i < length; i++) {
        string token = expression[i];

        if (isdigit(token[0]) || (token.length() > 1 && isdigit(token[1]))) {
            // pushing operand to stack
            operands.push(stoi(token));
        } else {
            // ensure there are at least two operands for operation
            if (operands.size() < 2) return 0;

            int right = operands.top(); operands.pop();
            int left = operands.top(); operands.pop();
            int result;

            // perform operation based on token
            if (token == "+") {
                result = left + right;
            } else if (token == "-") {
                result = left - right;
            } else if (token == "*") {
                result = left * right;
            } else if (token == "/") {
                if (right == 0) return 0;
                result = left / right;
            } else if (token == "%") {
                if (right == 0) return 0;
                result = left % right;
            } else {
                return 0;
            }
            
            // push result back onto stack
            operands.push(result);
        }
    }
    
    // ensure only one result remains
    if (operands.size() != 1) return 0;
    
    return operands.top();
}