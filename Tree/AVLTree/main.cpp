#include <iostream>
#include <vector>
#include "../avlTree.hpp"
using namespace std;

int main()
{
    auto tree = AVLTree<int>(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    tree.remove(6);
    tree.printLevelOrder();
    cout << tree.find(6);
}