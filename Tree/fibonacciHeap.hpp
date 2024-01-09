#ifndef FIBONACCIHEAP_HPP
#define FIBONACCIHEAP_HPP

#include <memory>
#include <vector>
#include <queue>
#include <iostream>
#include <functional>
#include <optional>

using namespace std;

class FibonacciNode
{
public:
    int value;
    int degree;
    bool mark;
    shared_ptr<FibonacciNode> parent, child, sibling, pre;

    FibonacciNode(int val) : value(val), degree(0), mark(false), parent(nullptr), child(nullptr), sibling(nullptr), pre(nullptr) {}
    // Additional methods...
};

class FibonacciHeap
{
private:
    shared_ptr<FibonacciNode> head;
    function<bool(int, int)> comp;
    int n; // Number of nodes in the heap

    void join(shared_ptr<FibonacciNode> node)
    {
        if (!head)
        {
            head = node;
            head->sibling = head;
            head->pre = head;
        }
        else
        {
            // Insert node into the root list
            node->sibling = head->sibling;
            head->sibling->pre = node;
            node->pre = head;
            head->sibling = node;

            // Update head if the new node has a smaller value
            if (comp(node->value, head->value))
            {
                head = node;
            }
        }
    }

    void remove(shared_ptr<FibonacciNode> node)
    {
        if (node->sibling == node) // Node is the only node in its list
        {
            if (node->parent)
                node->parent->child = nullptr;
        }
        else
        {
            node->pre->sibling = node->sibling;
            node->sibling->pre = node->pre;
            if (node->parent && node->parent->child == node)
                node->parent->child = node->sibling;
        }
        node->parent = nullptr;
        node->mark = false;
    }
    void cut(shared_ptr<FibonacciNode> child, shared_ptr<FibonacciNode> parent)
    {
        // Remove child from the child list of the parent
        if (parent->child == child)
        {
            // If the child is the only child or is the starting point of the child list
            if (child->sibling == child)
            {
                parent->child = nullptr; // If it's the only child
            }
            else
            {
                parent->child = child->sibling; // Move the parent's child pointer to the next sibling
            }
        }

        // If child is not the only child, update the siblings
        if (child->sibling != child)
        {
            child->pre->sibling = child->sibling;
            child->sibling->pre = child->pre;
        }

        // Now that child is removed from its sibling list, reset its sibling and pre pointers
        child->sibling = child;
        child->pre = child;

        // Add child to the root list of the heap using join
        join(child);

        // Clear the parent pointer and unmark the child, as it's now in the root list
        child->parent = nullptr;
        child->mark = false;

        // Decrease the degree of the parent node
        parent->degree--;
    }

    void cascadingCut(shared_ptr<FibonacciNode> node)
    {
        auto parentNode = node->parent;
        if (parentNode)
        {
            if (node->mark)
            {
                cut(node, parentNode);
                cascadingCut(parentNode);
            }
            else
            {
                node->mark = true;
            }
        }
    }

    void linkTrees(shared_ptr<FibonacciNode> node1, shared_ptr<FibonacciNode> node2)
    {
        if (!comp(node1->value, node2->value))
        {
            swap(node1, node2);
        }
        remove(node2);

        if (!node1->child)
        {
            node1->child = node2;
            node2->pre = node2->sibling = node2;
        }
        else
        {
            node2->sibling = node1->child;
            node2->pre = node1->child->pre;
            node1->child->pre->sibling = node2;
            node1->child->pre = node2;
        }
        node1->degree++;
    }

    void mergeRootLists(shared_ptr<FibonacciNode> &head1, shared_ptr<FibonacciNode> &head2)
    {
        if (!head1 || !head2)
            return; // Safety check if one of the lists is empty

        auto head1Last = head1->pre;
        auto head2Last = head2->pre;

        head1Last->sibling = head2;
        head2->pre = head1Last;

        head2Last->sibling = head1;
        head1->pre = head2Last;
    }

    void consolidate()
    {
        vector<shared_ptr<FibonacciNode>> degreeTable;
        vector<shared_ptr<FibonacciNode>> rootList;

        // Populate rootList with the nodes in the current root list
        if (head != nullptr)
        {
            auto current = head;
            do
            {
                rootList.push_back(current);
                current = current->sibling;
            } while (current != head);
        }

        for (auto w : rootList) // lazy combine
        {
            auto x = w;
            auto d = x->degree;
            while (degreeTable.size() > d && degreeTable[d] != nullptr)
            {
                auto y = degreeTable[d];
                if (comp(y->value, x->value))
                {
                    swap(x, y);
                }
                linkTrees(x, y);
                degreeTable[d] = nullptr;
                d++;
            }
            if (degreeTable.size() <= d)
            {
                degreeTable.resize(d + 1);
            }
            degreeTable[d] = x;
        }

        // Reconstruct the root list from the degree table
        head = nullptr;
        for (auto node : degreeTable)
        {
            if (node != nullptr)
            {
                join(node); // Use the join function to add the node to the root list
            }
        }
    }

public:
    FibonacciHeap(shared_ptr<FibonacciNode> newHead, function<bool(int, int)> comparisonFunc) : head(newHead), comp(comparisonFunc) {}
    FibonacciHeap(function<bool(int, int)> comparisonFunc) : comp(comparisonFunc) {}
    shared_ptr<FibonacciNode> insert(int element)
    {
        auto newNode = make_shared<FibonacciNode>(element);
        join(newNode);
        n++; // Increase the number of nodes in the heap
        return newNode;
    }

    std::optional<int> getTop() const
    {
        if (!head)
        {
            return std::nullopt;
        }
        return head->value; // Constant time access to the minimum element
    }

    // Returns and removes the minimum element (if exists)
    std::optional<int> deleteTop()
    {
        if (!head)
            return std::nullopt;

        // Remove the minimum node
        int minValue = head->value;
        auto minNode = head;
        if (head == head->sibling)
        {
            head = nullptr;
        }
        else
        {
            head->pre->sibling = head->sibling;
            head->sibling->pre = head->pre;
            head = head->sibling;
        }

        // Add the children of the minimum node to the root list
        if (minNode->child)
        {
            auto child = minNode->child;
            do
            {
                auto next = child->sibling;
                child->parent = nullptr; // Clear parent pointer
                child->sibling = child;  // Disconnect the child from its siblings
                child->pre = child;      // Set child as a singular node in preparation for join

                join(child); // Use the join function to add the child to the root list

                child = next;
            } while (child != minNode->child);
        }

        // Pairwise combine
        consolidate();

        // Find new minimum
        if (head)
        {
            auto newMin = head;
            auto curr = head->sibling;
            while (curr != head)
            {
                if (comp(curr->value, newMin->value))
                {
                    newMin = curr;
                }
                curr = curr->sibling;
            }
            head = newMin;
        }

        return minValue;
    }

    void levelUpKey(shared_ptr<FibonacciNode> targetNode, int newKey)
    {
        if (!targetNode)
        {
            throw std::invalid_argument("Key is deleted.");
        }
        if (comp(targetNode->value, newKey))
        {
            throw std::invalid_argument("New key is greater than old key.");
        }

        targetNode->value = newKey;
        auto parentNode = targetNode->parent;

        if (parentNode && comp(targetNode->value, parentNode->value))
        {
            cut(targetNode, parentNode);
            cascadingCut(parentNode);
        }

        if (comp(targetNode->value, head->value))
        {
            head = targetNode;
        }
    }

    void merge(FibonacciHeap &other)
    {
        if (!other.head)
            return; // Other heap is empty, nothing to merge

        if (!head)
        {
            head = other.head; // Current heap is empty, just take the other heap
        }
        else
        {
            mergeRootLists(head, other.head);
            consolidate(); // Consolidate only if both heaps were non-empty
        }

        other.head = nullptr; // Clear the other heap
    }

    // Clears all elements from the priority queue
    void clear()
    {
        head = nullptr;
    }

    // Prints the elements of the priority queue (for debugging/testing)
    void print() const {}

    bool empty() const
    {
        return head == nullptr;
    }
};
#endif