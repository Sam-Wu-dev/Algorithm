#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define maxf 10001
using namespace std;

int findMin(vector<float> &vec, vector<bool> &record)
{
    int index = 1;
    float val = maxf;
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < val && !record[i])
        {
            index = i;
            val = vec[i];
        }
    }
    record[index] = true;
    return index;
}

int main()
{
    // Dijastra's algorithm
    int n, m, s;
    cin >> n >> m;
    vector<vector<float>> table(n + 1, vector<float>(n + 1, maxf));
    vector<float> dis(n + 1, maxf);
    vector<int> parent(n + 1);
    vector<bool> record(n + 1, false);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        float c;
        cin >> a >> b >> c;
        table[a][b] = c;
        table[b][a] = c;
    }
    for (int i = 1; i <= n; i++)
    {
        table[i][i] = 0;
    }
    cin >> s;
    for (int j = 1; j <= n; j++)
    {
        dis[j] = table[s][j];
        parent[j] = s;
    }
    parent[s] = 0;
    record[s] = true;
    for (int k = 1; k < n; k++)
    {

        int min_v = findMin(dis, record);
        for (int j = 1; j <= n; j++)
        {
            if (dis[min_v] + table[min_v][j] < dis[j])
            {
                dis[j] = table[min_v][j] + dis[min_v];
                parent[j] = min_v;
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        cout << dis[i] << " ";
    }
    cout << dis[n] << endl;
    for (int i = 1; i < n; i++)
    {
        cout << parent[i] << " ";
    }
    cout << parent[n] << endl;
    return 0;
}