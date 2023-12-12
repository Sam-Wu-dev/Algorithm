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
    vector<float> dis(n + 1, maxf);
    vector<int> parent(n + 1);
    vector<bool> record(n + 1, false);
    vector<vector<pair<int, float>>> edges(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        float c;
        cin >> a >> b >> c;
        edges[a].push_back({b, c});
        edges[b].push_back({a, c});
    }
    cin >> s;
    parent[s] = 0;
    dis[s] = 0;
    for (int k = 0; k < n; k++)
    {
        int min_v = findMin(dis, record);
        for (auto edge : edges[min_v])
        {
            int target = edge.first;
            if (record[target])
                continue;
            if (dis[min_v] + edge.second < dis[target])
            {
                dis[target] = dis[min_v] + edge.second;
                parent[target] = min_v;
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
// Time complexity O(n^2)