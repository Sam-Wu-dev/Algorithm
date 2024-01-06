#ifndef MinMaxHeap_hpp
#define MinMaxHeap_hpp

#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <optional>
#include "doubleEndedPriorityQueue.hpp"
#include "completeBinaryTree.hpp"

using namespace std;

class MinMaxHeap : public DEPQ, public CompleteBinaryTree
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
    void sinkDownMin(int now)
    {
        int firstChild = getLeft(now);
        int secondChild = getRight(now);
        int firstGrandChild = getLeft(firstChild);
        if (firstChild >= tree.size())
        {
            return;
        }
        if (firstGrandChild >= tree.size())
        {
            int minChild = firstChild;
            if (secondChild < tree.size() && tree[secondChild] < tree[firstChild])
            {
                minChild = secondChild;
            }
            if (tree[minChild] < tree[now])
            {
                swap(tree[minChild], tree[now]);
            }
            return;
        }
        int minGrandChild = firstGrandChild;
        int lastGrandChild = min(int(tree.size() - 1), getRight(secondChild));
        for (int i = firstGrandChild; i <= lastGrandChild; i++)
        {
            if (tree[i] < tree[minGrandChild])
            {
                minGrandChild = i;
            }
        }
        if (tree[minGrandChild] < tree[now])
        {
            swap(tree[minGrandChild], tree[now]);
            sinkDownMin(minGrandChild);
        }
    }
    void sinkDownMax(int now)
    {
        int firstChild = getLeft(now);
        int secondChild = getRight(now);
        int firstGrandChild = getLeft(firstChild);
        if (firstChild >= tree.size())
        {
            return;
        }
        if (firstGrandChild >= tree.size())
        {
            int maxChild = firstChild;
            if (secondChild >= tree.size() && tree[secondChild] > tree[firstChild])
            {
                maxChild = secondChild;
            }
            swap(tree[maxChild], tree[now]);
            return;
        }
        int maxGrandChild = firstGrandChild;
        int lastGrandChild = min(int(tree.size() - 1), getRight(secondChild));
        for (int i = firstGrandChild; i <= lastGrandChild; i++)
        {
            if (tree[i] > tree[maxGrandChild])
            {
                maxGrandChild = i;
            }
        }
        if (tree[maxGrandChild] > tree[now])
        {
            swap(tree[now], tree[maxGrandChild]);
            sinkDownMax(maxGrandChild);
        }
    }

public:
    MinMaxHeap(vector<int> arr)
    {
        for (auto val : arr)
        {
            insert(val);
        }
    }

    void insert(int val)
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
        int depth = getDepth(parent);
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
    std::optional<int> getMin()
    {
        if (tree.empty())
        {
            return std::nullopt;
        }
        return tree[0].val;
    }

    std::optional<int> getMax()
    {
        if (tree.empty())
        {
            return std::nullopt;
        }
        int maxNode = 0;
        int lastNode = std::min(int(tree.size() - 1), getRight(0));
        for (int i = 0; i < lastNode; i++)
        {
            if (tree[i] > tree[maxNode])
            {
                maxNode = i;
            }
        }
        return tree[maxNode].val;
    }

    std::optional<int> deleteMin()
    {
        if (tree.empty())
        {
            return std::nullopt;
        }
        int minValue = tree[0].val;
        swap(tree[0], tree.back());
        tree.pop_back();
        sinkDownMin(0);
        return minValue;
    }
    std::optional<int> deleteMax()
    {
        if (tree.empty())
        {
            return std::nullopt;
        }
        int maxNode = 0;
        int lastNode = std::min(int(tree.size() - 1), getRight(0));
        for (int i = 0; i <= lastNode; i++)
        {
            if (tree[i] > tree[maxNode])
            {
                maxNode = i;
            }
        }
        int maxValue = tree[maxNode].val;
        swap(tree[maxNode], tree.back());
        tree.pop_back();
        sinkDownMax(maxNode);
        return maxValue;
    }
    void clean()
    {
        tree.clear();
    }
    void print()
    {
        CompleteBinaryTree::print();
    }
};
#endif