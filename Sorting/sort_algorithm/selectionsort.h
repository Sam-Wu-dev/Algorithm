#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
template<typename I>
void selection_sort(I begin,I end){
    // Sort the elements by keep finding the smallest element until it's all sorted.
    for(auto i=begin;i<end;i++){
        auto smallest=i;
        for(auto j=i;j<end;j++){
            // Find the smallest element in the unsorted area
            if(*j<*smallest){
                smallest=j;
            }
        }
        swap(*smallest,*i);// Swap the smallest element and the leftest element in the unsorted area
    }
}