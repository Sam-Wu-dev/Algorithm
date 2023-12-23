#include "dfs.hpp"
#include <iostream>
using namespace std;

// vector<string> vertices = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"};
// vector<tuple<int, int, float>> edges = {
//     {0, 1, 1.0},  // a-b
//     {1, 4, 1.0},  // b-e
//     {1, 2, 1.0},  // b-c
//     {2, 3, 1.0},  // c-d
//     {3, 4, 1.0},  // d-e
//     {4, 5, 1.0},  // e-f
//     {5, 6, 1.0},  // f-g
//     {5, 8, 1.0},  // f-i
//     {6, 9, 1.0},  // g-j
//     {6, 10, 1.0}, // g-k
//     {6, 7, 1.0},  // g-h
//     {7, 8, 1.0},  // h-i
// };
vector<string> vertices = {
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"};

vector<tuple<int, int, float>> edges = {
    {0, 1, 1.0},   // a-b
    {1, 2, 1.0},   // b-c
    {2, 3, 1.0},   // c-d
    {3, 4, 1.0},   // d-e
    {4, 5, 1.0},   // e-f
    {5, 6, 1.0},   // f-g
    {6, 7, 1.0},   // g-h
    {7, 8, 1.0},   // h-i
    {8, 9, 1.0},   // i-j
    {9, 10, 1.0},  // j-k
    {10, 11, 1.0}, // k-l
    {11, 0, 1.0},  // l-a
    // {1, 4, 1.0},   // b-e
    // {2, 5, 1.0},   // c-f
    // {3, 6, 1.0},   // d-g
    // {4, 7, 1.0},   // e-h
    // {5, 8, 1.0},   // f-i
    // {6, 9, 1.0},   // g-j
    // {7, 10, 1.0},  // h-k
    // {8, 11, 1.0},  // i-l
    // {9, 0, 1.0},   // j-a
    // {10, 1, 1.0},  // k-b
    // {11, 2, 1.0},  // l-c
    // {0, 3, 1.0},   // a-d
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
    cout << "Back edges: " << endl;
    graph.printBackEdges();
}