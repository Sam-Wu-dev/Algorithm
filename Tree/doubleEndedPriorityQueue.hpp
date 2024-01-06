#ifndef DoubleEndedPriorityQueue_hpp
#define DoubleEndedPriorityQueue_hpp
#include <vector>
#include <optional>
class DEPQ
{
public:
    virtual void insert(int) = 0;
    virtual std::optional<int> getMin() = 0;
    virtual std::optional<int> getMax() = 0;
    virtual std::optional<int> deleteMin() = 0;
    virtual std::optional<int> deleteMax() = 0;
    virtual void clean() = 0;
    virtual void print() = 0;
};
#endif