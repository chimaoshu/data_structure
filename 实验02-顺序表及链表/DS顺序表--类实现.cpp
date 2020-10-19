#include<iostream>
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
    int listsize() {return size;}
    int list_insert(int order_num, T item); // 插入
    int list_delete(int order_num);
    int list_get(int index);
    int list_find(T item);  // 获取元素在数组中的位置
    void list_diaplay();
};

template<class T>
SeqList<T>::SeqList()
{
    maxsize = 1000;
    size = 0;
    list = new T[maxsize];
}

template<class T>
SeqList<T>::~SeqList()
{
    delete[] list;
}

template<class T>
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
    size ++;

    // list_diaplay();
    return ok;
}

template<class T>
void SeqList<T> ::list_diaplay()
{
    cout << size << " " << flush;
    for(int i = 1; i < size + 1; i ++)
    {
        cout << list[i] << " " << flush;
    }
    cout << "\n" << flush;
}

template<class T>
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

    size --;
    // list_diaplay();
    return ok;
}

template<class T>
int SeqList<T>::list_find(T item)
{
    for (int i = 1; i <= size; i ++)
    {
        if (list[i] == item)
        {
            return i;
        }
    }
    return error;
}

template<class T>
int SeqList<T>::list_get(int index)
{
    if (index < 1 || index > size)
    {
        return error;
    }

    return list[index];
}

int main()
{
    SeqList<int> a;

    int length;
    scanf("%d", &length);

    int input_num;
    for (int i = 0; i < length; i++)
    {
        scanf(" %d", &input_num);
        a.list_insert(i + 1, input_num);
    }
    a.list_diaplay();

    int order_num, insert_data;
    scanf("%d %d", &order_num, &insert_data);
    if(a.list_insert(order_num, insert_data))
        a.list_diaplay();
    else
        cout << "error" << endl;

    scanf("%d %d", &order_num, &insert_data);
    if(a.list_insert(order_num, insert_data))
        a.list_diaplay();
    else
        cout << "error" << endl;

    int delete_index;
    scanf("%d", &delete_index);
    if (a.list_delete(delete_index))
        a.list_diaplay();
    else
        cout << "error" << endl;

    scanf("%d", &delete_index);
    if (a.list_delete(delete_index))
        a.list_diaplay();   
    else
        cout << "error" << endl;


    int num_to_find;
    int the_index;

    scanf("%d", &num_to_find);
    the_index = a.list_get(num_to_find);
    if (the_index)
        cout << the_index << endl;
    else
        cout << "error" << endl;

    //a.list_diaplay();
    scanf("%d", &num_to_find);
    the_index = a.list_get(num_to_find);
    if (the_index)
        cout << the_index << endl;
    else
        cout << "error" << endl;
    
    return 0;
}
