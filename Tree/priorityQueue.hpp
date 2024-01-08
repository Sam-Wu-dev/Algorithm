#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <vector>
#include <optional>

class PriorityQueue
{
public:
    // Inserts a new element into the priority queue
    virtual void insert(int element) = 0;

    // Returns the minimum element without removing it (if exists)
    virtual std::optional<int> getTop() const = 0;

    // Returns and removes the minimum element (if exists)
    virtual std::optional<int> deleteTop() = 0;

    // Decreases the key value of a specific element (mainly for Fibonacci heaps)
    // virtual void decreaseKey(int oldKey, int newKey) = 0;
    virtual void merge(PriorityQueue &other) = 0;

    // Clears all elements from the priority queue
    virtual void clear() = 0;

    // Prints the elements of the priority queue (for debugging/testing)
    virtual void print() const = 0;
    virtual bool empty() const = 0;
};

#endif // PRIORITYQUEUE_HPP
