#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define maxf 10001
using namespace std;

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
    priority_queue<pair<int, float>, vector<pair<int, float>>, greater<pair<int, float>>> pq;
    pq.push({s, dis[s]});
    while (!pq.empty())
    {
        auto min_v = pq.top().first;
        pq.pop();
        if (record[min_v])
            continue;
        record[min_v] = true;
        for (auto edge : edges[min_v])
        {
            int target = edge.first;
            if (record[target])
                continue;
            if (dis[min_v] + edge.second < dis[target])
            {
                dis[target] = dis[min_v] + edge.second;
                pq.push({target, dis[target]});
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
// Time complexity O((E+V)logV)