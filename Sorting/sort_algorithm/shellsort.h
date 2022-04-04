#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
template<typename I>
void shell_sort(I begin,I end){
    int n=end-begin;
    vector<int> gap;
    int counter=0;
    while(n>0){
        gap.push_back(pow(2,counter++));
        n/=2;
    }
    reverse(gap.begin(),gap.end());
    for(auto i:gap){
        for(auto j=begin;j<begin+i;j++){
            for(auto k=j+i;k<end;k+=i){
                auto key=*k;
                auto now=k-i;
                while(now>=begin&&key<=*now){
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