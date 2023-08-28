#include <iostream>
#include <algorithm>
#include <vector>
#define maxf 100000
using namespace std;

struct Edge
{
    int from;
    int target;
    float val;
    Edge(int a, int b, float c) : from(a), target(b), val(c) {}
};

int main()
{
    // Bellman-Ford algorithm
    int n, m, s;
    cin >> n >> m;
    vector<float> dis(n + 1, maxf);
    vector<int> parent(n + 1);
    vector<Edge> edges;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        float c;
        cin >> a >> b >> c;
        edges.push_back(Edge(a, b, c));
    }
    cin >> s;
    for (int j = 0; j < m; j++)
    {
        if (edges[j].from == s)
        {
            dis[edges[j].target] = edges[j].val;
            parent[edges[j].target] = s;
        }
    }
    dis[s] = 0;
    parent[s] = 0;
    for (int k = 1; k < n; k++)
    {
        for (int j = 0; j < m; j++)
        {
            auto edge = edges[j];
            if (dis[edge.from] + edge.val < dis[edge.target])
            {
                dis[edge.target] = dis[edge.from] + edge.val;
                parent[edge.target] = edge.from;
            }
        }
    }
    vector<float> temp = dis;
    for (int j = 0; j < m; j++)
    {
        auto edge = edges[j];
        if (dis[edge.from] + edge.val < dis[edge.target])
        {
            dis[edge.target] = dis[edge.from] + edge.val;
        }
    }
    if (temp != dis)
    {
        cout << "There is a negative weight cycle in the graph" << endl;
        return 0;
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