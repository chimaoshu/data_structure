#include <iostream>
#include <string>

using namespace std;

// 相当于切片了
char getCharInString(string *str, int index)
{
    string::iterator it = str->begin();
    advance(it, index);
    return *it;
}

int getMaxRepeatedSubStringLength(string str)
{
    int maxRepeatedSubStringLength = -1;
    for (int i = 0; i < str.size(); i++)
    {
        // 获得i处的字符
        char temp = getCharInString(&str, i);

        // 下一个相同字符的位置
        int nextPositionOfTempWord = i;

        while (1)
        {
            // 寻找
            nextPositionOfTempWord = str.find(temp, nextPositionOfTempWord + 1);

            // 找不到
            if (nextPositionOfTempWord == str.npos)
                break;
            // 找到了
            else
            {
                // 第一个配上了，检查后方是否配对
                // 其中j1在前，j2在后，后移匹配
                int j1 = i + 1;
                int j2 = nextPositionOfTempWord + 1;
                int length = 1;
                while (1)
                {
                    if (j1 == str.size() || j2 == str.size() || j1 == nextPositionOfTempWord)
                        break;

                    if (getCharInString(&str, j1) == getCharInString(&str, j2))
                    {
                        length++;
                        j1++;
                        j2++;
                    }
                    else
                        break;
                }
                if (length > maxRepeatedSubStringLength)
                    maxRepeatedSubStringLength = length;
            }
            // 结束一次匹配后，继续循环找后面匹配的，直到匹配不到
        }
    }
    return maxRepeatedSubStringLength;
}

void run()
{
    int testTime;
    cin >> testTime;

    for (int i = 0; i < testTime; i++)
    {
        string userInput;
        cin >> userInput;

        cout << getMaxRepeatedSubStringLength(userInput) << endl;
    }
}

int main()
{
    run();
    // getMaxRepeatedSubStringLength(string("1231234"));
    // cout << string("1231234").find('1',3);
    return 0;
}