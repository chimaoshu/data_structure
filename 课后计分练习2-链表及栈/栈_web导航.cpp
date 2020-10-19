#include <iostream>
#include <stack>
#include <string>
#include <list>

using namespace std;

void visit(stack<string> *forwardStack, stack<string> *backwardStack, string url)
{
}

void back(stack<string> *forwardStack, stack<string> *backwardStack)
{
}

void forward(stack<string> *forwardStack, stack<string> *backwardStack)
{
}

// 默认以空格隔开，默认无最大切割限制(即0)，最后会得到maxSplitString个字符串
list<string> *split(string mainString, char a = ' ', int maxStringOutcome = 0)
{
    string tempString;
    list<string> *output = new list<string>;

    // 天生为1串，每切一次多一串
    int splitStringNumber = 1;

    for (int i = 0; i < mainString.length(); i++)
    {
        char ch = mainString[i];

        if (ch == a && splitStringNumber != maxStringOutcome)
        {
            if (tempString.length() != 0)
            {
                output->push_back(tempString);
                tempString.clear();
                splitStringNumber++;
            }
            continue;
        }
        else
        {
            tempString += ch;
        }
    }

    if (tempString.length() != 0)
    {
        output->push_back(tempString);
    }

    return output;
}

// split单元测试
void unitTestSplit()
{
    auto a = string("VISIT http://acm.ashland.edu/");
    auto b = split(a, ' ', 2);
    auto c = b->begin();
    while (c != b->end())
    {
        cout << *c << " ";
        c++;
    }
}

void showString(string a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << i << flush;
    }
    cout << endl;
}

void run()
{
    stack<string> forwardStack;
    stack<string> backwardStack;
    string currentURL = string("http://www.acm.org/");

    while (true)
    {

        string userInput;
        getline(cin, userInput);

        list<string> *splitOutcome = split(userInput, ' ', 2);
        list<string>::iterator iter = splitOutcome->begin();

        string command = *iter;

        // VISIT
        if (splitOutcome->size() == 2)
        {
            string url = string(*(++iter));
            if (!currentURL.empty())
            {
                // backward
                backwardStack.push(currentURL);
            }
            // current
            currentURL = url;

            // forawrd
            while (!forwardStack.empty())
            {
                forwardStack.pop();
            }
            cout << currentURL << endl;
        }
        else if (command == string("BACK"))
        {
            if (backwardStack.empty())
                cout << "Ignored" << endl;
            else
            {
                forwardStack.push(currentURL);
                currentURL = backwardStack.top();
                backwardStack.pop();
                cout << currentURL << endl;
            }
        }
        else if (command == string("FORWARD"))
        {
            if (forwardStack.empty())
                cout << "Ignored" << endl;
            else
            {
                backwardStack.push(currentURL);
                currentURL = forwardStack.top();
                forwardStack.pop();
                cout << currentURL << endl;
            }
        }
        // QUIT
        else if (command == string("QUIT"))
        {
            // cout << "QUIT" << endl;
            break;
        }
        else
        {
            cout << "输入错误" << endl;
        }
    }
}

int main()
{
    run();
    // unitTestSplit();
    return 0;
}