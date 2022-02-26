#include <iostream>
#include <algorithm>
using namespace std;
template <typename I>
void quick_sort(I begin, I end){
    // Choose a element to be pivot, then divide the elements into two parts, one is smaller the pivot, the other one is bigger.
    // Recursiviely do it to the two parts until it's sorted.
    if (begin >= end)
        return;
    auto pivot = *begin;// choose the first element as the pivot
    auto i = begin;// 1. elements on the left side of i and *i should be smaller or equal to pivot
    auto j = end;  // 2. elements on the right side of j and *j should be bigger or equal to pivot
    do{
        do{i++;}while(*i<pivot);// find the first i that *i is bigger then pivot
        do{j--;}while(*j>pivot);// find the first j that *j is smaller then pivot
        if(i<j){
            // *i should be bigger then pivot now and *j should be smaller then pivot now
            swap(*i,*j);//so we swap *i and *j to keep 1. and 2. are true
        }
    }while(i<j);
    swap(*j, *begin);
    quick_sort(begin, j);
    quick_sort(j + 1, end);
}