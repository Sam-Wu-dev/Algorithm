// Time Complexity
// O(Max-Digit*(Radix-size+n))
#include <iostream>
#include <vector>
using namespace std;
template <typename I>
void radix_sort(I begin, I end)
{
    using t = typename I::value_type;
    t max = *begin;
    for (auto i = begin; i < end; i++)
    {
        if (*i > max)
        {
            max = *i;
        }
    }
    t n = 1;
    while (max > 9)
    {
        max /= 10;
        n *= 10;
    }
    vector<vector<t>> radix(10);
    t r = 1;
    while (r <= n)
    {
        for (auto i = begin; i < end; i++)
        {
            int key = ((*i) / r) % 10;
            radix[key].push_back(*i);
        }
        auto temp = begin;
        for (auto i : radix)
        {
            for (auto j : i)
            {
                *temp = j;
                temp++;
            }
        }
        for (int i = 0; i < 10; i++)
        {
            radix[i].clear();
        }
        r *= 10;
    }
    // cout<< r <<endl;
}