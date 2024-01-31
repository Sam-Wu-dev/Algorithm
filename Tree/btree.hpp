#ifndef BTREE_HPP
#define BTREE_HPP
#include <vector>
#include <utility>
#include <memory>
#include <queue>
using namespace std;

template <class T>
struct Node
{
    vector<T> keys;
    vector<shared_ptr<Node<T>>> children;
    Node() {}
    Node(T key)
    {
        keys.push_back(key);
    }
};
template <class T>
class Btree
{
private:
    shared_ptr<Node<T>> root;
    int m;
    int t;
    int mid;
    shared_ptr<Node<T>> _search(shared_ptr<Node<T>> now, T key)
    {
        while (now)
        {
            for (int i = 0; i < now->keys.size(); i++)
            {
                if (key == now->keys[i])
                {
                    return now;
                }
                else if (!now->children.empty() && key < now->keys[i])
                {
                    now = now->children[i];
                }
            }
            now = !now->children.empty() ? now->children.back() : nullptr;
        }
        return nullptr;
    }

public:
    Btree(int t, vector<T> arr)
    {
        this->t = t;
        this->m = 2 * t;
        this->mid = (m - 1) / 2;
        for (auto i : arr)
        {
            insert(i);
        }
    }
    pair<T, shared_ptr<Node<T>>> split(shared_ptr<Node<T>> origin)
    {
        auto newNode = make_shared<Node<T>>();

        // Directly assign the second half of keys to newNode
        newNode->keys.assign(origin->keys.begin() + mid + 1, origin->keys.end());
        origin->keys.erase(origin->keys.begin() + mid + 1, origin->keys.end());

        // Handle children if not empty
        if (!origin->children.empty())
        {
            newNode->children.assign(origin->children.begin() + mid + 1, origin->children.end());
            origin->children.erase(origin->children.begin() + mid + 1, origin->children.end());
        }

        auto midKey = origin->keys.back();
        origin->keys.pop_back();

        return {midKey, newNode};
    }
    void merge(shared_ptr<Node<T>> parent, int index)
    {
        shared_ptr<Node<T>> left = parent->children[index];
        shared_ptr<Node<T>> right = parent->children[index + 1];

        // Add the middle key from the parent to the end of the left child's keys
        left->keys.push_back(parent->keys[index]);

        // Append the keys from the right child to the left child
        left->keys.insert(left->keys.end(), right->keys.begin(), right->keys.end());

        // If the nodes have children, append the children from the right child to the left child
        if (!right->children.empty())
        {
            left->children.insert(left->children.end(), right->children.begin(), right->children.end());
        }

        // Remove the key and the right child from the parent
        parent->keys.erase(parent->keys.begin() + index);
        parent->children.erase(parent->children.begin() + index + 1);
    }

    typename vector<T>::iterator _find(vector<T> &arr, T key)
    {
        auto it = arr.begin();
        while (it != arr.end() && *it < key)
        {
            ++it;
        }
        return it;
    }
    pair<T, shared_ptr<Node<T>>> _insert(shared_ptr<Node<T>> &node, T key)
    {
        if (node == nullptr)
        {
            node = make_shared<Node<T>>();
            node->keys.push_back(key);
            return {T(), nullptr}; // Return an empty pair
        }

        auto it = _find(node->keys, key);
        int index = it - node->keys.begin();
        // Common method to insert key and child
        auto insert_into_node = [&](shared_ptr<Node<T>> &targetNode, T &insertKey, auto childNode)
        {
            auto newit = _find(targetNode->keys, insertKey);
            targetNode->keys.insert(newit, insertKey);

            size_t pos = newit - targetNode->keys.begin();
            pos = std::min(pos, targetNode->children.size());
            if (childNode)
            {
                targetNode->children.insert(targetNode->children.begin() + pos, childNode);
            }
        };

        // Node is a leaf
        if (node->children.empty())
        {
            if (node->keys.size() < m - 1)
            {
                node->keys.insert(it, key);
                return {T(), nullptr};
            }
            else
            {
                auto [midKey, newNode] = split(node);
                shared_ptr<Node<T>> targetNode = (key > midKey) ? newNode : node;
                insert_into_node(targetNode, key, nullptr);
                return {midKey, newNode};
            }
        }
        // Node is not a leaf
        else
        {
            auto result = _insert(node->children[index], key);
            if (result.second)
            {
                if (node->keys.size() < m - 1)
                {
                    insert_into_node(node, result.first, result.second);
                }
                else
                {
                    auto [midKey, newNode] = split(node);
                    shared_ptr<Node<T>> targetNode = (result.first > midKey) ? newNode : node;
                    insert_into_node(targetNode, result.first, result.second);
                    return {midKey, newNode};
                }
            }
        }
        return {T(), nullptr};
    }

    void insert(T key)
    {
        if (root == nullptr)
        {
            // Tree is initially empty. Create a new root node.
            root = make_shared<Node<T>>();
            root->keys.push_back(key);
            return;
        }
        auto result = _insert(root, key);
        if (result.second)
        {
            // Root was split, create new root
            auto newRoot = make_shared<Node<T>>();
            newRoot->keys.push_back(result.first);
            newRoot->children.push_back(root);
            newRoot->children.push_back(result.second);
            root = newRoot;
        }
    }
    bool search(T key)
    {
        return _search(root, key) != nullptr;
    }
    bool _remove(shared_ptr<Node<T>> node, T key)
    {
        if (!node)
            return false;

        auto it = _find(node->keys, key);
        bool found = (it != node->keys.end() && *it == key);
        int index = it - node->keys.begin();

        if (found)
        {
            if (node->children.empty())
            {
                // Leaf node
                node->keys.erase(it);
                return true;
            }
            else
            {
                // Internal node
                auto left = node->children[index];
                auto right = node->children[index + 1];

                if (left->keys.size() >= t)
                {
                    // Predecessor key
                    T predecessor = left->keys.back();
                    node->keys[index] = predecessor;
                    return _remove(left, predecessor);
                }
                else if (right->keys.size() >= t)
                {
                    // Successor key
                    T successor = right->keys.front();
                    node->keys[index] = successor;
                    return _remove(right, successor);
                }
                else
                {
                    // Merge left and right
                    merge(node, index);
                    node->keys.erase(node->keys.begin() + index);
                    node->children.erase(node->children.begin() + index + 1);
                    return _remove(left, key);
                }
            }
        }
        else
        {
            if (node->children.empty())
            {
                // Key not found in leaf
                return false;
            }
            // Key might be in the subtree
            bool atLastKey = (index == node->keys.size());
            // Key in the subtree
            if (node->children[index]->keys.size() < t)
            {
                // Rebalance before going deeper

                shared_ptr<Node<T>> child = node->children[index];
                shared_ptr<Node<T>> leftSibling = (index > 0) ? node->children[index - 1] : nullptr;
                shared_ptr<Node<T>> rightSibling = (index < node->keys.size()) ? node->children[index + 1] : nullptr;

                if (leftSibling && leftSibling->keys.size() >= t)
                {
                    // Borrow from the left sibling
                    child->keys.insert(child->keys.begin(), node->keys[index - 1]);
                    node->keys[index - 1] = leftSibling->keys.back();
                    leftSibling->keys.pop_back();

                    if (!leftSibling->children.empty())
                    {
                        child->children.insert(child->children.begin(), leftSibling->children.back());
                        leftSibling->children.pop_back();
                    }
                }
                else if (rightSibling && rightSibling->keys.size() >= t)
                {
                    // Borrow from the right sibling
                    child->keys.push_back(node->keys[index]);
                    node->keys[index] = rightSibling->keys.front();
                    rightSibling->keys.erase(rightSibling->keys.begin());

                    if (!rightSibling->children.empty())
                    {
                        child->children.push_back(rightSibling->children.front());
                        rightSibling->children.erase(rightSibling->children.begin());
                    }
                }
                else
                {
                    // Merge with a sibling
                    if (leftSibling)
                    {
                        merge(node, index - 1);
                    }
                    else if (rightSibling)
                    {
                        merge(node, index);
                    }
                }
                if (atLastKey && index > node->keys.size())
                {
                    // If the key was in the last position, but a merge happened
                    return _remove(node->children[index - 1], key);
                }
                else
                {
                    return _remove(node->children[index], key);
                }
            }
            else
            {
                return _remove(node->children[index], key);
            }
        }

        return true;
    }
    bool remove(T key)
    {
        if (!root)
            return false;

        bool result = _remove(root, key);

        if (!result)
        {
            return false; // Key was not found in the tree
        }

        if (root->keys.empty())
        {
            // After removal, if the root is empty
            if (root->children.empty())
            {
                // The tree is now empty
                root = nullptr;
            }
            else
            {
                // The root has only one child, make this child the new root
                root = root->children[0];
            }
        }

        return true;
    }

    void _printNode(shared_ptr<Node<T>> node)
    {
        cout << "keys: ";
        for (auto i : node->keys)
        {
            cout << i << " ";
        }
        cout << endl
             << "children: ";
        for (auto i : node->children)
        {
            cout << i->keys[0] << " ";
        }
        cout << endl;
    }
    void printTree()
    {
        if (root == nullptr)
        {
            std::cout << "The tree is empty." << std::endl;
            return;
        }

        std::queue<shared_ptr<Node<T>>> queue;
        queue.push(root);

        while (!queue.empty())
        {
            size_t levelSize = queue.size();

            for (size_t i = 0; i < levelSize; ++i)
            {
                shared_ptr<Node<T>> currentNode = queue.front();
                queue.pop();

                // Print all keys in the current node
                for (T key : currentNode->keys)
                {
                    std::cout << key << " ";
                }
                std::cout << "| "; // Separator between nodes at the same level

                // Enqueue children of the current node
                for (auto &child : currentNode->children)
                {
                    if (child != nullptr)
                    {
                        queue.push(child);
                    }
                }
            }

            std::cout << std::endl; // New line after each level
        }
    }
};
#endif