#include <iostream>
#include <vector>
using namespace std;
int firstone(vector<vector<bool>> &dp, int i, int size)
{
    int first = -1;
    for (int j = 1; j < size; j++)
    {
        if (dp[i][j])
        {
            first = j;
            break;
        }
    }
    return first;
}
bool isMatch(string s, string p)
{
    int size = s.size() + 1;
    vector<vector<bool>> dp;
    for (int i = 0; i <= p.size(); i++)
    {
        vector<bool> temp(size, 0);
        temp[0] = 1;
        dp.push_back(temp);
    }
    int first = 0;
    for (int i = 1; i < p.size() + 1; i++)
    {
        if (p[i-1] == '*')
        {
            for (int j = first ; j < size; j++)
            {
                dp[i][j] = 1;
            }
            continue;
        }
        bool dot = (p[i-1] == '.');
        for (int j = first + 1; j < size; j++)
        {
            if (dp[i - 1][j - 1] && (dot || s[j-1] == p[i-1]))
            {
                dp[i][j] = 1;
            }
        }
        first = firstone(dp, i, size);
        if (first == -1)
        {
            break;
        }
    }
    for(auto i:dp){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    return dp[p.size()][s.size()];
}

int main()
{
    string s = "ab";
    string p = "a.*";
    while(cin>>s>>p)
    cout << isMatch(s, p) << endl;
}