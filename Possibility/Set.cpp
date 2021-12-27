#include "Set.h"

using namespace std;
Set::Set(vector<string> input_elements){
    elements=input_elements;
}

vector<string> Set::Get_elements(){
    return elements;
}

