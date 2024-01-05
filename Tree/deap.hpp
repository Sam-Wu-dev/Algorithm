#ifndef DEAP_HPP
#define DEAP_HPP
using namespace std;

#include "doubleEndedPriorityQueue.hpp"
#include "completeBinaryTree.hpp"

class Deap : public CompleteBinaryTree, public DEPQ
{
};
#endif