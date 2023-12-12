#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> start(n);
    vector<int> end(n);
    vector<int> ans;
    vector<tuple<int, int, int>> activities(n);
    for (int i = 0; i < n; i++)
    {
        cin >> start[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> end[i];
        activities[i] = {i, start[i], end[i]};
    }
    sort(activities.begin(), activities.end(), [](tuple<int, int, int> a, tuple<int, int, int> b)
         { return get<1>(a) < get<1>(b); });
    int index = n - 1;
    int now = 1001;
    while (index >= 0)
    {
        if (get<2>(activities[index]) <= now)
        {
            ans.push_back(get<0>(activities[index]));
            now = get<1>(activities[index]);
        }
        index--;
    }
    cout << ans.size() << endl;
    cout << "(";
    for (int i = ans.size() - 1; i > 0; i--)
    {
        cout << ans[i] + 1 << ",";
    }
    cout << ans[0] + 1 << ")";
}