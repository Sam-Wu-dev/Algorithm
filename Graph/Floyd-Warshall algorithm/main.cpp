#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define maxf 10000001
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<float>> table(n + 1, vector<float>(n + 1, maxf));
    for (int i = 0; i < m; i++)
    {
        int a, b;
        float c;
        cin >> a >> b >> c;
        table[a][b] = c;
    }
    for (int i = 1; i <= n; i++)
    {
        table[i][i] = 0;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (table[i][k] + table[k][j] < table[i][j])
                {
                    table[i][j] = table[i][k] + table[k][j];
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (table[i][j] != maxf)
            {
                cout << table[i][j] << " ";
            }
            else
            {
                cout << 'N' << " ";
            }
        }
        if (table[i][n] != maxf)
        {
            cout << table[i][n] << endl;
        }
        else
        {
            cout << 'N' << endl;
        }
    }
    return 0;
}
// Time complexity O(n^3)