#include <iostream>
#include <vector>
#include <string>
#include "../redBlackTree.hpp"
using namespace std;

int main()
{
    auto tree = RedBlackTree<int>(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    string command;
    int value;

    cout << "Deap CLI. Available commands: insert, remove, print, quit" << endl;

    while (true)
    {
        cout << "> ";
        cin >> command;

        if (command == "quit")
        {
            break;
        }
        else if (command == "insert")
        {
            cin >> value;
            tree.insert(value);
            cout << value << " inserted." << endl;
        }
        else if (command == "remove")
        {
            cin >> value;
            tree.remove(value);
            cout << value << " removed." << endl;
        }
        else if (command == "print")
        {
            tree.print();
        }
        else
        {
            cout << "Unknown command." << endl;
        }
    }

    cout << "Exiting Min-Max Heap CLI." << endl;
    return 0;
}