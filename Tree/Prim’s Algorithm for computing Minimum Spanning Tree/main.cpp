#include <iostream>
#include <vector>
#include <queue>
#define maxf 10001
using namespace std;

struct Edge
{
    int from;
    int target;
    float val;
    Edge(int a, int b, float c) : from(a), target(b), val(c) {}
};

struct compare
{
    bool operator()(Edge *a, Edge *b)
    {
        return a->val > b->val;
    }
};

int main()
{
    // Prim's algorithm
    int n, m, s;
    cin >> n >> m;
    vector<vector<Edge *>> edges(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        float c;
        cin >> a >> b >> c;
        edges[a].push_back(new Edge(a, b, c));
        edges[b].push_back(new Edge(b, a, c));
    }
    vector<bool> record(n + 1, false);
    priority_queue<Edge *, vector<Edge *>, compare> pq;
    vector<int> ans(n + 1);
    cin >> s;
    ans[s] = 0;
    float total_weight = 0;
    for (int k = 0; k < n; k++)
    {
        record[s] = true;
        for (auto edge : edges[s])
        {
            if (!record[edge->target])
            {
                pq.push(edge);
            }
        }
        while (!pq.empty() && record[pq.top()->target])
        {
            pq.pop();
        }
        if (!pq.empty())
        {
            s = pq.top()->target;
            total_weight += pq.top()->val;
            ans[s] = pq.top()->from;
            pq.pop();
        }
    }
    for (int i = 1; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << ans[n] << endl;
    cout << total_weight << endl;
    return 0;
}