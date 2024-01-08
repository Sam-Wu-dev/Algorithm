#ifndef BINOMIALHEAP
#define BINOMIALHEAP
#include <memory>
#include <vector>
#include <queue>
#include <iostream>
#include <functional>
#include "priorityQueue.hpp"

using namespace std;

class BinomialNode
{
public:
    int value;
    int degree;
    shared_ptr<BinomialNode> parent;
    shared_ptr<BinomialNode> child;
    shared_ptr<BinomialNode> sibling;
    BinomialNode(int val) : value(val), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
    // Constructor and other methods...
};

class BinomialHeap : public PriorityQueue
{

private:
    shared_ptr<BinomialNode> head;
    function<bool(int, int)> comp;
    void linkTrees(shared_ptr<BinomialNode> node1, shared_ptr<BinomialNode> node2)
    {
        if (!comp(node1->value, node2->value))
        {
            swap(node1, node2);
        }
        node2->parent = node1;
        node2->sibling = node1->child;
        node1->child = node2;
        node1->degree++;
    }
    void printBinomialTree(shared_ptr<BinomialNode> root) const
    {
        std::queue<shared_ptr<BinomialNode>> queue;
        queue.push(root);

        while (!queue.empty())
        {
            auto current = queue.front();
            queue.pop();

            // Print current node
            std::cout << current->value << " ";

            // Add all children of the current node to the queue
            auto child = current->child;
            while (child)
            {
                queue.push(child);
                child = child->sibling;
            }
        }
    }
    shared_ptr<BinomialNode> mergeRootLists(shared_ptr<BinomialNode> head1, shared_ptr<BinomialNode> head2)
    {
        shared_ptr<BinomialNode> newhead, prev, next;
        auto temp1 = head1, temp2 = head2;

        while (temp1 && temp2)
        {
            if (temp1->degree <= temp2->degree)
            {
                next = temp1;
                temp1 = temp1->sibling;
            }
            else
            {
                next = temp2;
                temp2 = temp2->sibling;
            }

            if (!prev)
            {
                newhead = next;
            }
            else
            {
                prev->sibling = next;
            }
            prev = next;
        }

        // Attach the remaining part of the list which is not yet processed
        prev->sibling = (temp1) ? temp1 : temp2;
        return newhead;
    }

    void consolidate(shared_ptr<BinomialNode> &head, function<bool(int, int)> comp)
    {
        if (!head)
            return;

        shared_ptr<BinomialNode> prev = nullptr, curr = head, nextNode = curr->sibling;
        while (nextNode)
        {
            if (curr->degree != nextNode->degree || (nextNode->sibling && nextNode->sibling->degree == curr->degree))
            {
                prev = curr;
                curr = nextNode;
            }
            else
            {
                if (comp(curr->value, nextNode->value))
                {
                    curr->sibling = nextNode->sibling;
                    linkTrees(curr, nextNode);
                }
                else
                {
                    if (!prev)
                    {
                        head = nextNode;
                    }
                    else
                    {
                        prev->sibling = nextNode;
                    }
                    linkTrees(nextNode, curr);
                    curr = nextNode;
                }
            }
            nextNode = curr->sibling;
        }
    }

public:
    BinomialHeap(shared_ptr<BinomialNode> newHead, function<bool(int, int)> comparisonFunc) : head(newHead), comp(comparisonFunc) {}
    BinomialHeap(vector<int> arr, function<bool(int, int)> comparisonFunc) : comp(comparisonFunc)
    {
        for (auto i : arr)
        {
            insert(i);
        }
    }
    BinomialHeap(function<bool(int, int)> comparisonFunc) : comp(comparisonFunc), head(nullptr) {}
    void insert(int element) override
    {
        shared_ptr<BinomialNode> newNode = make_shared<BinomialNode>(element);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            BinomialHeap tempHeap(comp);
            tempHeap.head = newNode;
            merge(tempHeap);
        }
    }

    // Returns the minimum element without removing it (if exists)
    std::optional<int> getTop() const override
    {
        if (!head)
            return nullopt;
        int best = head->value;
        auto iter = head->sibling;
        while (iter)
        {
            if (comp(iter->value, best))
            {
                best = iter->value;
            }
            iter = iter->sibling;
        }
        return best;
    }

    // Returns and removes the minimum element (if exists)
    std::optional<int> deleteTop() override
    {
        if (!head)
        {
            return std::nullopt; // Heap is empty
        }

        // Find the tree with the minimum root
        auto prevTop = head, top = head, current = head;
        int topValue = head->value;
        while (current->sibling)
        {
            if (comp(current->sibling->value, topValue))
            {
                topValue = current->sibling->value;
                prevTop = current;
                top = current->sibling;
            }
            current = current->sibling;
        }

        // Remove the tree with the minimum root from the heap
        if (prevTop == head && top == head)
        {
            head = head->sibling;
        }
        else
        {
            prevTop->sibling = top->sibling;
        }

        // Create a new heap from the children of the removed root
        shared_ptr<BinomialNode> newHead = nullptr, child = top->child;
        while (child)
        {
            auto nextChild = child->sibling;
            child->sibling = newHead;
            child->parent = nullptr;
            newHead = child;
            child = nextChild;
        }

        BinomialHeap tempHeap(newHead, comp);
        merge(tempHeap);

        return topValue;
    }
    void merge(PriorityQueue &other)
    {
        auto otherHeapPtr = dynamic_cast<BinomialHeap *>(&other);
        if (!otherHeapPtr)
            return; // Type mismatch, cannot merge

        auto &otherHeap = *otherHeapPtr;
        if (!otherHeap.head)
            return; // Other heap is empty, nothing to merge
        if (!head)
        {
            head = otherHeap.head; // Current heap is empty, just take the other heap
            otherHeap.head = nullptr;
            return;
        }

        head = mergeRootLists(head, otherHeap.head);
        consolidate(head, comp);
        otherHeap.head = nullptr; // Clear the other heap
    }

    // Clears all elements from the priority queue
    void clear()
    {
        head = nullptr;
    }

    bool empty() const
    {
        return head == nullptr;
    }

    // Prints the elements of the priority queue (for debugging/testing)
    void print() const
    {
        shared_ptr<BinomialNode> current = head;
        while (current)
        {
            printBinomialTree(current);
            current = current->sibling;
        }
        std::cout << std::endl;
    }
};
#endif