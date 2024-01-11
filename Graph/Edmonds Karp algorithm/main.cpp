#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <unordered_set>
#include <limits.h>
#include "../graph.hpp"
using namespace std;

class EdmondsKarp
{
private:
    Graph &graph;

    // Finds an augmenting path and returns the flow for that path.
    float find_augmenting_path(int source, int sink, vector<int> &parent)
    {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = source;
        queue<pair<int, float>> q; // Pair of vertex index and flow.
        q.push({source, numeric_limits<float>::max()});

        while (!q.empty())
        {
            int u = q.front().first;
            float flow = q.front().second;
            q.pop();

            for (auto &edge : graph.adj[u])
            {
                int v = edge.to;
                if (parent[v] == -1 && edge.weight > 0)
                {                  // Check for available capacity
                    parent[v] = u; // Set parent
                    float new_flow = min(flow, edge.weight);
                    if (v == sink)
                        return new_flow;
                    q.push({v, new_flow});
                }
            }
        }

        return 0;
    }

public:
    EdmondsKarp(Graph &g) : graph(g) {}

    float getMaximumFlow(int source, int sink)
    {
        float maximumFlow = 0;
        vector<int> parent(graph.V.size()); // Store parent of each vertex in path
        float flow;

        while ((flow = find_augmenting_path(source, sink, parent)) > 0)
        {
            maximumFlow += flow;
            int cur = sink;
            while (cur != source)
            {
                int prev = parent[cur];
                // Update the capacities of the forward and reverse edges
                auto &forward_edge = *find_if(graph.adj[prev].begin(), graph.adj[prev].end(),
                                              [cur](const Edge &edge)
                                              { return edge.to == cur; });
                forward_edge.weight -= flow;
                // For reverse edge, either find it and update it, or create it if it doesn't exist
                auto reverse_edge_it = find_if(graph.adj[cur].begin(), graph.adj[cur].end(),
                                               [prev](const Edge &edge)
                                               { return edge.to == prev; });
                if (reverse_edge_it != graph.adj[cur].end())
                {
                    reverse_edge_it->weight += flow;
                }
                else
                {
                    graph.adj[cur].push_back(Edge(cur, prev, flow));
                }

                cur = prev;
            }
        }

        return maximumFlow;
    }
};

int main()
{
    std::vector<std::string> vertices = {"A", "B", "C", "D", "E", "F"};
    std::vector<std::tuple<int, int, float>> edges = {
        {0, 1, 10.0}, {0, 2, 10.0}, {1, 2, 2.0}, {1, 3, 4.0}, {1, 4, 8.0}, {2, 4, 9.0}, {3, 5, 10.0}, {4, 3, 6.0}, {4, 5, 10.0}};
    Graph g = Graph(vertices, edges, true);
    g.initialize_adj_list();
    EdmondsKarp ek(g);
    float maxFlow = ek.getMaximumFlow(0, 5);
    cout << "Maximum flow: " << maxFlow << endl;
    return 0;
}
