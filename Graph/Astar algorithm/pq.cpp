#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#define maxf 10001
#define axis pair<float, float>
using namespace std;

struct AStarNode
{
    int vertex;
    float cost;

    AStarNode(int v, float c) : vertex(v), cost(c) {}

    // Comparator for the priority queue
    bool operator>(const AStarNode &other) const
    {
        return cost > other.cost;
    }
};

float potential(axis from, axis target)
{
    return sqrt((target.first - from.first) * (target.first - from.first) + (target.second - from.second) * (target.second - from.second));
}

int main()
{
    // Dijastra's algorithm
    int n, m, s, e;
    cin >> n >> m;
    vector<float> dis(n + 1, maxf);
    vector<int> parent(n + 1);
    vector<bool> record(n + 1, false);
    vector<vector<pair<int, float>>> edges(n + 1);
    vector<axis> coordinates(n + 1, {0, 0});
    vector<float> potentials(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        float c;
        cin >> a >> b >> c;
        edges[a].push_back({b, c});
        edges[b].push_back({a, c});
    }
    for (int i = 1; i <= n; i++)
    {
        float x, y;
        cin >> x >> y;
        coordinates[i] = {x, y};
    }
    cin >> s >> e;
    for (int i = 1; i <= n; i++)
    {
        potentials[i] = potential(coordinates[i], coordinates[e]);
    }
    parent[s] = 0;
    dis[s] = 0;
    priority_queue<AStarNode, vector<AStarNode>, greater<AStarNode>> pq;
    pq.push(AStarNode(s, potentials[s]));
    while (!pq.empty())
    {
        auto min_v = pq.top().vertex;
        pq.pop();
        if (min_v == e)
            break;
        if (record[min_v])
            continue;
        record[min_v] = true;
        for (auto edge : edges[min_v])
        {
            int target = edge.first;
            if (dis[min_v] + edge.second < dis[target])
            {
                dis[target] = dis[min_v] + edge.second;
                pq.push(AStarNode(target, dis[target] + potentials[target]));
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