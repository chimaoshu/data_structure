#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
};

class linkListClass
{
public:
    node *head;

public:
    linkListClass();
    ~linkListClass();
    void show();
    bool append(int element);
    bool pop(int index);
    bool insert(int element, int index);
};

linkListClass::linkListClass()
{
    node *newNode = new node;
    this->head = newNode;
    newNode->next = this->head;
}

linkListClass::~linkListClass()
{
    node *p = this->head, *q;
    while (true)
    {
        q = p->next;
        delete p;
        p = q;

        if (p == this->head)
            break;
    }
}

void linkListClass::show()
{
    node *p = head->next;

    if (p == this->head)
        cout << "error" << endl;

    while (p != this->head)
    {
        cout << p->data << " " << flush;
        p = p->next;
    }
    cout << endl;
}

bool linkListClass::append(int element)
{
    node *p = this->head;

    while (p->next != this->head)
        p = p->next;

    node *newNode = new node;

    if (newNode == this->head)
        return false;

    newNode->data = element;
    newNode->next = this->head;
    p->next = newNode;

    return true;
}

bool linkListClass::insert(int element, int index)
{
    node *p = head;

    int i = 1;
    while (true)
    {
        if (index == i)
        {
            node *newNode = new node;
            newNode->data = element;
            newNode->next = p->next;
            p->next = newNode;
            return true;
        }
        i++;
        p = p->next;

        if (p == this->head)
            return false;
    }
    return false;
}

bool linkListClass::pop(int index)
{
    node *p = head, *q;

    int i = 1;
    while (true)
    {
        if (index == i)
        {
            q = p->next;
            p->next = q->next;
            delete q;
            return true;
        }
        i++;
        p = p->next;
        if (p == this->head)
        {
            return false;
        }
    }
    return false;
}

int run()
{

    int N, K, S;
    while (cin >> N >> K >> S)
    {
        linkListClass a = linkListClass();

        // 给循环链表赋值
        for (int i = 1; i < N + 1; i++)
        {
            a.append(i);
        }

        // 移动到第S个人的前一个位置
        node *p = a.head;
        for (int i = 0; i < S - 1; i++)
        {
            p = p->next;
        }

        while (true)
        {
            // 现在p的位置是第一个人的前一个位置
            // 开始数数，跳过头结点，数K-1次
            for (int i = 0; i < K - 1; i++)
            {
                p = p->next;
                if (p == a.head)
                {
                    p = p->next;
                }
            }

            // 检查下一个节点是否是头结点
            if (p->next == a.head)
            {
                p = p->next;
            }

            // 现在p的位置是第K人的前面
            // 输出
            cout << p->next->data << ' ' << flush;

            // 出列
            node *q = p->next;
            p->next = p->next->next;
            delete q;

            // 跳出条件：只剩一个元素
            if (a.head->next == a.head)
            {
                break;
            }
        }
        cout << endl;
    }
    return 1;
}

int main()
{
    run();
    return 1;
}
