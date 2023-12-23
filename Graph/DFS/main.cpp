#include "dfs.hpp"
#include <iostream>
using namespace std;

vector<string> vertices = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"};
vector<tuple<int, int, float>> edges = {
    {0, 1, 1.0},  // a-b
    {1, 4, 1.0},  // b-e
    {1, 2, 1.0},  // b-c
    {2, 3, 1.0},  // c-d
    {3, 4, 1.0},  // d-e
    {4, 5, 1.0},  // e-f
    {5, 6, 1.0},  // f-g
    {5, 8, 1.0},  // f-i
    {6, 9, 1.0},  // g-j
    {6, 10, 1.0}, // g-k
    {6, 7, 1.0},  // g-h
    {7, 8, 1.0},  // h-i
};

int main()
{
    DFSTree graph(vertices, edges);
    graph.start(4);
    cout << "DFS Analysis" << endl;
    graph.printNodes();
    cout << "Traversal order: " << endl;
    graph.TraversalOrder();
    cout << "Topologic order: " << endl;
    graph.TopologicalOrder();
    cout << "Articulation points: " << endl;
    graph.printArticulationPoints();
}