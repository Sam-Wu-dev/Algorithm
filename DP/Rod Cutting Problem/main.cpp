#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    int k;
    cin >> k;
    vector<int> rods(k + 1);
    // 鐵條長度為i
    // 鐵條價格為rods[i]
    for (int i = 1; i <= k; i++)
    {
        cin >> rods[i];
    }
    vector<int> dp(k + 1);
    vector<int> s(k + 1);
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (rods[j] + dp[i - j] > dp[i])
            {
                dp[i] = rods[j] + dp[i - j];
                s[i] = j;
            }
        }
    }
    vector<int> records;
    int temp = k;
    while (s[temp] > 0)
    {
        records.push_back(s[temp]);
        temp -= s[temp];
    }
    cout << dp[k] << endl;
    cout << records.size() << endl;
    cout << k << "=";
    for (int i = 0; i < records.size() - 1; i++)
    {
        cout << records[i] << "+";
    }
    cout << records[records.size() - 1];
}