#include <iostream>
#include <climits>
using namespace std;

void insertionSort(int arr[], int size);
void selectionSort(int arr[], int size);

int main()
{
    int arr[] = {1, 3, 33, 221, 43, 9, 6};
    int size = 7;
    insertionSort(arr, size);
    return 0;
}

void insertionSort(int arr[], int size)
{
    // loop through array
    int j = 0;
    int placeHolder = 0;
    for (int i = 1; i < size; i++)
    {
        j = i - 1;
        placeHolder = arr[i];
        while (j >= 0 && arr[j] > placeHolder)
        {
            for (int k = 0; k < size; k++)
            {
                cout << arr[k] << ", ";
            }
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = placeHolder;
    }
}
void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}
