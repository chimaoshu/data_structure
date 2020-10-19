#include <queue>
#include <string>
#include <iostream>
using namespace std;

void run()
{
    queue<int> a, b;
    int customerNumber;
    cin >> customerNumber;
    int userInput;

    for (int i = 0; i < customerNumber; i++)
    {
        cin >> userInput;

        // 偶数
        if (userInput % 2 == 0)
        {
            b.push(userInput);
            continue;
        }
        a.push(userInput);
    }

    int index = 0;
    bool firstOutput = true;
    while (1)
    {
        if (!a.empty())
        {
            if (!firstOutput)
                cout << ' ';
            else
                firstOutput = false;
            cout << a.front();
            a.pop();
        }

        if (!a.empty())
        {
            if (!firstOutput)
                cout << ' ';
            else
                firstOutput = false;
            cout << a.front();
            a.pop();
        }

        if (!b.empty())
        {
            if (!firstOutput)
                cout << ' ';
            else
                firstOutput = false;
            cout << b.front();
            b.pop();
        }

        if (a.empty() && b.empty())
        {
            break;
        }
    }
    cout << endl;
}

int main()
{
    run();
    return 0;
}