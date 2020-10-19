#include <list>
#include <string>
#include <iostream>
using namespace std;

void run()
{
    string userInput;
    list<char> outputData;
    while (cin >> userInput)
    {
        list<char>::iterator it = outputData.begin();
        for (string::iterator i = userInput.begin(); i != userInput.end(); i++)
        {
            switch (*i)
            {
            case '[':
                it = outputData.begin();
                break;
            case ']':
                it = outputData.end();
                break;
            default:
                outputData.insert(it, *i);
            }
        }

        // 输出
        for (list<char>::iterator i = outputData.begin(); i != outputData.end(); i++)
        {
            cout << *i;
        }
        cout << endl;
        outputData.clear();
    }
    return;
}

int main()
{
    run();
    return 0;
}