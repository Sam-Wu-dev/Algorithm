#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
template<typename I>
void selection_sort(I begin,I end){
    // Sort the numbers by keep finding the smallest number until it's all sorted.
    for(auto i=begin;i<end;i++){
        auto smallest=i;
        for(auto j=i;j<end;j++){
            // Find the smallest number in the unsorted area
            if(*j<*smallest){
                smallest=j;
            }
        }
        swap(*smallest,*i);// Swap the smallest number and the leftest number in the unsorted area
    }
}