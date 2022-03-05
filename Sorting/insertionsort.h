#include <iostream>
#include <algorithm>
using namespace std;
template<typename I>
void insertion_sort(I begin,I end){
    // Insert an unsorted element into the right place of sorted part.
    // keep doing that until all the elements are sorted.
    I left=begin+1;
    I right=end;
    while(left!=right){
        // typename I::value_type key=*left;
        auto key=*left;// the unsorted element
        I now=left-1;
        while(now>=begin&&key<*now){
            // find the biggest elements that is smaller then the unsorted element while pushing every elements to the right by 1 
            *(now+1)=*now;
            now--;
        }
        *(now+1)=key;
        left++;
    }   
}