#include <iostream>
#include <list>
#include <vector>

using namespace std;
using Edge = pair<int, int>;
class Graph
{
    int V;          // Number of vertices
    list<int> *adj; // Pointer to an array containing adjacency lists

public:
    Graph(int V);                                                       // Constructor
    void addEdge(int v, int w);                                         // Function to add an edge to graph
    void DFS(int v, vector<bool> &visited, vector<Edge> &spanningTree); // DFS traversal
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Since the graph is undirected
}

void Graph::DFS(int v, vector<bool> &visited, vector<Edge> &spanningTree)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {
            spanningTree.push_back({v, *i});
            DFS(*i, visited, spanningTree);
        }
    }
}

int main()
{
    // Create a graph given in the above diagram
    int V = 5; // Number of vertices
    Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    vector<bool> visited(V, false);
    vector<Edge> spanningTree;       // Vector to store edges of the spanning tree
    g.DFS(0, visited, spanningTree); // Start DFS from vertex 0

    // Print the spanning tree edges
    cout << "Spanning Tree Edges: " << endl;
    for (const auto &edge : spanningTree)
    {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }

    return 0;
}
