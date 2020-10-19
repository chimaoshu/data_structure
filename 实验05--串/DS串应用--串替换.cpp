#include <iostream>
#include <string>

using namespace std;

class myString
{
private:
    string mainstr; //串
    int size;       //串长度

public:
    myString(string mainstr); //构造函数
    ~myString();              //析构函数

    int *GetNext(string str);
    int KMPFindAndReplace(string p, int pos, int next[], string replaceString);
    void SetVal(string sp); //设定主事字符内容和长度
    int KMPFindSubstr(string p, int pos, string replaceString);
};

myString::myString(string mainstr) //构造函数，定义对象并赋初始串值
{
    this->mainstr = mainstr;
    this->size = mainstr.size();
}

myString::~myString()
{
    size = 0;
    mainstr = "";
}

void myString::SetVal(string sp)
{
    mainstr = "";
    mainstr.assign(sp);
    size = mainstr.length();
}

char getCharInString(string *str, int index)
{
    string::iterator it2 = (*str).begin();
    advance(it2, index - 1);
    return *it2;
}

void unitTest()
{
    string a = "123123";
    cout << getCharInString(&a, 1);
    // myString a = myString("ABCDABD");
    // a.GetNext();
    // return 0;
    return;
}

int *myString::GetNext(string str)
{

    // first place of next storages length
    int *next = new int[str.size() + 1];
    next[0] = str.size();
    next[1] = 0;

    int i = 1;
    int j = i;
    while (1)
    {
        if (i == str.size() + 1)
            break;

        char si = getCharInString(&str, i);
        if (next[j] == 0 || si == getCharInString(&str, next[j]))
        {
            i++;
            next[i] = next[j] + 1;
            j = i;
        }
        else
            j = next[j];
    }
    // for (int i = 0; i < next[0]; i++)
    // {
    //     cout << next[i + 1] - 1 << ' ';
    // }
    // cout << endl;
    return next;
}

int myString::KMPFindSubstr(string p, int pos, string replaceString)
{
    // 主串从pos开始查找子串p。找到返回p在主串的开始位置。否则返回-1。
    int *next = GetNext(p);

    int v = -1;
    v = KMPFindAndReplace(p, pos, next, replaceString);

    // delete[] next;
    return v;
}

int myString::KMPFindAndReplace(string p, int pos, int next[], string replaceString)
{
    int i = pos;
    int j = 1;
    while (1)
    {
        if (j == 0 || getCharInString(&(this->mainstr), i) == getCharInString(&p, j))
        {
            if (j == p.size())
            {
                int countEraseTime = 0;
                for (int i2 = 0; i2 < replaceString.size(); i2++)
                {
                    string::iterator it = this->mainstr.begin();
                    advance(it, i - p.size() + i2); // j位置
                    if (countEraseTime < p.size())
                    {
                        this->mainstr.erase(it);
                        countEraseTime++;
                    }
                    this->mainstr.insert(it, getCharInString(&replaceString, i2 + 1));
                }
                for (string::iterator i3 = this->mainstr.begin(); i3 != this->mainstr.end(); i3++)
                {
                    cout << *i3;
                }
                cout << endl;
                return 0;
            }
            i++;
            j++;
        }
        else
        {
            if (i == this->size)
            {

                for (string::iterator i = this->mainstr.begin(); i != this->mainstr.end(); i++)
                {
                    cout << *i;
                }
                cout << endl;
                return 0;
            }

            j = next[j];
        }
    }
}

void run()
{
    int instanceNumber;
    cin >> instanceNumber;

    for (int i = 0; i < instanceNumber; i++)
    {
        string mainString;
        cin >> mainString;

        string subString;
        cin >> subString;

        string replaceString;
        cin >> replaceString;

        for (string::iterator i = mainString.begin(); i != mainString.end(); i++)
        {
            cout << *i;
        }
        cout << endl;

        myString a = myString(mainString);
        int pos = a.KMPFindSubstr(subString, 1, replaceString);
    }
}

int main()
{
    run();
    return 0;
}