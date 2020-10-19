#include <iostream>
#include <stack>
#include <queue>
#include <math.h>
using namespace std;

stack<int> *integralPartProcessor(int demicalFormOfIntegralPart, int numberSystem)
{
    int remainder; // 余数
    stack<int> *binaryFormOfIntegralPart = new stack<int>;

    while (true)
    {
        remainder = demicalFormOfIntegralPart % numberSystem;
        demicalFormOfIntegralPart = demicalFormOfIntegralPart / numberSystem;
        binaryFormOfIntegralPart->push(remainder);

        if (demicalFormOfIntegralPart == 0)
            break;
    }
    return binaryFormOfIntegralPart; // 输出时需要倒叙输出
}

queue<int> *fractionalPartProcessor(double demicalFormOfFractionalPart, int numberSystem)
{
    int integer; // 取整后的数
    queue<int> *binaryFormOfFractionalPart = new queue<int>;

    while (true)
    {
        demicalFormOfFractionalPart = demicalFormOfFractionalPart * numberSystem;
        integer = demicalFormOfFractionalPart / 1;                          // 向下取整（整数部分）
        demicalFormOfFractionalPart = fmod(demicalFormOfFractionalPart, 1); // 取小数部分
        binaryFormOfFractionalPart->push(integer);

        if (demicalFormOfFractionalPart == 0 || binaryFormOfFractionalPart->size() == 3) // 精确到小数点后三位
            break;
    }

    return binaryFormOfFractionalPart;
}

void demical2binary(double demicalForm, int numberSystem)
{
    int integralPart = demicalForm / 1.0;         // 整数部分
    double fractionalPart = fmod(demicalForm, 1); // 小数部分

    stack<int> *binaryFormOfIntegralPart = integralPartProcessor(integralPart, numberSystem);
    queue<int> *binaryFormOfFractionalPart = fractionalPartProcessor(fractionalPart, numberSystem);

    // 输出整数
    while (!binaryFormOfIntegralPart->empty())
    {
        int topNumber = binaryFormOfIntegralPart->top();
        switch (topNumber)
        {
        case 10:
            cout << 'A';
            break;
        case 11:
            cout << 'B';
            break;
        case 12:
            cout << 'C';
            break;
        case 13:
            cout << 'D';
            break;
        case 14:
            cout << 'E';
            break;
        case 15:
            cout << 'F';
            break;
        default:
            cout << topNumber;
            break;
        }
        binaryFormOfIntegralPart->pop();
    }

    cout << '.' << flush;

    // 后续补零
    int zeroNumber = 3 - binaryFormOfFractionalPart->size();

    // 输出小数
    int frontNumber;
    while (!binaryFormOfFractionalPart->empty())
    {
        frontNumber = binaryFormOfFractionalPart->front();
        switch (frontNumber)
        {
        case 10:
            cout << 'A';
            break;
        case 11:
            cout << 'B';
            break;
        case 12:
            cout << 'C';
            break;
        case 13:
            cout << 'D';
            break;
        case 14:
            cout << 'E';
            break;
        case 15:
            cout << 'F';
            break;
        default:
            cout << frontNumber;
            break;
        }
        binaryFormOfFractionalPart->pop();
    }

    for (int i = 0; i < zeroNumber; i++)
        cout << '0';
    cout << '\n';
}

void run()
{
    int tryTimes, numberSystem;
    cin >> tryTimes;

    double demicalForm;
    for (int i = 0; i < tryTimes; i++)
    {
        cin >> demicalForm >> numberSystem;
        demical2binary(demicalForm, numberSystem);
    }
}

int main()
{
    run();
    return 0;
}