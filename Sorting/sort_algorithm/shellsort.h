#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
template<typename I>
void shell_sort(I begin,I end){
    vector<int> gap{32,16,8,4,2,1};
    for(auto i:gap){
        for(auto j=begin;j<begin+i;j++){
            for(auto k=j+i;k<end;k+=i){
                auto key=*k;
                auto now=k-i;
                while(key<=*now&&now>=begin){
                    swap(*now,*(now+i));
                    now-=i;
                }
            }
        }
    }
}
template<typename I>
void shell_sort(I begin,I end,initializer_list<int> li){
    vector<int> gap(li);
    for(auto i:gap){
        for(auto j=begin;j<begin+i;j++){
            for(auto k=j+i;k<end;k+=i){
                auto key=*k;
                auto now=k-i;
                while(key<=*now&&now>=begin){
                    swap(*now,*(now+i));
                    now-=i;
                }
            }
        }
    }
}