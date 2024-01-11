#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <optional>

template <class T>
class BinarySearchTree
{
public:
    virtual void insert(T) = 0;
    virtual bool find(T) = 0;
    virtual bool remove(T) = 0;
    virtual void clean() = 0;
};

#endif // BINARYSEARCHTREE_HPP
