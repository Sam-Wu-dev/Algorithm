#include <iostream>
#include <vector>
#include <list>
//#include <ctime>
#include <chrono>
#include <limits>
#include <random> /* 亂數相關函數 */
#include "sort_algorithm/insertionsort.h"
#include "sort_algorithm/quicksort.h"
#include "sort_algorithm/selectionsort.h"
#include "sort_algorithm/mergesort.h"
#include "sort_algorithm/heapsort.h"
#include "sort_algorithm/radixsort.h"
#include "sort_algorithm/shellsort.h"
using namespace std;

int vector_size=10000;
template<typename C>
void print(C c){
    for(auto i=c.begin();i!=c.end();i++){
        cout<<*i<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> vec;
    random_device rd;
    mt19937 generator( rd() );// 梅森旋轉演算法 
    uniform_int_distribution<int> uid(0,INT_MAX);
    for(int i=0;i<vector_size;i++){
        vec.push_back(uid(generator));
    }
    // insertion_sort(vec.begin(),vec.end());
    auto start = chrono::steady_clock::now();
    quick_sort(vec.begin(),vec.end());
    // selection_sort(vec.begin(),vec.end());
    // merge_sort(vec.begin(),vec.end());
    // heap_sort(vec.begin(),vec.end());
    // radix_sort(vec.begin(),vec.end());
    // srand( time(nullptr) );
    // shell_sort(vec.begin(),vec.end(),{8,4,2,1});
    auto elasped = chrono::steady_clock::now() - start;
    auto execution_time=chrono::duration_cast<chrono::nanoseconds>(elasped).count();
    cout<<vec.size()<<endl;
    cout<<execution_time<<endl;
}