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
            s.push(str[i]);
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