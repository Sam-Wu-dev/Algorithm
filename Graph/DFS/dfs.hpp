#ifndef dfs_hpp
#define dfs_hpp
#include "../graph.hpp"
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

struct Node
{
    Vertex &vertex;
    shared_ptr<Node> parent;
    int initialTime = INT_MAX;
    int finishTime = INT_MAX;
    Color color = WHITE;
    Node(Vertex &v) : vertex(v) {}
    Node(Vertex &v, shared_ptr<Node> p, int i, int f, Color c) : vertex(v), parent(p), initialTime(i), color(c) {}
};

class DFSTree : public Graph
{
private:
    int order = 0;
    vector<shared_ptr<Node>> nodes;
    vector<shared_ptr<Edge>> cross_edges; //  Edges that connect vertices in a way that they are neither ancestors nor descendants of each other.
    vector<shared_ptr<Edge>> back_edges;  // Edges that connect a vertex to an ancestor in the DFS tree.
    vector<shared_ptr<Edge>> front_edges; // Edges that lead to an unvisited vertex.

public:
    DFSTree(vector<string> vertices, vector<tuple<int, int, float>> edges) : Graph(vertices, edges)
    {
        initialize_adj_list();
        for (int i = 0; i < V.size(); i++)
        {
            nodes.push_back(make_shared<Node>(Node(V[i])));
        }
    }

    void start()
    {
        int order = 0;
        for (int i = 0; i < V.size(); i++)
        {
            if (nodes[i]->color != BLACK)
            {
                DFS(nodes[i]);
            }
        }
    }

    void DFS(shared_ptr<Node> now)
    {
        now->color = GRAY;
        now->initialTime = order++;

        for (auto e : adj[now->vertex.index])
        {
            switch (nodes[e.to]->color)
            {
            case WHITE:
                nodes[e.to]->parent = now;
                front_edges.push_back(make_shared<Edge>(e));
                DFS(nodes[e.to]);
                break;
            case GRAY:
                back_edges.push_back(make_shared<Edge>(e));
                break;
            case BLACK:
                cross_edges.push_back(make_shared<Edge>(e));
                break;
            }
        }
        now->color = BLACK;
        now->finishTime = order++;
    }

    void TopologicalSort()
    {
        sort(nodes.begin(), nodes.end(), [](shared_ptr<Node> a, shared_ptr<Node> b)
             { return a->finishTime < b->finishTime; });
    }

    void TraversalOrderSort()
    {
        sort(nodes.begin(), nodes.end(), [](shared_ptr<Node> a, shared_ptr<Node> b)
             { return a->initialTime < b->initialTime; });
    }

    void printNodes()
    {
        for (auto n : nodes)
        {
            cout << n->vertex.name << " -> ";
        }
        cout << endl;
    }

    void printArticulationPoints()
    {
    }
};

#endif