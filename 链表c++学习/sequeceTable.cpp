#include <iostream>
#include <cstdlib>

using namespace std;

// 函数返回状态码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //不可能的
#define OVERFLOW -2

typedef int Status;

// 线性表的动态分配顺序存储结构
#define LIST_INIT_SIZE 10 //线性表存储空间的初始分配量
#define LISTINCREMENT 5  //线性表存储空间的分配增量
#define ElemType int     //定义基本类型为int

typedef struct
{
    ElemType *elem; //存储空间基址（指向第一处内存）
    int length;     //当前长度
    int listsize;   //当前分配得存储容量（以sizof(ElemType)为单位）
} SqList;

// 初始化
Status InitSqList(SqList *L)
{
    // 意思是分配LIST_INIT_SIZE个sizeof(ElemType)大小的空间，然后把void指针转化为ElemType指针
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));

    // 判断内存分配是否成功
    if(!L->elem) 
        return OVERFLOW;

    L->length = 0; //空表长度为0
    L->listsize = LIST_INIT_SIZE; // 存储初始变量

    return OK;
}

// 在顺序表的第i个位置插入e
Status InsertSqListElem(SqList *L, int i, ElemType e)
{
    // 判断插入位置是否合法
    if(i < 1 || i > (L->length + 1))
        return ERROR;

    // 储存空间满了
    if (L->length == L->listsize)
    {
        // 分配内存给新的顺序表
        ElemType *newList = (ElemType *)malloc((L->length + LISTINCREMENT) * sizeof(ElemType));

        // 检查是否分配成功
        if(!newList)
            return OVERFLOW;

        // 把原来顺序表的内容复制到新的顺序表
        for (int j = 0; j <= L->length; j++)
        {
            *(newList + j) = *(L->elem + j);
        }

        // 释放后分配
        free(L->elem);
        L->elem = newList;
    }

    // 从后往前移动指针，开始插入
    for (int j = L->length; j >= 0; j--)
    {
        // 空数组的话，直接赋值
        if(j == 0)
        {
            *(L->elem) = e;
            L->length ++;
            return OK;
        }

        // 元素往后移动一位
        *(L->elem + j) = *(L->elem + j - 1);

        // 到达位置进行插入
        if(j + 1 == i)
        {
            // 插入
            *(L->elem + j) = e;

            // 增加长度
            L->length ++;
            return OK;
        }
    }
}

// 指定位置i删除元素
Status DeleteSqListElem(SqList *L, ElemType i)
{
    // 判断删除位置是否合法
    if(i < 1 || i > L->length)
        return ERROR;

    // 指针从删除位置向后移动
    for (int j = i - 1; j < L->length - 1; j++)
    {
        *(L->elem + j) = *(L->elem + j + 1);
    }

    L->length --;
    return OK;
}

void PrintSqList(SqList *L)
{
    for(int i = 0; i < L->length; i++)
    {
        cout<<*(L->elem + i)<<"\n"<<endl;
    }
}

void ProcessStatus(Status s)
{
    switch (s)
    {
    case OK:
        cout<<"OK\n"<<endl;
        break;
    case ERROR:
        cout<<"ERROR\n"<<endl;
        break;
    case OVERFLOW:
        cout<<"OVERFLOW\n"<<endl;
        break;
    case INFEASIBLE:
        cout<<"INFEASIBLE\n"<<endl;
        break;
    default:
        cout<<"FALSE\n"<<endl;
        break;
    }
}

int main()
{
    SqList L;

    // 指向结构体L的位置
    InitSqList(&L);

    InsertSqListElem(&L, 1, 13);
    InsertSqListElem(&L, 2, 15);
    InsertSqListElem(&L, 2, 14);
    InsertSqListElem(&L, 1, 2);
    InsertSqListElem(&L, 3, 1336);
    InsertSqListElem(&L, 1, 4);
    InsertSqListElem(&L, 2, 3);
    DeleteSqListElem(&L, 8);

    PrintSqList(&L);
    return 1;
}