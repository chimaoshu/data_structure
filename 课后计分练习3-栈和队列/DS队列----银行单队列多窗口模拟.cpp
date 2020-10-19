#include <queue>
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

void run()
{
    queue<int> arrivalTimeStack, handleTimeStack, awaitTimeStack;
    int customerNumber;
    cin >> customerNumber;

    int userInput;
    for (int i = 0; i < customerNumber; i++)
    {
        cin >> userInput;
        arrivalTimeStack.push(userInput);

        cin >> userInput;
        handleTimeStack.push(userInput);
    }

    int windowsNumber;
    cin >> windowsNumber;

    // 存储各个窗口的空闲时间
    int *windowsFreeTime = new int[windowsNumber];
    for (int i = 0; i < windowsNumber; i++)
        windowsFreeTime[i] = 0;

    int currentTime = 0;
    while (1)
    {
        while ((!arrivalTimeStack.empty()) && currentTime >= arrivalTimeStack.front())
        {
            bool modified = false; // 进行了修改
            for (int i = 0; i < windowsNumber; i++)
            {
                if (currentTime >= windowsFreeTime[i])
                {
                    // 预计空闲时间
                    windowsFreeTime[i] = currentTime + handleTimeStack.front();

                    // 等待时间
                    awaitTimeStack.push(currentTime - arrivalTimeStack.front());

                    // 移出队列
                    arrivalTimeStack.pop();
                    handleTimeStack.pop();
                    modified = true;
                    break;
                }
            }
            // 全部窗口都没空
            if (!modified)
            {
                break;
            }
        }

        // 是否所有窗口空闲
        bool everyWindowIsFree = true;
        for (int i = 0; i < windowsNumber; i++)
        {
            if (windowsFreeTime[i] > currentTime)
                everyWindowIsFree = false;
        }

        if (!everyWindowIsFree || !arrivalTimeStack.empty())
        {
            currentTime++;
            continue;
        }

        // 所有顾客都已经离开
        // 此时的currentTime是最后完成时间
        int maxAwaitTime = awaitTimeStack.front();
        float totalAwaitTime = 0.0;
        while (!awaitTimeStack.empty())
        {
            totalAwaitTime += awaitTimeStack.front();
            if (maxAwaitTime < awaitTimeStack.front())
            {
                maxAwaitTime = awaitTimeStack.front();
            }
            awaitTimeStack.pop();
        }
        cout << fixed << setprecision(1) << totalAwaitTime / customerNumber << ' ' << maxAwaitTime << ' ' << currentTime << endl;
        return;
    }
}

int main()
{
    run();
    return 0;
}