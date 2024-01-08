#ifndef HEAP_HPP
#define HEAP_HPP

#include <optional>
#include <memory>
#include <algorithm>
#include "completeBinaryTree.hpp"
using namespace std;

class Heap : public CompleteBinaryTree
{
public:
    virtual void insert(int) = 0; // O(log n)
    virtual void bubbleUp(int) = 0;
    virtual int sinkDown(int) = 0;
    virtual optional<int> deleteTop() = 0; // O(log n)
    virtual optional<int> getTop() = 0;    // O(1)
};

class MinHeap : public Heap
{
public:
    void bubbleUp(int now)
    {
        int parent = getParent(now);
        if (parent == -1)
            return;
        if (tree[now] < tree[parent])
        {
            swap(tree[now], tree[parent]);
            bubbleUp(parent);
        }
    }
    int sinkDown(int now)
    {
        int left = getLeft(now);
        int right = getRight(now);
        if (left >= tree.size())
            return now;
        if (right >= tree.size())
        {
            if (tree[left] < tree[now])
            {
                swap(tree[left], tree[now]);
                return sinkDown(left);
            }
            else
            {
                return now;
            }
        }
        int minchild = left;
        if (tree[right] < tree[left])
            minchild = right;
        if (tree[minchild] < tree[now])
        {
            swap(tree[minchild], tree[now]);
            return sinkDown(minchild);
        }
        return now;
    }
    MinHeap() {}
    MinHeap(vector<int> arr)
    {
        for (int i : arr)
        {
            insert(i);
        }
    }
    void insert(int val)
    {
        int now = tree.size();
        tree.push_back(val);
        bubbleUp(now);
    }
    optional<int> getTop()
    {
        if (tree.empty())
            return nullopt;
        return tree[0].val;
    }
    optional<int> deleteTop()
    {
        if (tree.empty())
            return nullopt;
        int temp = tree[0].val;
        swap(tree[0], tree.back());
        tree.pop_back();
        sinkDown(0);
        return temp;
    }
};

class MaxHeap : public CompleteBinaryTree
{
public:
    void bubbleUp(int now)
    {
        int parent = getParent(now);
        if (parent == -1)
            return;
        if (tree[now] > tree[parent])
        {
            swap(tree[now], tree[parent]);
            bubbleUp(parent);
        }
    }
    int sinkDown(int now)
    {
        int left = getLeft(now);
        int right = getRight(now);
        if (left >= tree.size())
            return now;
        if (right >= tree.size())
        {
            if (tree[left] > tree[now])
            {
                swap(tree[left], tree[now]);
                return sinkDown(left);
            }
            else
            {
                return now;
            }
        }
        int maxchild = left;
        if (tree[right] > tree[left])
            maxchild = right;
        if (tree[maxchild] > tree[now])
        {
            swap(tree[maxchild], tree[now]);
            return sinkDown(maxchild);
        }
        return now;
    }
    MaxHeap() {}
    MaxHeap(vector<int> arr)
    {
        for (int i : arr)
        {
            insert(i);
        }
    }
    void insert(int val)
    {
        int now = tree.size();
        tree.push_back(val);
        bubbleUp(now);
    }
    optional<int> getTop()
    {
        if (tree.empty())
            return nullopt;
        return tree[0].val;
    }
    optional<int> deleteTop()
    {
        if (tree.empty())
            return nullopt;
        int temp = tree[0].val;
        swap(tree[0], tree.back());
        tree.pop_back();
        sinkDown(0);
        return temp;
    }
};
#endif