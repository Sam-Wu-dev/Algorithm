#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <limits>
#include <random> 
#include "sort_algorithm/insertionsort.h"
#include "sort_algorithm/quicksort.h"
#include "sort_algorithm/selectionsort.h"
#include "sort_algorithm/mergesort.h"
#include "sort_algorithm/heapsort.h"
#include "sort_algorithm/radixsort.h"
#include "sort_algorithm/shellsort.h"
using namespace std;

template<typename C>
void print(C c){
    for(auto i=c.begin();i!=c.end();i++){
        cout<<*i<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> vec_size{10000,50000,100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000};
    for(auto size:vec_size){
        vector<int> vec;
        random_device rd;
        mt19937 generator( rd() );// 梅森旋轉演算法 
        uniform_int_distribution<int> uid(0,INT_MAX);
        for(int i=0;i<size;i++){
            vec.push_back(uid(generator));
        }
        auto start = chrono::steady_clock::now();
        // insertion_sort(vec.begin(),vec.end());
        // quick_sort(vec.begin(),vec.end());
        // selection_sort(vec.begin(),vec.end());
        // merge_sort(vec.begin(),vec.end());
        // heap_sort(vec.begin(),vec.end());
        // radix_sort(vec.begin(),vec.end());
        // shell_sort(vec.begin(),vec.end());
        auto elasped = chrono::steady_clock::now() - start;
        auto execution_time=chrono::duration_cast<chrono::nanoseconds>(elasped).count();
        cout<<'#'<<vec.size()<<':'<<execution_time<<endl;
    }
}