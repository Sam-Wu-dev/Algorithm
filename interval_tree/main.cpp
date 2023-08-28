#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
struct IntervalNode
{
    int low;
    int high;
    int max;
    IntervalNode *left;
    IntervalNode *right;
};

struct IntervalNodeR
{
    int low;
    int high;
    int min;
    IntervalNodeR *left;
    IntervalNodeR *right;
};

void insert(IntervalNode *root, int low, int high)
{
    if (!root)
    {
        root = new IntervalNode{low, high, high};
        return;
    }
    while (root)
    {
        root->max = max(root->max, high);
        if (root->low > low)
        {
            if (!root->left)
            {
                root->left = new IntervalNode{low, high, high};
                return;
            }
            root = root->left;
        }
        else
        {
            if (!root->right)
            {
                root->right = new IntervalNode{low, high, high};
                return;
            }
            root = root->right;
        }
    }
}

void insertR(IntervalNodeR *root, int low, int high)
{
    if (!root)
    {
        root = new IntervalNodeR{low, high, low};
        return;
    }
    while (root)
    {
        root->min = min(root->min, low);
        if (root->high > high)
        {
            if (!root->left)
            {
                root->left = new IntervalNodeR{low, high, low};
                return;
            }
            root = root->left;
        }
        else
        {
            if (!root->right)
            {
                root->right = new IntervalNodeR{low, high, low};
                return;
            }
            root = root->right;
        }
    }
}

void print(IntervalNode *root)
{
    if (!root)
        return;
    queue<IntervalNode *> q;
    q.push(root);
    while (!q.empty())
    {
        vector<IntervalNode *> temp;
        while (!q.empty())
        {
            temp.push_back(q.front());
            q.pop();
        }
        for (auto i : temp)
        {
            cout << i->low << " " << i->high << " " << i->max << " ";
            if (i->left)
            {
                q.push(i->left);
            }
            if (i->right)
            {
                q.push(i->right);
            }
        }
        cout << endl;
    }
}

void printR(IntervalNodeR *root)
{
    if (!root)
        return;
    queue<IntervalNodeR *> q;
    q.push(root);
    while (!q.empty())
    {
        vector<IntervalNodeR *> temp;
        while (!q.empty())
        {
            temp.push_back(q.front());
            q.pop();
        }
        for (auto i : temp)
        {
            cout << i->low << " " << i->high << " " << i->min << " ";
            if (i->left)
            {
                q.push(i->left);
            }
            if (i->right)
            {
                q.push(i->right);
            }
        }
        cout << endl;
    }
}

IntervalNode *search(IntervalNode *root, IntervalNode *target)
{
    while (root && (target->low > root->high || target->high < root->low))
    {
        // target and root no overlap
        if (root->left && root->left->max >= target->low)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

IntervalNodeR *searchR(IntervalNodeR *root, IntervalNodeR *target)
{
    while (root && (target->low > root->high || target->high < root->low))
    {
        // target and root no overlap
        if (root->right && root->right->min <= target->high)
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return root;
}

int main()
{
    IntervalNodeR *root = new IntervalNodeR{3, 5, 3};
    insertR(root, 1, 7);
    insertR(root, 6, 11);
    insertR(root, 0, 3);
    insertR(root, -9, 16);
    printR(searchR(root, new IntervalNodeR{15, 18, 15}));
}