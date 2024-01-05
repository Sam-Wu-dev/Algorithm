#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "../doubleEndedPriorityQueue.hpp"
#include "../minMaxHeap.hpp"

using namespace std;

int main()
{
    unique_ptr<DEPQ> test = make_unique<MinMaxHeap>(vector<int>{2, 20, 12}); // Assuming default constructor exists
    string command;
    int value;

    cout << "Min-Max Heap CLI. Available commands: insert, getmin, getmax, deletemin, deletemax, print, quit" << endl;

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
            test->insert(value);
            cout << value << " inserted." << endl;
        }
        else if (command == "getmin")
        {
            cout << "Minimum value: " << test->getMin() << endl;
        }
        else if (command == "getmax")
        {
            cout << "Maximum value: " << test->getMax() << endl;
        }
        else if (command == "deletemin")
        {
            test->deleteMin();
            cout << "Minimum value deleted." << endl;
        }
        else if (command == "deletemax")
        {
            test->deleteMax();
            cout << "Maximum value deleted." << endl;
        }
        else if (command == "print")
        {
            test->print();
        }
        else
        {
            cout << "Unknown command." << endl;
        }
    }

    cout << "Exiting Min-Max Heap CLI." << endl;
    return 0;
}