// Sami Shibli
//  P

#include <stack>
#include <iostream>
using namespace std;

bool isOperator(char x);
int isOperand(char x);
string prefixToInfix(string s);
string infixToPrefix(string s);
int operatorValue(char n);

int main()
{
    string infix = "A*(B+C/D)";
    string prefix = "+*AB/CD";
    cout << "Prefix Notation: " << prefix << endl;
    cout << "Infix Notation: " << prefixToInfix(prefix) << endl;
    cout << endl;
    cout << "Infix Notation: " << infix << endl;
    cout << "Prefix Notation: " << infixToPrefix(infix) << endl;
    return 0;
}

bool isOperator(char x)
{
    return (!isalpha(x) && !isdigit(x));
}
int isOperand(char x)
{
    return (isalpha(x) || isdigit(x));
}
int operatorValue(char c)
{
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

string prefixToInfix(string s)
{
    stack<string> infix;
    int n = s.length();

    for (int i = n - 1; i >= 0; i--)
    {
        if (isOperator(s[i]))
        {
            string first = infix.top();
            infix.pop();
            string second = infix.top();
            infix.pop();
            string temp = '(' + first + s[i] + second + ')';
            infix.push(temp);
        }
        else
        {
            infix.push(string(1, s[i]));
        }
    }
    return infix.top();
}
string infixToPrefix(string s)
{
    stack<char> x;
    string reversedExpression = "";
    string infixExpression = "";

    // Reverse the infix equation first
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] == '(')
        {
            reversedExpression += ')';
        }
        else if (s[i] == ')')
        {
            reversedExpression += '(';
        }
        else
        {
            reversedExpression += s[i];
        }
    }
    int n = reversedExpression.length();
    for (int i = 0; i < n; i++)
    {
        char y = reversedExpression[i];
        // condition to handle if charachter is a letter
        if (isOperand(y))
        {
            infixExpression += y;
        }
        else if (isOperator(y))
        {
            if (x.empty() || (operatorValue(y) > operatorValue(x.top())))
                x.push(y);
            else
            {
                while (!x.empty() && (operatorValue(x.top()) >= operatorValue(y)))
                {
                    infixExpression += x.top();
                    x.pop();
                }
                x.push(y);
            }
        }
        else if (y == '(')
        {
            x.push(y);
        }
        else if (y == ')')
        {
            while (x.top() != '(')
            {
                infixExpression += x.top();
                x.pop();
            }
        }
    }
    while (!x.empty())
    {
        infixExpression += x.top();
        x.pop();
    }
    // result is in postfix notation, reverse the expression
    reverse(infixExpression.begin(), infixExpression.end());
    // remove the parentheses
    infixExpression.erase(remove(infixExpression.begin(), infixExpression.end(), '('), infixExpression.end());
    infixExpression.erase(remove(infixExpression.begin(), infixExpression.end(), ')'), infixExpression.end());
    return infixExpression;
}
