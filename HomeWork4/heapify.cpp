#include <iostream>
using namespace std;

class max_heap
{
public:
    static const int CAPACITY = 100;
    max_heap()
    {
        size = CAPACITY;
        for (std::size_t i = 0; i < CAPACITY; i++)
        {
            data[i] = 0;
        }
    }
    max_heap(int arr[], std::size_t s)
    {
        size = s;
        for (std::size_t i = 0; i < CAPACITY; i++)
        {
            data[i] = 0;
        }
        for (std::size_t i = 0; i < size; i++)
        {
            data[i] = arr[i];
        }
    }
    std::size_t heap_size()
    {
        return size;
    }
    void insert(int val)
    {
        for (std::size_t i = 0; i < size; i++)
        {
            if (data[i] == 0)
            {
                data[i] = val;
                break;
            }
        }
        for (std::size_t i = 0; i < size; i++)
        {
            while (data[(i - 1) / 2] < data[i])
            {
                int temp = data[i];
                data[i] = data[(i - 1) / 2];
                data[(i - 1) / 2] = temp;
                i = 0;
            }
        }
    }
    bool full()
    {
        int count = 0;
        for (std::size_t i = 0; i < size; i++)
        {
            if (data[i] != 0)
            {
                count++;
            }
        }
        return (count == size);
    }
    void print()
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] != 0)
                cout << data[i] << " ";
        }
        cout << endl;
    }

private:
    int data[CAPACITY];
    std::size_t size;
};

int main()
{
    int value;
    int arr[10];
    int size = 10;
    cout << "What integers do you have?" << endl;
    for (std::size_t i = 0; i < 10; i++)
    {
        cin >> value;
        arr[i] = value;
    }
    max_heap p1(arr, size);
    cout << "What new values do you want to be added to the heap? (Input -1 if you're finished)" << endl;
    cin >> value;
    while (value != -1)
    {
        if (p1.full())
        {
            cout << "Sorry! You're heap is already full!" << endl;
            break;
        }
        p1.insert(value);
        cin >> value;
    }
    p1.print();

    return 0;
}
