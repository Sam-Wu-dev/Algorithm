#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include "binarySearchTree.hpp"
#include <memory>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

template <class T>
struct Node
{
    int val;
    int height;
    shared_ptr<Node<T>> left;
    shared_ptr<Node<T>> right;
    Node(int val, int height) : val(val), height(height) {}
};

template <class T>
class AVLTree : public BinarySearchTree<T, Node<T>>
{
private:
    shared_ptr<Node<T>> LeftRotate(shared_ptr<Node<T>> now)
    {
        shared_ptr<Node<T>> temp = now->right;
        now->right = temp->left;
        temp->left = now;
        now->height = 1 + max(height(now->left), height(now->right));
        temp->height = 1 + max(height(temp->left), height(temp->right));
        return temp;
    }
    shared_ptr<Node<T>> RightRotate(shared_ptr<Node<T>> now)
    {
        shared_ptr<Node<T>> temp = now->left;
        now->left = temp->right;
        temp->right = now;
        now->height = 1 + max(height(now->left), height(now->right));
        temp->height = 1 + max(height(temp->left), height(temp->right));
        return temp;
    }
    int GetBalanceFactor(shared_ptr<Node<T>> node)
    {
        return height(node->left) - height(node->right);
    }

    shared_ptr<Node<T>> fixImbalance(shared_ptr<Node<T>> node)
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
        this->root = insertNode(this->root, val);
    }

    shared_ptr<Node<T>> insertNode(shared_ptr<Node<T>> node, T val)
    {
        if (!node)
        {
            return make_shared<Node<T>>(val, 1);
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

    int height(shared_ptr<Node<T>> node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    bool remove(T val)
    {
        bool removed = false;
        this->root = removeNode(this->root, val, removed);
        return removed;
    }

    shared_ptr<Node<T>> removeNode(shared_ptr<Node<T>> node, T val, bool &removed)
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
                shared_ptr<Node<T>> temp = node->left ? node->left : node->right;

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
                shared_ptr<Node<T>> successor = this->Successor(node);

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
};
#endif