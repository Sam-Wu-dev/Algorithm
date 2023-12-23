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
    int low = INT_MAX;
    Color color = WHITE;
    Node(Vertex &v) : vertex(v) {}
    Node(Vertex &v, shared_ptr<Node> p, int i, int f, Color c) : vertex(v), parent(p), initialTime(i), color(c) {}
};

class DFSTree : public Graph
{
private:
    int order = 0;
    int root;
    vector<shared_ptr<Node>> nodes;
    vector<shared_ptr<Node>> articulationPoints;
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

    void start(int r)
    {
        root = r;
        int order = 0;
        DFS(nodes[r]);
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
        now->low = now->initialTime;
        int count = 0;
        int maxLow = -1;
        for (auto e : adj[now->vertex.index])
        {
            if (nodes[e.to] == now->parent || nodes[e.to] == now)
                continue;
            switch (nodes[e.to]->color)
            {
            case WHITE:
                count++;
                nodes[e.to]->parent = now;
                front_edges.push_back(make_shared<Edge>(e));
                DFS(nodes[e.to]);
                now->low = min(nodes[e.to]->low, now->low);
                maxLow = max(maxLow, nodes[e.to]->low);
                break;
            case GRAY:
                back_edges.push_back(make_shared<Edge>(e));
                now->low = min(now->low, nodes[e.to]->initialTime);
                break;
            case BLACK:
                cross_edges.push_back(make_shared<Edge>(e));
                break;
            }
        }
        now->color = BLACK;
        now->finishTime = order++;
        if (now->vertex.index == root && count > 1 || now->vertex.index != root && now->initialTime <= maxLow)
        {
            articulationPoints.push_back(now);
        }
        return;
    }

    void TopologicalOrder()
    {
        sort(nodes.begin(), nodes.end(), [](shared_ptr<Node> a, shared_ptr<Node> b)
             { return a->finishTime < b->finishTime; });
        for (auto n : nodes)
        {
            cout << n->vertex.name << " -> ";
        }
        cout << endl;
    }

    void TraversalOrder()
    {
        sort(nodes.begin(), nodes.end(), [](shared_ptr<Node> a, shared_ptr<Node> b)
             { return a->initialTime < b->initialTime; });
        for (auto n : nodes)
        {
            cout << n->vertex.name << " -> ";
        }
        cout << endl;
    }

    void printNodes()
    {
        for (auto n : nodes)
        {
            cout << "Name: " << n->vertex.name << ", InitialTime: " << n->initialTime << ", FinishTime: " << n->finishTime << ", Low:" << n->low << endl;
        }
    }

    void printBackEdges()
    {
        for (auto e : back_edges)
        {
            cout << V[e->from].name << " -> " << V[e->to].name << endl;
        }
    }

    void printArticulationPoints()
    {
        for (auto n : articulationPoints)
        {
            cout << n->vertex.name << " ";
        }
        cout << endl;
    }
};

#endif