#ifndef DEAP_HPP
#define DEAP_HPP
using namespace std;

#include <vector>
#include "doubleEndedPriorityQueue.hpp"
#include "completeBinaryTree.hpp"

class Deap : public CompleteBinaryTree, public DEPQ
{
private:
    enum Type
    {
        LEFT,
        RIGHT
    };
    Type getType(int index)
    {
        if (index == 0)
            return LEFT;
        int depth = getDepth(index);
        int width = pow(2, depth);
        int half_width = width / 2;
        if (index < width - 1 + half_width)
        {
            return LEFT;
        }
        return RIGHT;
    }

    optional<int> getRight(int index)
    {
        if (index == 0 || getType(index) == RIGHT)
        {
            return nullopt;
        }
        int depth = getDepth(index);
        int half_width = pow(2, depth - 1);
        if (index + half_width < tree.size())
        {
            return index + half_width;
        }
        else
        {
            return getParent(index + half_width);
        }
    }

    optional<int> getLeft(int index)
    {
        if (index == 0 || getType(index) == LEFT)
        {
            return nullopt;
        }
        int depth = getDepth(index);
        int half_width = pow(2, depth - 1);
        return index - half_width;
    }

    void verifyMin(int now)
    {
        int parent = getParent(now);
        if (parent == 0 || parent == -1)
            return;
        if (tree[now] < tree[parent])
        {
            swap(tree[now], tree[parent]);
            verifyMin(parent);
        }
    }
    void verifyMax(int now)
    {
        int parent = getParent(now);
        if (parent == 0 || parent == -1)
            return;
        if (tree[now] > tree[parent])
        {
            swap(tree[now], tree[parent]);
            verifyMax(parent);
        }
    }
    void _insert(int index)
    {
        if (getType(index) == LEFT)
        {
            auto right = getRight(index);
            if (right.has_value())
            {
                if (tree[index] > tree[right.value()])
                {
                    swap(tree[index], tree[right.value()]);
                    verifyMax(right.value());
                }
                else
                {
                    verifyMin(index);
                }
            }
        }
        else
        {
            auto left = getLeft(index);
            if (left.has_value())
            {
                if (tree[index] < tree[left.value()])
                {
                    swap(tree[index], tree[left.value()]);
                    verifyMin(left.value());
                }
                else
                {
                    verifyMax(index);
                }
            }
        }
    }
    int sinkDownMax(int now)
    {
        int left = CompleteBinaryTree::getLeft(now);
        int right = CompleteBinaryTree::getRight(now);
        if (left >= tree.size())
            return now;
        if (right >= tree.size())
        {
            if (tree[left] > tree[now])
            {
                swap(tree[left], tree[now]);
                return sinkDownMax(left);
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
            return sinkDownMax(maxchild);
        }
        return now;
    }
    int sinkDownMin(int now)
    {
        int left = CompleteBinaryTree::getLeft(now);
        int right = CompleteBinaryTree::getRight(now);
        if (left >= tree.size())
            return now;
        if (right >= tree.size())
        {
            if (tree[left] < tree[now])
            {
                swap(tree[left], tree[now]);
                return sinkDownMin(left);
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
            return sinkDownMin(minchild);
        }
        return now;
    }

public:
    Deap(vector<int> arr)
    {
        tree.push_back(0);
        for (auto i : arr)
        {
            insert(i);
        }
    }
    void insert(int val)
    {
        int now = tree.size();
        tree.push_back(val);
        if (now == 1)
            return;
        _insert(now);
    }
    optional<int> getMin()
    {
        if (tree.size() == 1)
        {
            return std::nullopt;
        }
        return tree[1].val;
    }
    optional<int> getMax()
    {
        if (tree.size() == 1)
        {
            return std::nullopt;
        }
        if (tree.size() == 2)
        {
            return tree[1].val;
        }
        return tree[2].val;
    }
    optional<int> deleteMin()
    {
        if (tree.size() < 2)
            return std::nullopt;
        int temp = tree[1].val;
        swap(tree[1], tree.back());
        tree.pop_back();
        _insert(sinkDownMin(1));
        return temp;
    }
    optional<int> deleteMax()
    {
        if (tree.size() < 2)
            return std::nullopt;
        if (tree.size() == 2)
        {
            int temp = tree[1].val;
            tree.pop_back();
            return temp;
        }
        int temp = tree[2].val;
        swap(tree[2], tree.back());
        tree.pop_back();
        _insert(sinkDownMax(2));
        return temp;
    }
    void clean()
    {
        tree.clear();
        tree.push_back(0);
    }
    void print()
    {
        CompleteBinaryTree::print();
    }
};
#endif