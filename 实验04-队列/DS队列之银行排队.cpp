#include <iostream>
#include <queue>
using namespace std;

float getAverageTime(queue<int> *myQueue)
{
    float sum = 0;
    int head;
    int len = myQueue->size();

    while (!myQueue->empty())
    {
        head = myQueue->front();
        sum += head;
        myQueue->pop();
    }

    return sum / len;
}

void run()
{
    int numberOfClients;
    cin >> numberOfClients;

    // declare a queue
    queue<int> queueA, queueB, queueC;
    auto str = new char[numberOfClients];

    char typeOfClients;
    for (int i = 0; i < numberOfClients; i++)
    {
        cin >> typeOfClients;
        str[i] = typeOfClients;
    }

    int costTimeOfEachClients;
    for (int i = 0; i < numberOfClients; i++)
    {
        cin >> costTimeOfEachClients;
        switch (str[i])
        {
        case 'A':
            queueA.push(costTimeOfEachClients);
            break;
        case 'B':
            queueB.push(costTimeOfEachClients);
            break;
        case 'C':
            queueC.push(costTimeOfEachClients);
            break;
        default:
            cout << "error";
            break;
        }
    }

    cout << getAverageTime(&queueA) << endl;
    cout << getAverageTime(&queueB) << endl;
    cout << getAverageTime(&queueC) << endl;
}

int main()
{
    run();
    return 0;
}
