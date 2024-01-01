#ifndef COMPLETEBINARYTREE_HPP
#define COMPLETEBINARYTREE_HPP
#include <vector>
#include <memory>
#include <math.h>
using namespace std;

struct Node
{
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    int val;
    Node(int val) : left(nullptr), right(nullptr), val(val) {}
    Node(shared_ptr<Node> left, shared_ptr<Node> right, int val) : left(left), right(right), val(val) {}
};

class CompleteBinaryTree
{
protected:
    vector<Node> tree;
    int getParent(int index)
    {
        if (index == 0 || index == -1)
            return -1; // Root node has no parent
        return (index - 1) / 2;
    }

    int getLeft(int index)
    {
        int leftIndex = 2 * index + 1;
        return leftIndex; // Caller should check if leftIndex is within bounds of the array
    }

    int getRight(int index)
    {
        int rightIndex = 2 * index + 2;
        return rightIndex; // Caller should check if rightIndex is within bounds of the array
    }
    int getGrandParent(int index) { return getParent(getParent(index)); }

public:
    void print()
    {
        int depth = 0;
        for (int i = 0; i < tree.size(); i++)
        {
            cout << tree[i].val << " ";
            int d = log2(i + 1);
            if (d > depth)
            {
                depth = d;
                cout << endl;
            }
        }
        cout << endl;
    }
};
#endif