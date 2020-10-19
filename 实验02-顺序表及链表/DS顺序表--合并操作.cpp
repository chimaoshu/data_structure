#include <iostream>
using namespace std;

#define ok 1
#define error 0

template <class T>
class SeqList
{
private:
    T *list;
    int maxsize; // 最大长度
    int size;    // 实际长度

public:
    SeqList();
    ~SeqList();
    T *get_list() {return list;}
    int listsize() { return size; }
    int list_insert(int order_num, T item); // 插入
    int list_delete(int order_num);
    int list_get(int index);
    int list_find(T item); // 获取元素在数组中的位置
    void list_diaplay();
    int list_insert_by_order(T item); // 插入
};

template <class T>
SeqList<T>::SeqList()
{
    maxsize = 1000;
    size = 0;
    list = new T[maxsize];
}

template <class T>
SeqList<T>::~SeqList()
{
    delete[] list;
}

template <class T>
int SeqList<T>::list_insert(int order_num, T item)
{
    if (order_num < 1 || order_num > size + 1)
    {
        return error;
    }

    // 从[1]开始存储
    if (size + 1 == maxsize)
    {
        return error;
    }

    // order_num = 3, i = 4
    for (int i = size + 1; i > order_num; i--)
    {
        list[i] = list[i - 1];
        //cout << list[i] << list[i - 1] << endl;
    }

    // 插入位置为3，插入后就是第3个
    list[order_num] = item;
    size++;

    // list_diaplay();
    return ok;
}

template <class T>
int SeqList<T>::list_insert_by_order(T item)
{
    // 从[1]开始存储
    if (size + 1 == maxsize)
    {
        return error;
    }

    for (int i = 1; i <= size; i++)
    {
        if (i == size)
        {
            // list_insert(size + 1, item);
            if (list[i] <= item)
            {
                list_insert(size + 1, item);
                //list_diaplay();
                break;
            }
        }
        
        if (list[i] <= item && item <= list[i + 1])
        {
            list_insert(i + 1, item);
            //list_diaplay();
            break;
        }
    }
    return ok;
}

template <class T>
void SeqList<T>::list_diaplay()
{
    cout << size << " " << flush;
    for (int i = 1; i < size + 1; i++)
    {
        cout << list[i] << " " << flush;
    }
    cout << "\n"
         << flush;
}

template <class T>
int SeqList<T>::list_delete(int order_num)
{
    if (order_num < 1 || order_num > size)
    {
        return error;
    }

    for (int i = order_num; i < size; i++)
    {
        list[i] = list[i + 1];
    }

    size--;
    // list_diaplay();
    return ok;
}

template <class T>
int SeqList<T>::list_find(T item)
{
    for (int i = 1; i <= size; i++)
    {
        if (list[i] == item)
        {
            return i;
        }
    }
    return error;
}

template <class T>
int SeqList<T>::list_get(int index)
{
    if (index < 1 || index > size)
    {
        return error;
    }

    return list[index];
}

// template<class T>
// int SeqList<T>::list_merge(SeqList<T> *a, SeqList<T> *b)
// {
//     if (index < 1 || index > size)
//     {
//         return error;
//     }

//     return list[index];
// }

int main()
{
    SeqList<int> a;
    SeqList<int> b;

    int length;
    int j;

    scanf("%d", &length);
    for (int i = 0; i < length; i++)
    {
        scanf(" %d", &j);
        a.list_insert(i + 1, j);
    }

    scanf("%d", &length);
    for (int i = 0; i < length; i++)
    {
        scanf(" %d", &j);
        b.list_insert(i + 1, j);
    }

    int *list = b.get_list();
    for (int i = 1; i <= b.listsize(); i++)
    {
        a.list_insert_by_order(list[i]);
    }
    a.list_diaplay();

    return 0;
}
