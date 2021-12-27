#include <iostream>
#include <string> 
#include <vector>
#include "Set.h"

using namespace std;


int main(){
    vector<string> elements;
    for(int i=0;i<5;i++){
        elements.push_back(to_string(i));
    }
    Set test(elements);
    for(auto i: test.Get_elements()){
        cout<< i<<endl;
    }
}
