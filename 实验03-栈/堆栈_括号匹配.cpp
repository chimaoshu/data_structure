#include <stack>
#include <iostream>
using namespace std;

int main()
{
    stack<char> s;
    string str;
    int len;

    int try_times;
    scanf("%d", &try_times);

    for (int j = 0; j < try_times; j++)
    {
        cin >> str;
        len = str.length();
        bool ok = true;

        for (int i = 0; i < len; i++)
        {
            switch (str[i])
            {
            case '(':
                s.push('(');
                break;
            case ')':
                if (s.top() == '(')
                {
                    s.pop();
                }
                else
                {
                    ok = false;
                }
                break;
            case '[':
                s.push('[');
                break;
            case ']':
                if (s.top() == '[')
                {
                    s.pop();
                }
                else
                {
                    ok = false;
                }
                break;
            case '{':
                s.push('{');
                break;
            case '}':
                if (s.top() == '}')
                {
                    s.pop();
                }
                else
                {
                    ok = false;
                }
                break;
            default:
                break;
            }
            if (!ok)
            {
                break;
            }
        }
        if (!s.empty())
        {
            ok = false;
        }

        if (ok)
        {
            cout << "ok" << endl;
        }
        else
        {
            cout << "error" << endl;
        }
    }
    return 1;
}