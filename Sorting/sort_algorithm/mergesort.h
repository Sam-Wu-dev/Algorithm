#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template <typename I>
void merge(I left_begin, I left_end, I right_begin, I right_end)
{
    I left_temp = left_begin;
    I right_temp = right_begin;
    I temp = left_begin;
    while (left_temp != left_end && right_temp != right_end)
    {
        if (*left_temp < *right_temp)
        {
            *temp = *left_temp;
            left_temp++;
        }
        else
        {
            *temp = *right_temp;
            right_temp++;
        }
        temp++;
    }
    while (left_temp != left_end)
    {
        *temp = *left_temp;
        left_temp++;
        temp++;
    }
    while (right_temp != right_end)
    {
        *temp = *right_temp;
        right_temp++;
        temp++;
    }
}
template <typename I>
void merge_sort(I begin, I end)
{
    // Divide and couquer
    // 1. Divide the elements into two parts form middle and then sort both parts
    // 2. Merge them together by keep comparing the smallest elements of both parts
    int size = end - begin;
    if (size <= 1)
    {
        return;
    }
    auto middle = begin + size / 2; // find the middle point
    merge_sort(begin, middle);      // step 1.
    merge_sort(middle, end);
    merge(begin, middle, middle, end); // step 2.
}