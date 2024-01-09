#include "../fibonacciHeap.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    vector<int> a{2, 20, 12, 30, 21, 22, 23, 0, 1, 5};
    vector<int> b{1, 4, 17, 39, 28, 20, 32, 87, 65, 43};
    unordered_map<int, shared_ptr<FibonacciNode>> nodes1;
    unordered_map<int, shared_ptr<FibonacciNode>> nodes2;
    unique_ptr<FibonacciHeap> test1 = make_unique<FibonacciHeap>([](int a, int b)
                                                                 { return a <= b; });
    unique_ptr<FibonacciHeap> test2 = make_unique<FibonacciHeap>([](int a, int b)
                                                                 { return a <= b; });
    for (auto i : a)
    {
        nodes1[i] = test1->insert(i);
    }
    for (auto i : b)
    {
        nodes2[i] = test2->insert(i);
    }
    auto top = test1->getTop();
    if (top.has_value())
        cout << top.value() << endl;
    test1->levelUpKey(nodes1[20], -5);
    top = test1->getTop();
    if (top.has_value())
        cout << top.value() << endl;
    test1->merge(*test2);
    while (!test1->empty())
    {
        auto top = test1->deleteTop();
        if (top.has_value())
        {
            cout << top.value() << endl;
        }
    }
}