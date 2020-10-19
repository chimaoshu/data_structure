#include <stack>
#include <string>
#include <iostream>
using namespace std;

void run()
{
    string userInput;
    cin >> userInput;
    stack<int> s;

    char firstChar;
    firstChar = *userInput.begin();

    int index = 0;
    for (string::iterator i = userInput.begin(); i != userInput.end(); i++)
    {
        if (*i == firstChar)
        {
            s.push(index);
        }
        else
        {
            cout << s.top() << ' ' << index << endl;
            s.pop();
        }
        index++;
    }
}

int main()
{
    run();
    return 0;
}