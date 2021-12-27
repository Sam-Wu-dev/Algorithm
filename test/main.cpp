#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> test(5,4);
    vector<int> testt(5,3);
    vector<int>& link=test;
    link=testt;
    link.push_back(6);
    for(auto i:link){
        cout<<i<<endl;
    }
}