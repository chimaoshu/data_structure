#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <string.h>
using namespace std;

bool firstOutput = true;

bool inTheSameGroup(list<int *> *groupList, int inputNumber, int originNumber)
{
    // 检查数字是否为某个group中分组
    for (list<int *>::iterator i = groupList->begin(); i != groupList->end(); i++)
    {
        int *eachGroup = *i;

        // 一个组内
        bool inputNumberIn = false;
        bool originNumberIn = false;
        for (int i = 0; i < eachGroup[0]; i++)
        {
            if (eachGroup[i + 1] == inputNumber)
            {
                inputNumberIn = 1;
            }
            if (eachGroup[i + 1] == originNumber)
            {
                originNumberIn = 1;
            }
            // cout << eachGroup[i + 1] << "test";
        }
        if (inputNumberIn && originNumberIn)
        {
            return 1;
        }
    }
    return 0;
}

void show(queue<int> *group)
{
    int front;
    while (!group->empty())
    {
        front = group->front();

        if (firstOutput)
        {
            cout << front;
            firstOutput = false;
        }
        else
        {
            cout << ' ' << front;
        }
        group->pop();
    }
}

void run()
{
    int groupNumber;
    cin >> groupNumber;

    // 主队列
    list<queue<int> *> myQueue;

    // 用一个字典来保存每个数值对应的队列
    // map<int, queue<int> *> memberGroupMapping;

    // 存储group
    list<int *> groupList;

    // 输入group
    int groupLength;
    int groupMember;
    for (int i = 0; i < groupNumber; i++)
    {
        // queue<int> *group = new queue<int>;
        // int group [100] = {0};
        int *group = new int(100);
        // group = {0};
        cin >> groupLength;
        group[0] = 0;

        for (int i = 0; i < groupLength; i++)
        {
            cin >> groupMember;
            group[group[0] + 1] = groupMember;
            group[0]++;
            // memberGroupMapping[groupMember] = group;
        }

        groupList.push_back(group);
        // myQueue.push(group);
    }

    char command[20];
    int inputNumber;
    while (true)
    {
        cin >> command;
        if (strcmp(command, "ENQUEUE") == 0)
        {
            cin >> inputNumber;
            // scanf("%d", &inputNumber);

            bool modified = false;
            for (list<std::queue<int> *>::iterator i = myQueue.begin(); i != myQueue.end(); i++)
            {
                queue<int> *thisGroup = *i;
                int originNumber = thisGroup->front();
                if (inTheSameGroup(&groupList, inputNumber, originNumber))
                {
                    thisGroup->push(inputNumber);
                    modified = true;
                    continue;
                }
            }

            if (modified)
                continue;

            queue<int> *newGroup = new queue<int>;
            newGroup->push(inputNumber);
            myQueue.push_back(newGroup);
        }
        else if (strcmp(command, "DEQUEUE") == 0)
        {
            queue<int> *deletedGroup = myQueue.front();

            if (firstOutput)
            {
                cout << deletedGroup->front();
                firstOutput = false;
            }
            else
            {
                cout << ' ' << deletedGroup->front();
            }
            deletedGroup->pop();
            if (deletedGroup->empty())
            {
                delete deletedGroup;
                myQueue.pop_front();
            }

            // show(deletedGroup);
            // delete deletedGroup;
        }
        else if (strcmp(command, "STOP") == 0)
        {
            cout << endl;
            break;
        }
        else
        {
            cout << "error";
        }
    }
}

int main()
{
    run();
    // char command[20];
    // while (1)
    // {
    //     cin >> command;
    //     cout << command << endl;
    //     if(strcmp(command, "123") == 0)
    //         break;
    // }
    return 0;
}