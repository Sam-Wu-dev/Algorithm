#ifndef HEAP_HPP
#define HEAP_HPP
#include <functional>
#include <optional>
#include <memory>
#include <algorithm>
#include "completeBinaryTree.hpp"
using namespace std;

template <class T>
class Heap : public CompleteBinaryTree<T>
{
public:
    virtual void insert(T) = 0; // O(log n)
    virtual void bubbleUp(int) = 0;
    virtual int sinkDown(int) = 0;
    virtual optional<T> deleteTop() = 0; // O(log n)
    virtual optional<T> getTop() = 0;    // O(1)
};
template <class T>
class MinHeap : public Heap<T>
{
public:
    using Heap<T>::getParent;
    using Heap<T>::getLeft;
    using Heap<T>::getRight;
    using Heap<T>::tree;
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
    MinHeap(vector<T> arr)
    {
        for (T i : arr)
        {
            insert(i);
        }
    }
    void insert(T val)
    {
        int now = tree.size();
        tree.push_back(val);
        bubbleUp(now);
    }
    optional<T> getTop()
    {
        if (tree.empty())
            return nullopt;
        return tree[0];
    }
    optional<T> deleteTop()
    {
        if (tree.empty())
            return nullopt;
        auto temp = tree[0];
        swap(tree[0], tree.back());
        tree.pop_back();
        sinkDown(0);
        return temp;
    }
};
template <class T>
class MaxHeap : public Heap<T>
{
public:
    using Heap<T>::getParent;
    using Heap<T>::getLeft;
    using Heap<T>::getRight;
    using Heap<T>::tree;
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
    MaxHeap(vector<T> arr)
    {
        for (T i : arr)
        {
            insert(i);
        }
    }
    void insert(T val)
    {
        int now = tree.size();
        tree.push_back(val);
        bubbleUp(now);
    }
    optional<T> getTop()
    {
        if (tree.empty())
            return nullopt;
        return tree[0].val;
    }
    optional<T> deleteTop()
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