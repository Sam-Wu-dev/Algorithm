#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> longest_increasing_subsequence(vector<int> &arr)
{
    if (arr.empty())
        return {};

    vector<int> dp(arr.size(), 1);
    int max_length = 1;
    int max_index = 0;

    // Compute the LIS values in a bottom-up manner
    for (int i = 1; i < arr.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
                if (max_length < dp[i])
                {
                    max_length = dp[i];
                    max_index = i;
                }
            }
        }
    }

    // Reconstruct the longest increasing subsequence
    vector<int> lis;
    int k = max_index;
    int current_length = max_length;
    while (k >= 0)
    {
        if (dp[k] == current_length)
        {
            lis.push_back(arr[k]);
            current_length--;
        }
        k--;
    }
    reverse(lis.begin(), lis.end()); // LIS is constructed in reverse, so reverse it

    return lis;
}

int main()
{
    vector<int> temp = {3, 10, 2, 1, 20};
    vector<int> ans = longest_increasing_subsequence(temp);
    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}