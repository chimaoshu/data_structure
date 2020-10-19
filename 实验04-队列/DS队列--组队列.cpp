#include <iostream>
#include <map>
#include <queue>
#include <string.h>
using namespace std;

bool firstOutput = true;

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
    }
}

void run()
{
    int groupNumber;
    cin >> groupNumber;

    queue<queue<int> *> myQueue;

    // 用一个字典来保存每个数值对应的队列
    map<int, queue<int> *> memberGroupMapping;

    // 输入group
    int groupLength;
    int groupMember;
    for (int i = 0; i < groupNumber; i++)
    {
        queue<int> *group = new queue<int>;
        cin >> groupLength;

        for (int i = 0; i < groupLength; i++)
        {
            cin >> groupMember;
            group->push(groupMember);
            memberGroupMapping[groupMember] = group;
        }

        myQueue.push(group);
    }

    char command[20], inputNumber;
    while (true)
    {
        cin >> command;
        if (strcmp(command, "ENQUEUE"))
        {
            cin >> inputNumber;

            // 看是数值否存在于group中
            queue<int> *targetGroup = memberGroupMapping[inputNumber];
            if (targetGroup)
            {
                targetGroup->push(inputNumber);
            }
            else
            {
                queue<int> *newGroup = new queue<int>;
                newGroup->push(inputNumber);
                memberGroupMapping[inputNumber] = newGroup;
                myQueue.push(newGroup);
            }
        }
        else if (strcmp(command, "DEQUEUE"))
        {
            queue<int> *deletedGroup = myQueue.front();
            myQueue.pop();
            show(deletedGroup);
            delete deletedGroup;
        }
        else if (strcmp(command, "STOP"))
        {
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