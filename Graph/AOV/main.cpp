#include <iostream>
#include <limits>
#include <math.h>
#include "../DFS/dfs.hpp"

using namespace std;

class AOV : public DFSTree
{
public:
    vector<float> est, lst;
    AOV(vector<string> vertices, vector<tuple<int, int, float>> edges, int initial) : DFSTree(vertices, edges)
    {
        est = vector<float>(V.size(), 0);
        lst = vector<float>(V.size(), std::numeric_limits<float>::infinity());
        est[initial] = 0;
        start(initial);
        TopologicalOrder();
    }

    void findEarliestStartTime()
    {
        for (auto n : nodes)
        {
            int now = n->vertex.index;
            for (auto e : adj[now])
            {
                est[e.to] = max(est[now] + e.weight, est[e.to]);
            }
        }
    }
    void findLatestStartTime()
    {
        lst.back() = est.back();
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
        {
            auto now = (*it)->vertex.index;
            for (auto e : adj[now])
            {
                lst[now] = min(lst[now], lst[e.to] - e.weight);
            }
        }
    }
    void findCriticalPath()
    {
        findEarliestStartTime();
        findLatestStartTime();
        vector<Edge> criticalPath;
        for (auto n : nodes)
        {
            int now = n->vertex.index;
            cout << n->vertex.name << " " << est[now] << " " << lst[now] << endl;
            for (auto e : adj[now])
            {
                if (est[now] == lst[e.to] - e.weight)
                {
                    criticalPath.push_back(e);
                }
            }
        }
        cout << "critical path:" << endl;
        for (auto e : criticalPath)
        {
            auto v = V[e.from].name;
            auto u = V[e.to].name;
            cout << v << " -> " << u << endl;
        }
        cout << endl;
    }
};

int main()
{
    vector<string> vertices = {"a", "b", "c", "d", "e", "f", "g"};
    vector<tuple<int, int, float>> edges = {
        {0, 1, 3}, // a-b
        {0, 2, 8}, // a-c
        {1, 3, 5}, // b-d
        {2, 4, 2}, // c-e
        {3, 4, 4}, // d-e
        {3, 5, 2}, // d-f
        {4, 5, 5}, // e-f
        {5, 6, 3}, // f-g
    };
    auto aov = AOV(vertices, edges, 0);
    aov.findCriticalPath();
}