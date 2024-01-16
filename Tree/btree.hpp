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

    typename vector<T>::iterator _search(vector<T> &arr, T key)
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

        auto it = _search(node->keys, key);

        // Common method to insert key and child
        auto insert_into_node = [&](shared_ptr<Node<T>> &targetNode, T &insertKey, auto childNode)
        {
            auto newit = _search(targetNode->keys, insertKey);
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
            auto result = _insert(node->children[it - node->keys.begin()], key);
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
        auto now = root;
        while (now)
        {
            for (int i = 0; i < now->keys.size(); i++)
            {
                if (key == now->keys[i])
                {
                    return true;
                }
                else if (key < now->keys[i])
                {
                    now = now.children[i];
                }
            }
        }
        return false;
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
    bool remove(T key)
    {
        return false;
    }
};
#endif