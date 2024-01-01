#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include "../completeBinaryTree.hpp"
using namespace std;

class MinMaxHeap : public CompleteBinaryTree
{
    enum Type
    {
        MIN,
        MAX
    };
    Type getType(int depth)
    {
        switch (depth % 2)
        {
        case 0:
            return MIN;
        case 1:
            return MAX;
        default:
            return MIN;
        }
    }

public:
    MinMaxHeap(vector<int> arr)
    {
        for (auto val : arr)
        {
            insertion(val);
        }
    }
    void bubbleUpMin(int now)
    {
        int grandparent = getGrandParent(now);
        while (grandparent != -1)
        {
            if (tree[grandparent].val > tree[now].val)
            {
                swap(tree[grandparent], tree[now]);
                now = grandparent;
                grandparent = getGrandParent(now);
            }
            else
            {
                break;
            }
        }
    }
    void bubbleUpMax(int now)
    {
        int grandparent = getGrandParent(now);
        while (grandparent != -1)
        {
            if (tree[grandparent].val < tree[now].val)
            {
                swap(tree[grandparent], tree[now]);
                now = grandparent;
                grandparent = getGrandParent(now);
            }
            else
            {
                break;
            }
        }
    }
    void insertion(int val)
    {
        int index = tree.size();
        tree.push_back(Node(val));
        if (index == 0)
        {
            return;
        }
        int parent = getParent(index);
        Node &top = tree[parent];
        Node &down = tree[index];
        int depth = log2(parent + 1);
        switch (getType(depth))
        {
        case MIN:
            if (top.val > down.val)
            {
                swap(tree[parent], tree[index]);
                bubbleUpMin(parent);
            }
            else
            {
                bubbleUpMax(index);
            }
            break;
        case MAX:
            if (top.val < down.val)
            {
                swap(tree[parent], tree[index]);
                bubbleUpMax(parent);
            }
            else
            {
                bubbleUpMin(index);
            }
            break;
        }
    }
    void deletion(int val)
    {
    }
};

int main()
{
    auto test = MinMaxHeap({5, 0, 3, 2, 30, 6, 7, 32, 34, 36, 35, 20});
    test.print();
}