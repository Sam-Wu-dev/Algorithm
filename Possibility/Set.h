#ifndef Set_h
#define Set_h
#include <iostream>
#include <vector>
using namespace std;

class Set
{
private:
    vector<string> elements;

public:
    Set(vector<string>);
    vector<string> Get_elements();
};

#endif

