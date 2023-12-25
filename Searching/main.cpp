#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <random>
#include <tuple>
#include "npuzzle.hpp"
using namespace std;

void shuffleTiles(vector<int> &vertices)
{
    random_device rd;
    mt19937 g(rd());

    // Shuffle the tiles, except the first one (the empty space)
    shuffle(next(vertices.begin()), vertices.end(), g);
}

vector<pair<vector<vector<int>>, vector<vector<int>>>> test_data = {
    {{{7, 11, 5, 0}, {8, 14, 12, 10}, {2, 4, 13, 15}, {6, 3, 9, 1}},
     {{7, 14, 11, 5}, {8, 12, 13, 10}, {2, 0, 4, 15}, {6, 3, 9, 1}}},
    {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}},
     {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 0, 11, 12}, {13, 10, 14, 15}}},
    {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 0, 10, 11}, {12, 13, 14, 15}},
     {{1, 2, 3, 0}, {9, 5, 6, 4}, {12, 10, 7, 8}, {13, 14, 15, 11}}}};

void print(vector<vector<int>> &vec)
{
    for (auto i : vec)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}
int main()
{
    // vector<int> vertices(grid_size * grid_size);
    // for (int i = 0; i < vertices.size(); ++i)
    // {
    //     vertices[i] = i;
    // }
    // shuffleTiles(vertices); // Randomly shuffle the tiles
    // vector<vector<int>> initializeState;
    // vector<vector<int>> finalState{{7, 14, 11, 5}, {8, 12, 13, 10}, {2, 0, 4, 15}, {6, 3, 9, 1}};
    // for (int i = 0; i < grid_size; i++)
    // {
    //     initializeState.push_back({});
    //     for (int j = 0; j < grid_size; j++)
    //     {
    //         initializeState[i].push_back(vertices[i * grid_size + j]);
    //     }
    // }

    vector<vector<int>> initializeState = test_data[2].first;
    vector<vector<int>> finalState = test_data[2].second;
    cout << "Initial state:" << endl;
    print(initializeState);
    cout << "---------------------------------" << endl;
    cout << "Solving with Iterative Depth First Search" << endl;
    IDFS idfs(initializeState, finalState);
    idfs.solve();
    idfs.analysis();
    cout << "---------------------------------" << endl;
    cout << "Solving with Uniform Cost Search" << endl;
    UCS ucs(initializeState, finalState);
    ucs.solve();
    ucs.analysis();
    cout << "---------------------------------" << endl;
    cout << "Solving with Greedy Best First Search" << endl;
    GBFS gbfs(initializeState, finalState);
    gbfs.solve();
    gbfs.analysis();
    cout << "---------------------------------" << endl;
    cout << "Solving with A* algorithm" << endl;
    AStar astar(initializeState, finalState);
    astar.solve();
    astar.analysis();
    cout << "---------------------------------" << endl;
    cout << "Solving with Recursive Best First Search" << endl;
    RBFS rbfs(initializeState, finalState);
    rbfs.solve();
    rbfs.analysis();
}