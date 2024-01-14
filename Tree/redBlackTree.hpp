#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#include "binarySearchTree.hpp"
#include <memory>
#include <vector>

using namespace std;

enum Color
{
    RED,
    BLACK
};

template <class T>
struct Node
{
    T val;                      // The value stored in the node
    shared_ptr<Node<T>> left;   // Pointer to the left child
    shared_ptr<Node<T>> right;  // Pointer to the right child
    shared_ptr<Node<T>> parent; // Pointer to the parent node
    Color color;                // Color of the node, either RED or BLACK

    // Constructor
    Node(T value) : val(value), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

template <class T>
class RedBlackTree : public BinarySearchTree<T, Node<T>>
{
private:
    void printWithSpacing(shared_ptr<Node<T>> node, int spacing)
    {
        cout << string(spacing / 2, ' ');
        if (node != nullptr)
            if (node->color == RED)
            {
                cout << '(' << node->val << ')';
            }
            else
            {
                cout << node->val;
            }

        else
            cout << " ";
        cout << string(spacing / 2, ' ');
    }
    void printLevel(queue<shared_ptr<Node<T>>> &q, int nodeCount, int level, int totalHeight)
    {
        int spacing = pow(2, totalHeight - level + 1);
        while (nodeCount > 0)
        {
            shared_ptr<Node<T>> node = q.front();
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
    shared_ptr<Node<T>> LeftRotate(shared_ptr<Node<T>> now)
    {
        shared_ptr<Node<T>> temp = now->right;
        now->right = temp->left;

        if (temp->left)
        {
            temp->left->parent = now;
        }

        temp->parent = now->parent;

        if (now->parent)
        {
            if (now == now->parent->left)
            {
                now->parent->left = temp;
            }
            else
            {
                now->parent->right = temp;
            }
        }

        temp->left = now;
        now->parent = temp;

        return temp;
    }

    shared_ptr<Node<T>> RightRotate(shared_ptr<Node<T>> now)
    {
        shared_ptr<Node<T>> temp = now->left;
        now->left = temp->right;

        if (temp->right)
        {
            temp->right->parent = now;
        }

        temp->parent = now->parent;

        if (now->parent)
        {
            if (now == now->parent->left)
            {
                now->parent->left = temp;
            }
            else
            {
                now->parent->right = temp;
            }
        }

        temp->right = now;
        now->parent = temp;

        return temp;
    }

    bool isLeftChild(shared_ptr<Node<T>> node)
    {
        if (node->parent->left == node)
            return true;
        return false;
    }
    Color color(shared_ptr<Node<T>> node)
    {
        if (!node)
            return BLACK;
        return node->color;
    }
    void fix(shared_ptr<Node<T>> node)
    {
        if (!node->parent)
        {
            node->color = BLACK;
            return;
        }

        if (node->parent->color == BLACK)
        {
            return;
        }

        auto grandparent = node->parent->parent;
        auto uncle = (node->parent == grandparent->left) ? grandparent->right : grandparent->left;

        if (color(uncle) == RED)
        {
            node->parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            fix(grandparent);
        }
        else
        {
            if (!isLeftChild(node) && isLeftChild(node->parent))
            {
                LeftRotate(node->parent);
                node = node->left;
            }
            else if (isLeftChild(node) && !isLeftChild(node->parent))
            {
                RightRotate(node->parent);
                node = node->right;
            }

            node->parent->color = BLACK;
            grandparent->color = RED;
            if (isLeftChild(node))
            {
                RightRotate(grandparent);
            }
            else
            {
                LeftRotate(grandparent);
            }
        }
    }
    void _insert(shared_ptr<Node<T>> node, T val)
    {
        if (val <= node->val)
        {
            if (node->left)
            {
                _insert(node->left, val);
            }
            else
            {
                node->left = make_shared<Node<T>>(val);
                node->left->parent = node;
                fix(node->left);
            }
        }
        else
        {
            if (node->right)
            {
                _insert(node->right, val);
            }
            else
            {
                node->right = make_shared<Node<T>>(val);
                node->right->parent = node;
                fix(node->right);
            }
        }
    }
    void _replaceNode(shared_ptr<Node<T>> oldNode, shared_ptr<Node<T>> newNode)
    {
        if (!oldNode->parent)
        {
            this->root = newNode;
        }
        else if (isLeftChild(oldNode))
        {
            oldNode->parent->left = newNode;
        }
        else
        {
            oldNode->parent->right = newNode;
        }
        if (newNode)
            newNode->parent = oldNode->parent;
    }
    void _fixRemove(shared_ptr<Node<T>> parent, bool isLeft)
    {
        if (!parent)
        {
            return;
        }
        auto now = isLeft ? parent->left : parent->right;
        while (now != this->root && color(now) == BLACK)
        {
            if (isLeft)
            {
                shared_ptr<Node<T>> sibling = parent->right;
                if (color(sibling) == RED)
                {
                    // Case 1: Sibling is red
                    sibling->color = BLACK;
                    parent->color = RED;
                    LeftRotate(parent);
                    sibling = parent->right;
                }

                if (color(sibling->left) == BLACK && color(sibling->right) == BLACK)
                {
                    // Case 2: Both of sibling's children are black
                    sibling->color = RED;
                    now = parent;
                    parent = now->parent;
                    isLeft = isLeftChild(now);
                }
                else
                {
                    if (color(sibling->right) == BLACK)
                    {
                        // Case 3: Right child of sibling is black
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        RightRotate(sibling);
                        sibling = parent->right;
                    }

                    // Case 4: Right child of sibling is red
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->right->color = BLACK;
                    LeftRotate(parent);
                    now = this->root;
                }
            }
            else
            {
                // Mirror cases for when now is the right child
                shared_ptr<Node<T>> sibling = parent->left;
                if (color(sibling) == RED)
                {
                    // Case 1: Sibling is red
                    sibling->color = BLACK;
                    parent->color = RED;
                    RightRotate(parent);
                    sibling = parent->left;
                }

                if (color(sibling->right) == BLACK && color(sibling->left) == BLACK)
                {
                    // Case 2: Both of sibling's children are black
                    sibling->color = RED;
                    now = parent;
                    parent = now->parent;
                    isLeft = isLeftChild(now);
                }
                else
                {
                    if (color(sibling->left) == BLACK)
                    {
                        // Case 3: Left child of sibling is black
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        LeftRotate(sibling);
                        sibling = parent->left;
                    }

                    // Case 4: Left child of sibling is red
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->left->color = BLACK;
                    RightRotate(parent);
                    now = this->root;
                }
            }
        }
        if (now != nullptr)
        {
            now->color = BLACK;
        }
    }

public:
    RedBlackTree(vector<T> arr)
    {
        for (auto &i : arr)
        {
            insert(i);
        }
    }
    void insert(T val)
    {
        if (!this->root)
        {
            this->root = make_shared<Node<T>>(val);
            this->root->color = BLACK; // Set the color of the root to BLACK
            return;
        }
        _insert(this->root, val);
        while (this->root->parent)
        {
            this->root = this->root->parent; // Keep updating the root until you reach the tree's actual root
        }
    }

    bool remove(T val)
    {
        auto deleteNode = this->_find(this->root, val);
        if (!deleteNode)
            return false;

        auto color = deleteNode->color;
        shared_ptr<Node<T>> fixNode, successor, parent;
        auto isLeft = false;
        if (!deleteNode->left && !deleteNode->right)
        {
            // Case 1: No children
            parent = deleteNode->parent;
            if (parent)
            {
                isLeft = isLeftChild(deleteNode);
            }
            fixNode = nullptr;
            _replaceNode(deleteNode, fixNode);
            return true;
        }
        else if (!deleteNode->left)
        {
            // Case 2: Only right child
            fixNode = deleteNode->right;
            _replaceNode(deleteNode, fixNode);
            isLeft = isLeftChild(fixNode);
            parent = fixNode->parent;
        }
        else if (!deleteNode->right)
        {
            // Case 3: Only left child
            fixNode = deleteNode->left;
            _replaceNode(deleteNode, fixNode);
            isLeft = isLeftChild(fixNode);
            parent = fixNode->parent;
        }
        else
        {
            // Case 4: Two children
            successor = this->Successor(deleteNode);
            color = successor->color;
            fixNode = successor->right;
            parent = successor->parent;
            isLeft = isLeftChild(successor);
            if (successor->parent == deleteNode)
            {
                if (fixNode)
                    fixNode->parent = successor;
            }
            else
            {
                _replaceNode(successor, successor->right);
                successor->right = deleteNode->right;
                successor->right->parent = successor;
            }

            _replaceNode(deleteNode, successor);
            successor->left = deleteNode->left;
            successor->left->parent = successor;
            successor->color = deleteNode->color;
        }

        if (color == BLACK)
        {
            _fixRemove(parent, isLeft);
        }
        while (this->root->parent)
        {
            this->root = this->root->parent; // Keep updating the root until you reach the tree's actual root
        }
        return true;
    }
    void print()
    {
        int h = this->height(this->root);
        queue<shared_ptr<Node<T>>> q;
        q.push(this->root);
        int level = 0;
        while (!q.empty() && level < h)
        {
            int nodeCount = q.size();
            printLevel(q, nodeCount, level, h);
            level++;
        }
    }
};

#endif