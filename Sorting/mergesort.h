#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template<typename I>
void merge_sort(I begin,I end){
    // Divide and couquer
    // 1. Divide the elements into two parts form middle and then sort both parts 
    // 2. Merge them together by keep comparing the smallest elements of both parts 
    int size=end-begin;
    if(size<=1){
        return;
    }
    auto middle=begin+size/2;// find the middle point
    merge_sort(begin,middle);// 1.
    merge_sort(middle,end);
    auto i=begin;
    auto j=middle;
    vector<typename std::iterator_traits<I>::value_type> temp;
    temp.reserve(size);
    while(i!=middle&&j!=end){
        // 2.
        if(*i<*j){
            temp.push_back(*i);
            i++;
        }
        else{
            temp.push_back(*j);
            j++;
        }
    }
    if(j==end){
        for(;i!=middle;i++){
            temp.push_back(*i);
        }
    }else{
        for(;j!=end;j++){
            temp.push_back(*j);
        }
    }
    for(int i=0;i<end-begin;i++){
        *(begin+i)=temp[i];
    }
}