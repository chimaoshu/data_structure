#include <iostream>
#include <list>
using namespace std;

// 多项式的一个项
struct term
{
    int coefficients;
    int index;
};

void show(list<term *> *a)
{
    bool isFirst = true;
    bool haveBeenPrint = false; // 若无输出，则输出0

    for (list<term *>::iterator i = a->begin(); i != a->end(); i++)
    {
        // 加减号
        if (isFirst)
        {
            if ((*i)->coefficients != 0)
                isFirst = false;
        }
        else
        {
            if ((*i)->coefficients > 0)
            {
                cout << '+' << flush;
                haveBeenPrint = true;
            }

            else if ((*i)->coefficients == 0)
                continue;
        }

        // 系数为1/-1指数为0-->显示系数
        // 系数为1指数不为0-->忽略系数
        // 系数为0-->忽略系数
        // 系数为-1指数不为0-->显示负号
        // 系数不为1、-1-->显示系数
        if (((*i)->coefficients == 1 || (*i)->coefficients == -1) && (*i)->index == 0)
        {
            cout << (*i)->coefficients << flush;
            haveBeenPrint = true;
        }
        else if ((*i)->coefficients != 1)
        {
            if ((*i)->coefficients == -1)
            {
                cout << '-' << flush; // 显示负号
                haveBeenPrint = true;
            }
            else if ((*i)->coefficients == 0)
                continue; // 忽略输出
            else
            {
                cout << (*i)->coefficients << flush;
                haveBeenPrint = true;
            }
        }

        // x与指数
        if ((*i)->index == 0)
            continue;

        else if ((*i)->index == 1)
        {
            cout << 'x' << flush;
            haveBeenPrint = true;
        }

        else
        {
            cout << "x^" << (*i)->index << flush;
            haveBeenPrint = true;
        }
    }
    if (!haveBeenPrint)
        cout << 0 << flush;
    cout << endl;
}

list<term *> *add(list<term *> *a, list<term *> *b)
{
    // 迭代器
    list<term *>::iterator iterator_a = a->begin(), iterator_b = b->begin();

    // 新数组
    list<term *> *newList = new list<term *>;

    // 按大小输入
    while (iterator_a != a->end() && iterator_b != b->end())
    {
        if ((*iterator_a)->index < (*iterator_b)->index)
        {
            newList->push_back(*iterator_a);
            iterator_a++;
        }
        else if ((*iterator_a)->index == (*iterator_b)->index)
        {
            term *newTerm = new term;
            newTerm->coefficients = (*iterator_a)->coefficients + (*iterator_b)->coefficients;
            newTerm->index = (*iterator_a)->index;
            newList->push_back(newTerm);
            iterator_a++;
            iterator_b++;
        }
        else
        {
            newList->push_back(*iterator_b);
            iterator_b++;
        }
    }

    // 输入剩余
    for (; iterator_a != a->end(); iterator_a++)
    {
        newList->push_back(*iterator_a);
    }

    for (; iterator_b != b->end(); iterator_b++)
    {
        newList->push_back(*iterator_b);
    }
    return newList;
}

list<term *> *sub(list<term *> *a, list<term *> *b)
{
    // 迭代器
    list<term *>::iterator iterator_a = a->begin(), iterator_b = b->begin();

    // 新数组
    list<term *> *newList = new list<term *>;

    // 按大小输入
    while (iterator_a != a->end() && iterator_b != b->end())
    {
        if ((*iterator_a)->index < (*iterator_b)->index)
        {
            newList->push_back(*iterator_a);
            iterator_a++;
        }
        else if ((*iterator_a)->index == (*iterator_b)->index)
        {
            term *newTerm = new term;
            int newCoefficients = (*iterator_a)->coefficients - (*iterator_b)->coefficients;
            if (newCoefficients == 0)
            {
                iterator_a++;
                iterator_b++;
                continue;
            }
            newTerm->coefficients = newCoefficients;
            newTerm->index = (*iterator_a)->index;
            newList->push_back(newTerm);
            iterator_a++;
            iterator_b++;
        }
        else
        {
            // 这里要加个负号
            term *newTerm = new term;
            newTerm->coefficients = -(*iterator_b)->coefficients;
            newTerm->index = (*iterator_b)->index;
            newList->push_back(newTerm);
            iterator_b++;
        }
    }

    // 输入剩余
    for (; iterator_a != a->end(); iterator_a++)
    {
        if ((*iterator_a)->coefficients) // 不为零
            newList->push_back(*iterator_a);
    }

    for (; iterator_b != b->end(); iterator_b++)
    {
        if ((*iterator_b)->coefficients) // 不为零
        {
            // 加个负号
            term *newTerm = new term;
            newTerm->coefficients = -(*iterator_b)->coefficients;
            newTerm->index = (*iterator_b)->index;
            newList->push_back(newTerm);
        }
    }

    return newList;
}

// 先乘后加
list<term *> *multiply(list<term *> *a, list<term *> *b)
{
    // 新数组
    list<term *> *newList = new list<term *>;

    for (list<term *>::iterator i = a->begin(); i != a->end(); i++)
    {
        list<term *> *tempList = new list<term *>;

        if ((*i)->coefficients == 0)
            continue;

        for (list<term *>::iterator i2 = b->begin(); i2 != b->end(); i2++)
        {
            if ((*i2)->coefficients == 0)
                continue;

            term *tempTerm = new term;
            tempTerm->coefficients = (*i)->coefficients * (*i2)->coefficients;

            if (tempTerm->coefficients == 0)
            {
                delete tempTerm;
                continue;
            }
            tempTerm->index = (*i)->index + (*i2)->index;
            tempList->push_back(tempTerm);
            // show(tempList);
        }
        newList = add(newList, tempList);
        // show(newList);
        delete tempList;
    }
    return newList;
}

int run()
{
    // 输入尝试次数
    int numberOfAttemps;
    cin >> numberOfAttemps;

    for (int i = 0; i < numberOfAttemps; i++)
    {
        // 多项式项数, 系数, 指数
        int numberOfPolynomialTerms, coefficients, index;

        // 存储容器
        list<term *> a, b;

        // 输入多项式项数
        cin >> numberOfPolynomialTerms;

        // 第一个多项式
        for (int i2 = 0; i2 < numberOfPolynomialTerms; i2++)
        {
            // 输入系数和指数
            cin >> coefficients >> index;

            // 构造存储单元
            term *newTerm = new term;

            if (!newTerm)
            {
                cout << "error" << endl;
                return 0;
            }
            newTerm->coefficients = coefficients;
            newTerm->index = index;

            // 存储
            a.push_back(newTerm);
        }

        // 输入多项式项数
        cin >> numberOfPolynomialTerms;

        // 第二个多项式
        for (int i2 = 0; i2 < numberOfPolynomialTerms; i2++)
        {
            // 输入系数和指数
            cin >> coefficients >> index;

            // 构造存储单元
            term *newTerm = new term;

            if (!newTerm)
            {
                cout << "error" << endl;
                return 0;
            }

            newTerm->coefficients = coefficients;
            newTerm->index = index;

            // 存储
            b.push_back(newTerm);
        }

        // 运算
        list<term *> *newList = add(&a, &b);
        show(newList);
        newList = sub(&a, &b);
        show(newList);
        newList = multiply(&a, &b);
        show(newList);
    }
    return 1;
}

int main()
{
    run();
    return 1;
}