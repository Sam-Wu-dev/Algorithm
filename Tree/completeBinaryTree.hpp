#ifndef COMPLETEBINARYTREE_HPP
#define COMPLETEBINARYTREE_HPP
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include <iomanip>
#include <string>
#include <functional>
using namespace std;

struct Node
{
    int val;
    Node() : val(0) {}
    Node(int val) : val(val) {}
    bool operator<(Node &other)
    {
        return this->val < other.val;
    }
    bool operator>(Node &other)
    {
        return this->val > other.val;
    }
    friend std::ostream &operator<<(std::ostream &os, const Node &obj)
    {
        os << obj.val;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Node &obj)
    {
        is >> obj.val;
        return is;
    }
};
struct Node2
{
    std::string val;

    Node2() : val("") {}
    Node2(std::string val) : val(val) {}

    bool operator<(const Node2 &other) const
    {
        return this->val < other.val;
    }

    bool operator>(const Node2 &other) const
    {
        return this->val > other.val;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node2 &obj)
    {
        os << obj.val;
        return os;
    }

    // Overloading >> operator
    friend std::istream &operator>>(std::istream &is, Node2 &obj)
    {
        is >> obj.val;
        return is;
    }
};
template <class T>
class CompleteBinaryTree
{
protected:
    vector<T> tree;

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
                cout << setw((i == 0) ? half_space : space) << tree[index];
            }

            cout << endl;
        }
    }
};
#endif