#include <iostream>

using namespace std;

template <class T>
struct node
{
    // 数据区
    T data;

    // 指针区，这里的<T>表示模板中的T类型，可以是int、char之类的
    node<T> *next;
};

// 我在这里声明了模板T，那么这个类里面的所有T就都是同一个东西，相当于格式占位符
// 就好比之前c里面的define eleType int一样
// 如果要表示不同的意思，那么就定义多个，模板。
// 如果数量不确定，就要用到变长模板
// 之所以要用到template，是因为data内容可以存储任何类型的数据
template <class T>
class linkList
{

public:
    linkList();
    ~linkList();
    bool createListF(T a[], int n); // 头插法
    bool createListR(T a[], int n); // 尾插法
    void displayList();             // display
    int getLenth();                 // 获取长度
    T getElement(int i);            // 获取链表中第i个元素
    int locateElement(T e);         // 根据元素的值定位元素位置
    bool insertElement(int i, T e); // 在i位置插入元素e
    bool deleteElement(int i);      // 删除第i个位置的元素
    void Sort();                    // 排序

private:
    node<T> *head; // 表头，指向节点的指针
    int length;
};

// 构造函数
template <class T>
linkList<T>::linkList()
{
    // 新建一个节点做head
    head = new node<T>;
    head->next = NULL;
    length = 0;
};

// 析构函数
template <class T>
linkList<T>::~linkList()
{
    // 只能从前往后删除
    // 先定义俩指针
    // 这里pre和next指的是相邻的上下两个节点
    node<T> *preNode, *nextNode;

    // 先指向头部
    preNode = head;

    // 下一个非空证明未到结尾
    while (preNode->next != NULL)
    {
        // 存储下一个节点位置
        nextNode = preNode->next;

        // 删除前一个节点位置
        delete preNode;

        // 让preNode也指向下一个节点
        preNode = nextNode;
    }

    // 到达末尾了
    delete preNode;
}

// 链表是怎么存储的，几个节点就创建几次？？
// 就和顺序表一样，你加一个数据就insert一次

// 尾插法建立顺序表
template <class T>
bool linkList<T>::createListR(T a[], int n)
{
    // 数组a表示创建链表的数组
    // n表示数量

    node<T> *preNode, *newNode;
    preNode = head;
    for (int i = 0; i < n; i++)
    {
        // 新建新节点
        newNode = new node<T>;
        if (!newNode)
        {
            return false;
        }

        // 赋值新节点
        newNode->data = a[i];
        newNode->next = NULL;

        // 修改上个节点的next
        preNode->next = newNode;
        preNode = newNode;
    }
    // private中记录长度
    length = n;
    return true;
}

// 头插法建立顺序表
template <class T>
bool linkList<T>::createListF(T a[], int n)
{
    node<T> *preNode, *newNode;
    preNode = head;
    for (int i = 0; i < n; i++)
    {
        newNode = new node<T>;

        if (!newNode)
            return false;

        newNode->data = a[i];
        newNode->next = preNode->next; // preNode->next无论是NULL还是节点，都可以
        preNode->next = newNode;
        preNode = newNode;
    }
    length = n;
}

// 求顺序表的长度
template <class T>
int linkList<T>::getLenth()
{
    return length;
}

// 打印单链表
template <class T>
void linkList<T>::displayList()
{
    node<T> *preNode = head;

    // 只要非空就是没到达结尾
    while (preNode->next)
    {
        preNode = preNode->next;
        cout << preNode->data << "   "
             << endl;
    }
    cout << "\n"
         << endl;
}

// 另一种打印方法：通过length来判断末尾，而非NULL
// template<class T>
// void linkList<T>::DispList()
// {
// 	if (length > 0)
// 	{
// 		LinkList<T> *p;
// 		p = head->next;
// 		int i = 0;
// 		for (i = 0; i < length; i++)
// 		{
// 			cout << p->data << " ";
// 			p = p->next;
// 		}
// 	}
// 	cout << endl;
// }j

// 按序号查找元素
template <class T>
int linkList<T>::locateElement(T i)
{
    if (i < 0 || i >= length)
        return false;

    int order_number = 0;
    node<T> *preNode = head;

    while (preNode->next)
    {
        order_number++;
        preNode = preNode->next;

        if (preNode->data == i)
            return order_number;
    }
    return false;
}

// 按序号获取元素
template <class T>
T linkList<T>::getElement(int i)
{
    if (i > length || i < 1)
        return false;

    node<T> *preNode = head;
    for (int j = 0; j < i; j++)
    {
        // 空指针返回错误
        if (!preNode->next)
            return false;

        preNode = preNode->next;
    }
    return preNode->data;
}

// 插入元素e到i位置
template <class T>
bool linkList<T>::insertElement(int i, T e)
{
    if (i < 0 || i >= length)
        return false;

    node<T> *preNode = head;

    // 如果要插入到第i个位置，只需移动到第i-1个位置（次）
    for (int j = 0; j < i - 1; j++)
    {
        if (!preNode->next)
            return false;

        preNode = preNode->next;
    }

    // 现在preNode指向第i-1个节点
    node<T> *newNode = new node<T>;

    if (!newNode)
        return false;

    newNode->next = preNode->next;
    newNode->data = e;
    preNode->next = newNode;

    return true;
}

// 删除i位置的元素
template <class T>
bool linkList<T>::deleteElement(int i)
{
    if (i < 0 || i >= length)
        return false;

    node<T> *preNode = head, *p;

    // 删除第i个元素，只需移动到i-1个节点（次）
    for (int j = 0; j < i - 1; j++)
    {
        if (!preNode->next)
            return false;

        preNode = preNode->next;
    }

    // 现在preNode已经移动到了第i-1个节点，要删除下一个节点
    p = preNode->next;
    preNode->next = p->next;
    delete p;

    return true;
}

template <class T>
void linkList<T>::Sort()
{
    // TO DO
}

int main()
{
    linkList<int> list;
    int array[5] = {1, 2, 3, 4, 5};
    list.createListF(array, 5);
    // list.displayList();
    list.insertElement(1, 2);
    list.insertElement(1, 3);
    list.deleteElement(7);
    list.displayList();

    return 0;
}