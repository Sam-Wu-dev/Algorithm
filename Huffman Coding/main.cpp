#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;
struct Node
{
    int feq;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(int f) : feq(f) {}
    Node(int f, Node *l, Node *r) : feq(f), left(l), right(r) {}
};
struct CustomCompare
{
    bool operator()(const Node *a, const Node *b)
    {
        return a->feq > b->feq;
    }
};
vector<string> ans;
string now = "";
unordered_map<int, int> map;
void helper(Node *root)
{
    if (!root)
    {
        return;
    }
    if (root->left)
    {
        now += "0";
        helper(root->left);
        now.pop_back();
        now += "1";
        helper(root->right);
        now.pop_back();
    }
    else
    {
        ans[map[root->feq]] = now;
    }
}
int main()
{
    int n;
    cin >> n;
    ans.resize(n);
    priority_queue<Node *, vector<Node *>, CustomCompare> pq;
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        cin >> temp;
        map[temp] = i;
        pq.push(new Node(temp));
    }
    while (pq.size() > 1)
    {
        auto a = pq.top();
        pq.pop();
        auto b = pq.top();
        pq.pop();
        pq.push(new Node(a->feq + b->feq, a, b));
    }
    helper(pq.top());
    cout << n << endl;
    for (int i = 0; i < n - 1; i++)
    {
        cout << ans[i] << " ";
    }
    cout << ans.back();
}