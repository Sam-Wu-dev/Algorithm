#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> price, weight, volume;
    int N, W, V;
    cin >> N >> W >> V;
    price.resize(N + 1);
    weight.resize(N + 1);
    volume.resize(N + 1);
    vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(W + 1, vector<int>(V + 1)));
    vector<vector<vector<bool>>> record(N + 1, vector<vector<bool>>(W + 1, vector<bool>(V + 1)));
    for (int i = 1; i <= N; i++)
    {
        cin >> price[i];
    }
    for (int i = 1; i <= N; i++)
    {
        cin >> weight[i];
    }
    for (int i = 1; i <= N; i++)
    {
        cin >> volume[i];
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            for (int k = 0; k <= V; k++)
            {
                if ((j - weight[i] >= 0) && (k - volume[i] >= 0))
                {
                    if (dp[i - 1][j - weight[i]][k - volume[i]] + price[i] > dp[i - 1][j][k])
                    {
                        dp[i][j][k] = dp[i - 1][j - weight[i]][k - volume[i]] + price[i];
                        record[i][j][k] = true;
                    }
                    else
                    {
                        dp[i][j][k] = dp[i - 1][j][k];
                        record[i][j][k] = false;
                    }
                }
                else
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    record[i][j][k] = false;
                }
            }
        }
    }
    vector<int> temp;
    cout << dp[N][W][V] << endl;
    while (N > 0)
    {
        if (record[N][W][V])
        {
            temp.push_back(N);
            W -= weight[N];
            V -= volume[N];
        }
        N--;
    }
    cout << temp.size() << endl;
    cout << "(";
    for (int i = temp.size() - 1; i > 0; i--)
    {
        cout << temp[i] << ",";
    }
    cout << temp[0] << ")";
}