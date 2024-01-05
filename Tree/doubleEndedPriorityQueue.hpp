#ifndef DoubleEndedPriorityQueue_hpp
#define DoubleEndedPriorityQueue_hpp
#include <vector>
class DEPQ
{
public:
    virtual void insert(int) = 0;
    virtual int getMin() = 0;
    virtual int getMax() = 0;
    virtual int deleteMin() = 0;
    virtual int deleteMax() = 0;
    virtual void clean() = 0;
    virtual void print() = 0;
};
#endif