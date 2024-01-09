#include "../binomialHeap.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    unique_ptr<BinomialHeap> test = make_unique<BinomialHeap>(vector<int>{2, 20, 12, 30, 21, 22, 23, 0, 1, 5}, [](int a, int b)
                                                              { return a <= b; });
    unique_ptr<BinomialHeap> test2 = make_unique<BinomialHeap>(vector<int>{1, 4, 17, 39, 28, 20, 32, 87, 65, 43}, [](int a, int b)
                                                               { return a <= b; });
    test->merge(*test2);
    while (!test->empty())
    {
        auto top = test->deleteTop();
        if (top.has_value())
        {
            cout << top.value() << endl;
        }
    }
}