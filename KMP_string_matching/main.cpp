#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector<int> Failure_Function2(string &p)
{ // O(p)
    vector<int> failure_function(p.size(), -1);
    for (int i = 1; i < p.size(); i++)
    {
        int j = failure_function[i - 1];
        while (p[i] != p[j + 1] && j != -1)
        {
            j = failure_function[j];
        }
        if (p[i] == p[j + 1])
        {
            failure_function[i] = j + 1;
        }
    }
    return failure_function;
}
bool KMP(vector<int> &failure_function, string &s, string &p)
{
    int i = 0, j = 0;
    while (i < s.size() && j < p.size())
    {
        if (s[i] == p[j])
        {
            i++;
            j++;
        }
        else if (j == 0)
        {
            i++;
        }
        else
        {
            j = failure_function[j - 1] + 1;
        }
    }
    if (j == failure_function.size())
    {
        return 1;
    }
    return 0;
}
int main()
{
    string s = "abbababababbbababbabaaabbababaa";
    string p = "ababbababaa";
    vector<int> failure_function = Failure_Function2(p);
    for (auto i : s)
    {
        cout << setw(2) << i;
    }
    cout << endl;
    for (auto i : failure_function)
    {
        cout << setw(2) << i;
    }
    cout << endl;
    for (auto i : p)
    {
        cout << setw(2) << i;
    }
    cout << endl;
    bool check = KMP(failure_function, s, p);
    if (check)
    {
        cout << "p為s的子字串" << endl;
    }
    else
    {
        cout << "p不為s的子字串" << endl;
    }
}