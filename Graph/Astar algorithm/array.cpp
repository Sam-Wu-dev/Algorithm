#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#define maxf 10001
#define axis pair<float, float>
using namespace std;

int findMin(vector<float> &vec, vector<bool> &record, vector<float> &potentials)
{
    int index = 1;
    float val = maxf;
    for (int i = 1; i < vec.size(); i++)
    {
        if (!record[i] && vec[i] + potentials[i] < val)
        {
            index = i;
            val = vec[i] + potentials[i];
        }
    }
    return index;
}

float potential(axis from, axis target)
{
    return sqrt((target.first - from.first) * (target.first - from.first) + (target.second - from.second) * (target.second - from.second));
}

int main()
{
    // A*
    int n, m, s, e;
    cin >> n >> m;
    vector<vector<float>> table(n + 1, vector<float>(n + 1, maxf));
    vector<float> dis(n + 1, maxf);
    vector<int> parent(n + 1);
    vector<bool> record(n + 1, false);
    vector<axis> coordinates(n + 1, {0, 0});
    vector<float> potentials(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        float c;
        cin >> a >> b >> c;
        table[a][b] = c;
        table[b][a] = c;
    }
    for (int i = 1; i <= n; i++)
    {
        float x, y;
        cin >> x >> y;
        table[i][i] = 0;
        coordinates[i] = {x, y};
    }
    cin >> s >> e;
    for (int i = 1; i <= n; i++)
    {
        potentials[i] = potential(coordinates[i], coordinates[e]);
    }
    dis[s] = 0;
    parent[s] = 0;
    record[s] = true;
    while (true)
    {
        int min_v = findMin(dis, record, potentials);
        if (min_v == e || dis[min_v] == maxf)
            break; // Break if target reached or no path

        for (int j = 1; j <= n; j++)
        {
            if (record[j])
                continue;
            if (dis[min_v] + table[min_v][j] < dis[j])
            {
                dis[j] = dis[min_v] + table[min_v][j];
                parent[j] = min_v;
            }
        }
        record[min_v] = true;
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
// Time complexity O(n^2)