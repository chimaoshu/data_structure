#include <iostream>
using namespace std;

#define ok 1
#define error 0

class ListNode
{
public:
    int coefficient;
    int power;
    ListNode *next;
    ListNode() { next = NULL; }
};

class LinkList
{
public:
    ListNode *head;
    int len;

    LinkList();
    ~LinkList();
    void LL_display();
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

void LinkList::LL_display()
{
    ListNode *p = head->next;
    while (p)
    {
        if (p->power == 0)
        {
            if (p->coefficient > 0)
                cout << p->coefficient << flush;
            else
                cout << "(" << p->coefficient << ")" << flush;
        }
        else if (p->coefficient < 0)
        {
            if (p->power > 0)
            {
                cout << "(" << p->coefficient << ")"
                     << "x^" << p->power << flush;
            }
            else
            {
                cout << "(" << p->coefficient << ")"
                     << "x^"
                     << "(" << p->power << ")" << flush;
            }
        }
        else
        {
            if (p->power > 0)
                cout << p->coefficient << "x^" << p->power << flush;
            else
                cout << p->coefficient << "x^"
                     << "(" << p->power << ")" << flush;
        }

        if (p->next)
            cout << " + " << flush;
        else
            cout << endl;

        p = p->next;
    }
}

// 相加
ListNode *add_poly(LinkList *a, LinkList *b)
{
    ListNode *output = new ListNode;
    output->next = NULL;

    ListNode *p, *q, *l;
    p = a->head->next;
    q = b->head->next;
    l = output;

    while (p && q)
    {
        if (p->power < q->power)
        {
            l->next = p;
            l = l->next;
            p = p->next;
        }
        else if (p->power == q->power)
        {
            int temp = p->coefficient + q->coefficient;
            if (temp == 0)
            {
                p = p->next;
                q = q->next;
            }
            else
            {
                ListNode *a = new ListNode;
                a->coefficient = temp;
                a->power = p->power;
                a->next = NULL;
                l->next = a;
                l = l->next;
                p = p->next;
                q = q->next;
            }
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
    int test_example;
    scanf("%d", &test_example);
    for (int i = 0; i < test_example; i++)
    {
        // 录入数据1
        int poly_length;
        LinkList *a = new LinkList;
        ListNode *p = a->head;

        scanf("%d", &poly_length);
        for (int j = 0; j < poly_length; j++)
        {
            ListNode *newNode = new ListNode;
            scanf("%d %d", &newNode->coefficient, &newNode->power);
            p->next = newNode;
            newNode->next = NULL;
            p = newNode;
        }
        a->LL_display();

        // 录入数据2
        LinkList *b = new LinkList;
        p = b->head;
        scanf("%d", &poly_length);
        for (int j = 0; j < poly_length; j++)
        {
            ListNode *newNode = new ListNode;
            scanf("%d %d", &newNode->coefficient, &newNode->power);
            p->next = newNode;
            newNode->next = NULL;
            p = newNode;
        }
        b->LL_display();

        // 计算
        LinkList *output = new LinkList;
        output->head = add_poly(a, b);
        output->LL_display();
    }
    return 0;
}
