#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "../heap.hpp"

using namespace std;

int main()
{
    auto test = MaxHeap(vector<int>{2, 20, 12, 30, 40, 50, 60, 70});
    string command;
    int value;

    cout << "Max Heap CLI. Available commands: insert, getmin, getmax, deletemin, deletemax, print, quit" << endl;

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
            test.insert(value);
            cout << value << " inserted." << endl;
        }
        else if (command == "getmax")
        {
            auto minValue = test.getTop();
            if (minValue.has_value())
            {
                cout << "Maximum value: " << minValue.value() << endl;
            }
            else
            {
                cout << "Heap is empty." << endl;
            }
        }
        else if (command == "deletemax")
        {
            auto minValue = test.deleteTop();
            if (minValue.has_value())
            {
                cout << "Maximum value " << minValue.value() << " deleted." << endl;
            }
            else
            {
                cout << "Heap is empty or no maximum value to delete." << endl;
            }
        }
        else if (command == "print")
        {
            test.print();
        }
        else
        {
            cout << "Unknown command." << endl;
        }
    }

    cout << "Exiting Max Heap CLI." << endl;
    return 0;
}