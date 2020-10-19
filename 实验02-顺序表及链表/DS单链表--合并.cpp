#include <iostream>
using namespace std;

#define ok 1
#define error 0

class ListNode
{
public:
    int data;
    ListNode *next;
};

class LinkList
{
public:
    ListNode *head;
    int len;

    LinkList();
    ~LinkList();

    ListNode *LL_index(int i); // 索引i结点，不存在返回NULL
    int LL_get(int i);         // 获取i位置的数据
    int LL_insert(int i, int item);
    int LL_delete(int i);
    void LL_display();
    int LL_merge(ListNode *Lb);
    int list_insert_by_order(int item);
};

LinkList::LinkList()
{
    head = new ListNode();
    head->next = NULL;
    len = 0;
}

LinkList::~LinkList()
{
    ListNode *p = head, *q;
    while (p->next)
    {
        q = p->next;
        delete p;
        p = q;
    }

    // 最后删除p
    delete p;
}

// 这算法过不了，无语了
int LinkList::list_insert_by_order(int item)
{
    ListNode *p = head->next;

    int index = 0;
    while (p)
    {
        index++;
        if (!p->next)
        {
            LL_insert(index + 1, item);
            break;
        }
        if (p->data <= item && item <= p->next->data)
        {
            LL_insert(index + 1, item);
            break;
        }
        p = p->next;
    }
    return ok;
}


// 还是过不了
int LinkList::LL_merge(ListNode *Lb)
{
    // Lb是head
    while (Lb)
    {
        Lb = Lb->next;
        if (Lb)
        {
            list_insert_by_order(Lb->data);
        }
    }
}

// int LinkList::LL_merge(ListNode *La, ListNode *Lb)
// {
//     ListNode *p, *q;
//     int index =0;

//     p = La->next;
//     q = Lb->next;

//     while (p&&q)
//     {
//         index++;
//         if (p->data >= q->data)
//         {
//             p = p->next;
//         }
//         else
//         {
//             LL_insert(index + 1, q->data);
//         }

//     }
// }

void LinkList::LL_display()
{
    ListNode *p = head->next;
    while (p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int LinkList::LL_insert(int i, int item)
{
    ListNode *p = head, *q, *test;

    if (i < 1 || i > len + 1)
        return error;

    // 移动到第i-1（次）
    for (int j = 0; j < i - 1; j++)
    {
        if (!p->next)
            return error;

        p = p->next;
    }

    q = new ListNode();

    if (!q)
        return error;

    test = p->next;
    q->next = p->next;
    q->data = item;
    p->next = q;

    len++;
    return ok;
}

int LinkList::LL_delete(int i)
{
    ListNode *p = head, *q;

    if (i < 1 || i > len + 1)
        return error;

    // 移动到第i-1个节点
    for (int j = 0; j < i - 1; j++)
    {
        if (!p->next)
            return error;
        p = p->next;
    }

    q = p->next;
    p->next = q->next;
    delete q;
    len--;

    return ok;
}

int LinkList::LL_get(int i)
{
    ListNode *p = head;

    if (i < 1 || i > len + 1)
        return error;

    // 移动到第i个节点
    for (int j = 0; j < i; j++)
    {
        if (!p->next)
            return error;
        p = p->next;
    }
    return p->data;
}

ListNode *LinkList::LL_index(int i)
{
    ListNode *p = head;

    if (i < 1 || i > len + 1)
        return error;

    // 移动到第i个节点
    for (int j = 0; j < i; j++)
    {
        if (!p->next)
            return error;
        p = p->next;
    }
    return p;
}


// 绝了，过不了
ListNode *LL_merge(ListNode *La, ListNode *Lb)
{
    ListNode *output = new ListNode;
    output->next = NULL;

    ListNode *p, *q, *l;
    p = La->next;
    q = Lb->next;
    l = output;

    while (p&&q)
    {
        if (p->data <= q->data)
        {
            l->next = p;
            l = l->next;
            p = p->next;
        }
        else
        {
            l->next = q;
            l = l->next;
            q = q->next;
        }
    }

    // 剩下的全部接上去
    if (p)
    {
        l->next = p;
    }
    else if (q)
    {
        l->next = q;
    }
    return output;
}

int main()
{
    LinkList *a = new LinkList();
    LinkList *b = new LinkList();

    int length;
    int j;

    scanf("%d", &length);
    for (int i = 0; i < length; i++)
    {
        scanf(" %d", &j);
        a->LL_insert(i + 1, j);
    }

    scanf("%d", &length);
    for (int i = 0; i < length; i++)
    {
        scanf(" %d", &j);
        b->LL_insert(i + 1, j);
    }

    LinkList *output = new LinkList();
    output->head = LL_merge(a->head, b->head);
    output->LL_display();
    // a->LL_merge(b->head);
    // // delete b;
    // a->LL_display();
    return 0;
}
