#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../btree.hpp"
using namespace std;

int main()
{
    // auto test = Btree<int>(2, vector<int>{});
    // auto node = make_shared<Node<int>>();
    // vector<int> keys{0, 1, 2};
    // node->keys = keys;
    // auto newNode = test.split(node);
    // test._printNode(node);
    // test._printNode(newNode);
    auto tree = Btree<int>(2, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1});
    tree.printTree();
    // string command;
    // int value;

    // cout << "Btree CLI. Available commands: insert, remove, print, quit" << endl;

    // while (true)
    // {
    //     cout << "> ";
    //     cin >> command;

    //     if (command == "quit")
    //     {
    //         break;
    //     }
    //     else if (command == "insert")
    //     {
    //         cin >> value;
    //         tree.insert(value);
    //         cout << value << " inserted." << endl;
    //     }
    //     else if (command == "remove")
    //     {
    //         cin >> value;
    //         tree.remove(value);
    //         cout << value << " removed." << endl;
    //     }
    //     else if (command == "print")
    //     {
    //         // tree.print();
    //     }
    //     else
    //     {
    //         cout << "Unknown command." << endl;
    //     }
    // }

    // cout << "Exiting Min-Max Heap CLI." << endl;
    // return 0;
}