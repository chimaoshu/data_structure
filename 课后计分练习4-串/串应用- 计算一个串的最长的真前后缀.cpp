#include <iostream>
#include <list>
#include <string>

using namespace std;

string matchedPrefixPostfix(string str)
{
    if (str.size() <= 1)
    {
        return string("empty");
    }

    list<string> prefixString;
    list<string> postfixString;

    string temp = str;
    temp.erase(temp.begin());
    while (!temp.empty())
    {
        postfixString.push_back(temp);
        temp.erase(temp.begin());
    }

    temp = str;
    temp.erase(--temp.end());
    while (!temp.empty())
    {
        prefixString.push_back(temp);
        temp.erase(--temp.end());
    }

    bool matched = false;
    string longestMatchedString;
    for (list<string>::iterator i = prefixString.begin(); i != prefixString.end(); i++)
    {
        temp = *i;
        for (list<string>::iterator j = postfixString.begin(); j != postfixString.end(); j++)
        {
            if (temp.compare(*j) == 0)
            {
                if (!matched)
                {
                    longestMatchedString = temp;
                    matched = 1;
                    break;
                }
                else
                {
                    if (temp.size() > longestMatchedString.size())
                    {
                        longestMatchedString = temp;
                        break;
                    }
                }
            }
        }
    }

    if (!matched)
    {
        longestMatchedString = "empty";
    }

    return longestMatchedString;
}

void run()
{
    int stringNumber;
    cin >> stringNumber;

    for (int i = 0; i < stringNumber; i++)
    {
        string userInput;
        cin >> userInput;

        string outputData = matchedPrefixPostfix(userInput);
        for (string::iterator i = outputData.begin(); i != outputData.end(); i++)
        {
            cout << *i;
        }
        cout << endl;
    }
}

int main()
{
    run();
    return 0;
}