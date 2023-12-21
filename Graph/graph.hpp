#ifndef graph_hpp
#define graph_hpp
#include <vector>
#include <limits>
#include <string>
#include <tuple>

using namespace std;
struct Vertex
{
    string name = "";
    int index;
    Vertex(int b) : index(b) {}
    Vertex(string a, int b) : name(a), index(b) {}
};
struct Edge
{
    int from;
    int to;
    float weight;
    Edge(int a, int b, float c) : from(a), to(b), weight(c) {}
};
class Graph
{
public:
    vector<Edge> E;
    vector<Vertex> V;
    vector<vector<Edge>> adj;
    vector<vector<float>> table;
    Graph(int n, vector<tuple<int, int, float>> edges)
    {
        int index = 0;
        for (int i = 0; i < n; i++)
        {
            V.push_back(Vertex(
                index++));
        }
        for (auto edge : edges)
        {
            E.push_back(Edge(get<0>(edge), get<1>(edge), get<2>(edge)));
        }
    }
    Graph(vector<string> vertices, vector<tuple<int, int, float>> edges)
    {
        int index = 0;
        for (auto s : vertices)
        {
            V.push_back(Vertex(s,
                               index++));
        }
        for (auto edge : edges)
        {
            E.push_back(Edge(get<0>(edge), get<1>(edge), get<2>(edge)));
        }
    }
    void initialize_adj()
    {
        adj.resize(V.size());
        for (const auto &edge : E)
        {
            // Assuming the graph is undirected. If it's directed, remove the second push_back.
            adj[edge.from].push_back(edge);
            adj[edge.to].push_back(Edge(edge.to, edge.from, edge.weight)); // Add this for undirected graph
        }
    }

    void initialize_table()
    {
        const float INF = std::numeric_limits<float>::infinity();
        table.resize(V.size(), vector<float>(V.size(), INF));
        for (int i = 0; i < V.size(); ++i)
        {
            table[i][i] = 0; // Distance from a vertex to itself is 0
        }
        for (const auto &edge : E)
        {
            table[edge.from][edge.to] = edge.weight;
            table[edge.to][edge.from] = edge.weight; // Add this for undirected graph
        }
    }
};
#endif