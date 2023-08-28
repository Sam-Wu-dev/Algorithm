#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void quick_sort(vector<int> &arr, int begin, int end)
{
    if (end - begin < 2)
        return;
    int pivot = arr[begin];
    int j = begin; // 最後一個<=pivot的index
    for (int i = begin + 1; i < end; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(arr[i], arr[j + 1]);
            j++;
        }
        else
        {
        }
    }
    swap(arr[begin], arr[j]);
    quick_sort(arr, begin, j);
    quick_sort(arr, j + 1, end);
}

int main()
{
    vector<int> arr{4, 3, 5, 4, 1, 2, 6, 9, 8, 5, 3, 6, 5, 4, 7, 5, 1, 2, 3, 6};
    quick_sort(arr, 0, arr.size());
    for (auto i : arr)
    {
        cout << i << " ";
    }
}