#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include "binarySearchTree.hpp"
#include <memory>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

struct Node
{
    int val;
    int height;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    Node(int val, int height) : val(val), height(height) {}
};

template <class T>
class AVLTree : public BinarySearchTree<T>
{
private:
    shared_ptr<Node> root;
    shared_ptr<Node> LeftRotate(shared_ptr<Node> now)
    {
        shared_ptr<Node> temp = now->right;
        now->right = temp->left;
        temp->left = now;
        return temp;
    }
    shared_ptr<Node> RightRotate(shared_ptr<Node> now)
    {
        shared_ptr<Node> temp = now->left;
        now->left = temp->right;
        temp->right = now;
        return temp;
    }

    int GetBalanceFactor(shared_ptr<Node> node)
    {
        int left = node->left ? node->left->height : 0;
        int right = node->right ? node->right->height : 0;
        return left - right;
    }

    shared_ptr<Node> fixImbalance(shared_ptr<Node> node)
    {
        int balanceFactor = GetBalanceFactor(node);

        // Left Left Case
        if (balanceFactor > 1 && GetBalanceFactor(node->left) >= 0)
        {
            return RightRotate(node);
        }

        // Left Right Case
        if (balanceFactor > 1 && GetBalanceFactor(node->left) < 0)
        {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // Right Right Case
        if (balanceFactor < -1 && GetBalanceFactor(node->right) <= 0)
        {
            return LeftRotate(node);
        }

        // Right Left Case
        if (balanceFactor < -1 && GetBalanceFactor(node->right) > 0)
        {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }

public:
    AVLTree(vector<T> arr)
    {
        for (auto i : arr)
        {
            insert(i);
        }
    }
    void insert(T val)
    {
        root = insertNode(root, val);
    }

    shared_ptr<Node> insertNode(shared_ptr<Node> node, T val)
    {
        if (!node)
        {
            return make_shared<Node>(val, 1);
        }

        if (val < node->val)
        {
            node->left = insertNode(node->left, val);
        }
        else
        {
            node->right = insertNode(node->right, val);
        }

        // Update height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // Check and fix imbalance
        return fixImbalance(node);
    }

    int height(shared_ptr<Node> node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    bool find(T val)
    {
        auto now = root;
        while (now)
        {
            if (now->val == val)
            {
                return true;
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
        return false;
    }

    bool remove(T val)
    {
        bool removed = false;
        root = removeNode(root, val, removed);
        return removed;
    }

    shared_ptr<Node> removeNode(shared_ptr<Node> node, T val, bool &removed)
    {
        if (!node)
        {
            // Value not found in the tree.
            return node;
        }

        if (val < node->val)
        {
            // Value is in the left subtree.
            node->left = removeNode(node->left, val, removed);
        }
        else if (val > node->val)
        {
            // Value is in the right subtree.
            node->right = removeNode(node->right, val, removed);
        }
        else
        {
            // Node with the value found for removal.

            // Case 1: Node with one child or no child.
            if (!node->left || !node->right)
            {
                shared_ptr<Node> temp = node->left ? node->left : node->right;

                // No child case.
                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    // One child case.
                    *node = *temp;
                }

                // Node is deleted.
                temp.reset();
                removed = true;
            }
            else
            {
                // Case 2: Node with two children. Get the in-order successor.
                shared_ptr<Node> successor = minValueNode(node->right);

                // Copy the in-order successor's data to this node.
                node->val = successor->val;

                // Delete the in-order successor.
                node->right = removeNode(node->right, successor->val, removed);
            }
        }

        if (!node)
        {
            return node; // If the tree had only one node, return it.
        }

        // Update height of the current node.
        node->height = 1 + max(height(node->left), height(node->right));

        // Check for balance factor and balance the tree if needed.
        return fixImbalance(node);
    }

    shared_ptr<Node> minValueNode(shared_ptr<Node> node)
    {
        shared_ptr<Node> current = node;
        while (current->left)
        {
            current = current->left;
        }
        return current;
    }
    void printLevelOrder()
    {
        if (!root)
            return;

        queue<shared_ptr<Node>> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i)
            {
                auto node = q.front();
                q.pop();
                cout << node->val << " ";
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            cout << endl; // New line for each level
        }
    }

    void inorderPrint(shared_ptr<Node> node)
    {
        if (node)
        {
            inorderPrint(node->left);
            cout << node->val << " ";
            inorderPrint(node->right);
        }
    }
    void print()
    {
        inorderPrint(root);
    }
    void clean()
    {
        root = nullptr;
    }
};
#endif