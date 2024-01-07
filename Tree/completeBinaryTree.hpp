#ifndef COMPLETEBINARYTREE_HPP
#define COMPLETEBINARYTREE_HPP
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include <iomanip>
using namespace std;

struct Node
{
    int val;
    Node(int val) : val(val) {}
    bool operator<(Node &other)
    {
        return this->val < other.val;
    }
    bool operator>(Node &other)
    {
        return this->val > other.val;
    }
};

class CompleteBinaryTree
{
protected:
    vector<Node> tree;

public:
    static int getParent(int index)
    {
        if (index == 0 || index == -1)
            return -1; // Root node has no parent
        return (index - 1) / 2;
    }

    static int getLeft(int index)
    {
        int leftIndex = 2 * index + 1;
        return leftIndex; // Caller should check if leftIndex is within bounds of the array
    }

    static int getRight(int index)
    {
        int rightIndex = 2 * index + 2;
        return rightIndex; // Caller should check if rightIndex is within bounds of the array
    }
    static int getGrandParent(int index) { return getParent(getParent(index)); }
    int size()
    {
        return tree.size();
    }
    void clean()
    {
        tree.clear();
    }
    bool empty()
    {
        return tree.empty();
    }
    void set(int index, int val)
    {
        tree[index] = val;
    }
    int getDepth(int index)
    {
        return log2(index + 1);
    }
    void print()
    {
        if (tree.empty())
            return;

        int depth = log2(tree.size()) + 1;
        int max_width = (1 << (depth + 1)) - 1; // Increased width for more spacing
        int index = 0;

        for (int level = 0; level < depth; level++)
        {
            int level_width = (1 << level);
            int space = max_width / level_width;
            int half_space = space / 2;

            for (int i = 0; i < level_width && index < tree.size(); i++, index++)
            {
                cout << setw((i == 0) ? half_space : space) << tree[index].val;
            }

            cout << endl;
        }
    }
};
#endif