#include <iostream>
#include <string>
#include <stack>
using namespace std;

#define space ' '

int getPriority(char a)
{
    switch (a)
    {
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
    case ')':
        return 0;
    default:
        return 0;
    }
}

bool isNumber(char temp)
{
    return (temp != '+' && temp != '-' && temp != '*' && temp != '/' && temp != '(' && temp != ')');
}

// 逆波兰式只要一个运算符栈就可以，数字直接输出
void reservePolish(string expression)
{
    stack<char> operatorStack; // 运算符栈
    char ch;

    bool theLastCharactorIsNumber = false;
    bool theFirst = true;
    for (int i = 0; i < expression.size(); i++)
    {
        char ch = expression[i];

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (operatorStack.empty() || operatorStack.top() == '(')
                operatorStack.push(ch);
            else
            {
                // 逆波兰式这里有=，而波兰式没有=
                while (getPriority(operatorStack.top()) >= getPriority(ch))
                {
                    if (!theFirst)
                        cout << space;

                    cout << operatorStack.top();
                    operatorStack.pop();

                    if (operatorStack.empty())
                        break;
                }
                operatorStack.push(ch);
            }
            theLastCharactorIsNumber = false;
            theFirst = false;
        }
        else if (ch == '(') // 这个不能做first
        {
            operatorStack.push(ch);
            theLastCharactorIsNumber = false;
        }
        else if (ch == ')')
        {
            while (!operatorStack.empty())
            {
                if (operatorStack.top() == '(')
                {
                    operatorStack.pop();
                    break;
                }
                else
                {
                    if (!theFirst)
                        cout << space;

                    cout << operatorStack.top();
                    operatorStack.pop();
                }
            }
            theLastCharactorIsNumber = false;
            theFirst = false;
        }
        // 数
        else
        {
            if (theLastCharactorIsNumber || theFirst)
                cout << ch << flush;
            else
                cout << space << ch << flush;

            theLastCharactorIsNumber = true;
            theFirst = false;
        }
        }
    while (!operatorStack.empty())
    {
        if (!theFirst)
            cout << space;

        cout << operatorStack.top();
        operatorStack.pop();
    }
    cout << endl;
}

// 波兰式：把)和(倒换，然后从后往前读,>=变成>，最后逆序输出
void polish(string expression)
{
    stack<char> operatorStack; // 运算符栈
    stack<char> output;
    char ch;

    bool theLastCharactorIsNumber = false;

    // 从后往前
    for (int i = expression.size() - 1; i >= 0; i--)
    {
        char ch = expression[i];

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (operatorStack.empty() || operatorStack.top() == ')')
                operatorStack.push(ch);
            else
            {
                // 逆波兰式这里有=，而波兰式没有=
                while (getPriority(operatorStack.top()) > getPriority(ch))
                {
                    // cout << operatorStack.top() << " ";
                    output.push(space);
                    output.push(operatorStack.top());
                    operatorStack.pop();

                    if (operatorStack.empty())
                        break;
                }
                operatorStack.push(ch);
            }
        }
        else if (ch == ')')
        {
            operatorStack.push(ch);
        }
        else if (ch == '(')
        {
            while (!operatorStack.empty())
            {
                if (operatorStack.top() == ')')
                {
                    operatorStack.pop();
                    break;
                }
                else
                {
                    // cout << operatorStack.top() << " ";
                    output.push(space);
                    output.push(operatorStack.top());
                    operatorStack.pop();
                }
            }
        }
        // 数
        else
        {
            // 从后往前读，而前一个读取的是数字，所以要
            if (!theLastCharactorIsNumber)
            {
                output.push(space);
            }

            output.push(ch);
        }
        theLastCharactorIsNumber = isNumber(ch);
    }
    while (!operatorStack.empty())
    {
        // cout << operatorStack.top() << " ";
        output.push(space);
        output.push(operatorStack.top());
        operatorStack.pop();
    }

    // 倒叙输出
    while (!output.empty())
    {
        char temp = output.top();

        // 判断栈是否只剩最后一个空格（不输出最后一个空格）
        if (temp == space)
        {
            output.pop();
            if (output.empty())
            {
                cout << endl;
                return;
            }
            else
            {
                cout << space << flush;
                continue;
            }
        }
        cout << temp << flush;
        output.pop();
    }
    cout << endl;
}

int main()
{
    int tryTimes;
    cin >> tryTimes;

    for (int i = 0; i < tryTimes; i++)
    {
        string expression;
        cin >> expression;

        polish(expression);
        reservePolish(expression);

        if (i != tryTimes - 1)
        {
            cout << endl;
        }
    }
    return 0;
}