#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <memory>
#include <queue>
#include <math.h>
using namespace std;

template <class T, class N>
class BinarySearchTree
{
protected:
    shared_ptr<N> root;

public:
    virtual void insert(T) = 0;
    virtual bool remove(T) = 0;
    shared_ptr<N> _find(shared_ptr<N> now, T val)
    {
        while (now)
        {
            if (now->val == val)
            {
                return now;
            }
            if (val < now->val)
            {
                now = now->left;
            }
            else
            {
                now = now->right;
            }
        }
        return nullptr;
    }
    bool find(T val)
    {
        return _find(root, val) ? true : false;
    }
    void clean()
    {
        root = nullptr;
    }
    shared_ptr<N> Successor(shared_ptr<N> node)
    {
        if (!node || !node->right)
            return nullptr;
        shared_ptr<N> current = node->right;
        while (current->left)
        {
            current = current->left;
        }
        return current;
    }
    shared_ptr<N> PreDecessor(shared_ptr<N> node)
    {
        if (!node || !node->left)
            return nullptr;
        shared_ptr<N> current = node->left;
        while (current->right)
        {
            current = current->right;
        }
        return current;
    }
    int height(shared_ptr<N> node)
    {
        if (node == nullptr)
            return 0;
        return max(height(node->left), height(node->right)) + 1;
    }
    void print()
    {
        int h = height(root);
        queue<shared_ptr<N>> q;
        q.push(root);
        int level = 0;
        while (!q.empty() && level < h)
        {
            int nodeCount = q.size();
            printLevel(q, nodeCount, level, h);
            level++;
        }
    }
    void printWithSpacing(shared_ptr<N> node, int spacing)
    {
        cout << string(spacing / 2, ' ');
        if (node != nullptr)
            cout << node->val;
        else
            cout << " ";
        cout << string(spacing / 2, ' ');
    }
    void printLevel(queue<shared_ptr<N>> &q, int nodeCount, int level, int totalHeight)
    {
        int spacing = pow(2, totalHeight - level + 1);
        while (nodeCount > 0)
        {
            shared_ptr<N> node = q.front();
            q.pop();
            printWithSpacing(node, spacing);
            if (node != nullptr)
            {
                q.push(node->left);
                q.push(node->right);
            }
            else
            {
                q.push(nullptr);
                q.push(nullptr);
            }
            nodeCount--;
        }
        cout << endl;
    }
};

#endif // BINARYSEARCHTREE_HPP
