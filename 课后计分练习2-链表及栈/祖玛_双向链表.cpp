#include <iostream>
#include <list>
using namespace std;

void show(list<char> *a)
{
    if (a->empty())
    {
        cout << '-' << endl;
        return;
    }

    for (list<char>::iterator i = a->begin(); i != a->end(); i++)
        cout << *i << flush;

    cout << endl;
}

// 删除第index个元素（从0开始）
void delete_list(list<char> *a, int index)
{
    list<char>::iterator it = a->begin();
    advance(it, index);
    if (it != a->end())
        a->erase(it);
}

// index 从0开始
void insert(list<char> *a, int index, char data)
{
    list<char>::iterator iter = a->begin();
    std::advance(iter, index);
    a->insert(iter, data);
}

void reflashStatus(list<char> *a)
{
    // bool makeChanges = false;

    for (list<char>::iterator iter = a->begin(); iter != a->end(); iter++)
    {
        list<char>::iterator last_it = --iter;
        iter++;

        // list<char>::iterator last_last_it = --last_it;
        // last_it++;

        list<char>::iterator next_it = ++iter;
        iter--;

        if (*last_it == *iter && *next_it == *iter)
        {
            // makeChanges = true;
            char data = *iter;

            a->erase(last_it);
            a->erase(iter);

            // erase会返回下一个迭代器的指针
            next_it = a->erase(next_it);

            // 3个以上相连都要删除
            while (next_it != a->end())
            {
                if (*next_it == data)
                    next_it = a->erase(next_it);
                else
                    break;
            }
            iter = a->begin();
        }
    }

    // 递归调用
    // if (makeChanges)
    // {
    //     reflashStatus(a);
    // }
}

bool reflashStatus_2(list<char> *a)
{
    list<char>::iterator iter = a->begin();

    int index = 1;
    while (iter != a->end())
    {
        int count = 1;
        list<char>::iterator iter2 = --iter;
        iter++;

        while (iter2 != a->end() && *iter == *iter2)
        {
            count++;
            iter2++;
        }
        if (count >= 3)
        {
            for (int i = index, j = 0; j < count; j++)
            {
                delete_list(a, i);
            }
            return 1;
        }
        index++;
        iter++;
    }
    return 0;
}

void run()
{
    char ball;
    list<char> a;

    while ((ball = getchar()) != '\n')
    {
        a.push_back(ball);
    }

    reflashStatus(&a);

    int operationTimes;
    cin >> operationTimes;

    for (int i = 0; i < operationTimes; i++)
    {
        int insertPosition;
        char ball;
        cin >> insertPosition >> ball;

        // 不这样的话，会循环链表那样子插入
        if (insertPosition > a.size())
        {
            insertPosition = a.size();
        }

        // 插入
        insert(&a, insertPosition, ball);

        // 刷新状态
        reflashStatus(&a);

        // 显示
        show(&a);
    }
}

void run2()
{

    char ball;
    list<char> a;

    while ((ball = getchar()) != '\n')
    {
        a.push_back(ball);
    }
    reflashStatus_2(&a);

    int operationTimes;
    cin >> operationTimes;

    int len = a.size();
    for (int i = 0; i < operationTimes; i++)
    {
        int index;
        char ch;
        cin >> index >> ch;
        insert(&a, index, ch);

        while (1)
        {
            if (reflashStatus_2(&a) != 1)
                break;
        }
        show(&a);
    }
}

int main()
{
    run();
    return 1;
}
