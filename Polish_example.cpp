#include <iostream>
#include <stack>
#include <map>
#include <string>
using namespace std;

int main() {
    string exp = "2 * (5+y)-2";
    map<string, int> variables;
    variables["exp"] = 0;
    variables["y"] = 2;

    // Convert infix expression to postfix (reverse Polish) notation
    string postfix = "";
    stack<char> operators;
    for (char c : exp) {
        if (c == ' ') {
            // Ignore whitespace
        } else if (isdigit(c) || isalpha(c)) {
            // If it's a digit or a letter, add it to the output
            postfix += c;
        } else if (c == '(') {
            // Push opening parenthesis onto stack
            operators.push(c);
        } else if (c == ')') {
            // Pop operators from stack and add them to output until we find opening parenthesis
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop(); // Discard opening parenthesis
            }
        } else {
            // It's an operator
            while (!operators.empty() && operators.top() != '(' && (
                    (c == '+' || c == '-') && (operators.top() == '*' || operators.top() == '/') ||
                    (c == '*' || c == '/') && (operators.top() == '+' || operators.top() == '-')
                )) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    // Evaluate postfix expression
    stack<int> operands;
    for (char c : postfix) {
        if (isdigit(c)) {
            // If it's a digit, push it onto the stack
            operands.push(c - '0');
        } else if (isalpha(c)) {
            // If it's a letter, look up its value in the map and push it onto the stack
            operands.push(variables[string(1, c)]);
        } else {
            // If it's an operator, pop two operands from the stack and apply the operator
            int b = operands.top();
            operands.pop();
            int a = operands.top();
            operands.pop();
            switch (c) {
                case '+': operands.push(a + b); break;
                case '-': operands.push(a - b); break;
                case '*': operands.push(a * b); break;
                case '/': operands.push(a / b); break;
            }
        }
    }

    // The final result is at the top of the stack
    int result = operands.top();
    cout << result << endl;
    return 0;
}
