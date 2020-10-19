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

        for (int i = 0; i < len; i++)
        {
            if (str[i] == '#')
                if (s.empty())
                    continue;
                else
                    s.pop();
            else
                s.push(str[i]);
        }

        if (s.empty())
        {
            cout << "NULL" << endl;
            continue;
        }

        // char output[100];
        string output;
        int output_len = 0;

        int i = 1;
        while (!s.empty())
        {
            output[i] = s.top();
            s.pop();
            output_len++;
            i++;
        }

        for (int i = 0; i < output_len; i++)
        {
            s.push(output[i + 1]);
        }

        while (!s.empty())
        {
            cout << s.top() << flush;
            s.pop();
        }
        cout << endl;
    }

    return 1;
}