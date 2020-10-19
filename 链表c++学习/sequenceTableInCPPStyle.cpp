#include <iostream>
#include <sstream>

template<class T>
struct Seq
{

    Seq(int capacity = 10) : length(0), capacity(capacity), arr(new T[capacity]) // 成员变量赋值
    {
        
    }

    void insert(int index, T value)
    {
        checkRange(index);
        checkCapacity(length + 1);

        for (int i = length; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }

        arr[index] = value;

        length++;
    }

    void remove(int index)
    {
        checkRange(index);

        for (int i = index; i < length - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        length--;
    }

    void add(T value)
    {
        checkCapacity(length + 1);
        arr[length] = value;
        length++;
    }

    T& operator[](int index) // 重载运算符 可以通过[]像数组一样访问
    {
        checkRange(index);
        return arr[index];
    }

    int getLength()
    {
        return length;
    }

    ~Seq()  // 析构函数
    {
        delete[] arr;
    }

private:
    T* arr;
    int length;
    int capacity;

    inline void checkRange(int index)
    {
        if (index >= length || index < 0)
        {
            std::stringstream message;
            message << "数组越界:" << index;
            throw std::out_of_range(message.str());
        }
    }

    void checkCapacity(int size)
    {
        if (size > capacity)
        {
            int newCapacity = capacity * 2;
            T* oldArr = arr;
            arr = new T[newCapacity];
            for (int i = 0; i < length; i++)
            {
                arr[i] = oldArr[i];
            }
            capacity = newCapacity;
            //std::cout << "扩容" << capacity << std::endl;
        }
    }
};

int main()
{
    Seq<double> seq(2);
    seq.add(5.1);
    seq.add(6.1);
    seq.add(7.1);
    seq.add(7.1);
    seq.remove(3);
    seq.insert(1, 9.1);

    try
    {
        seq[-1] = 5.1;
    }
    catch (std::out_of_range error)
    {
        std::cout << error.what() << std::endl;
    }

    for (int i = 0; i < seq.getLength(); i++)
    {
        std::cout << seq[i] << std::endl;
    }
}