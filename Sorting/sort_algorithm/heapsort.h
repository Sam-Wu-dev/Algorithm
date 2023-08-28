#include <iostream>
#include <algorithm>
using namespace std;
template <typename I>
void max_heapify(I begin, I start, I end)
{
    // 1. find the biggest child as son
    // 2. swap dad and son and let son become new dad if son is bigger than dad
    // 3. recursively do 1. and 2. until it's a max heap
    auto dad = start;
    auto son = begin + 2 * (dad - begin) + 1;
    while (son < end)
    {
        // step 3.
        if (son + 1 < end && *(son + 1) > *son)
        {
            // step 1.
            son++;
        }
        if (*dad >= *son)
        {
            return;
        }
        else
        {
            // step 2.
            swap(*dad, *son);
            dad = son;
            son = begin + 2 * (dad - begin) + 1;
        }
    }
}
template <typename I>
void heap_sort(I begin, I end)
{
    // 1. create a max heap (A max heap is a complete binary tree that every node in the tree is bigger than it's children.).
    // 2. keep taking out the max element and reheapify the tree.
    int size = end - begin;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        // step 1.
        // we use array to implement max heap
        // the left child of an element with index i is 2 * i +1
        // the right child of an element with index i is 2 * i +2
        // the parent of an element with index i is ( i - 1 ) / 2
        max_heapify(begin, begin + i, end);
    }
    for (auto i = end - 1; i > begin; i--)
    {
        // step 2.
        swap(*begin, *i);
        max_heapify(begin, begin, i);
    }
}
