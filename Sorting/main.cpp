#include <iostream>
#include <vector>
#include <list>
#include "insertionsort.h"
#include "quicksort.h"
#include "selectionsort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "radixsort.h"
using namespace std;

template<typename C>
void print(C c){
    for(auto i=c.begin();i!=c.end();i++){
        cout<<*i<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> vec{1,3,5,2,2,1,3,532,4,100,2,32,65,21,54,87,65,34,54,3,9,2,2,2,62,4,98,4};
    // insertion_sort(vec.begin(),vec.end());
    // quick_sort(vec.begin(),vec.end());
    // selection_sort(vec.begin(),vec.end());
    // merge_sort(vec.begin(),vec.end());
    // heap_sort(vec.begin(),vec.end());
      radix_sort(vec.begin(),vec.end());
    print(vec);
}