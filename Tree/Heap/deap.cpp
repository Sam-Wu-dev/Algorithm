#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "../doubleEndedPriorityQueue.hpp"
#include "../deap.hpp"

using namespace std;

int main()
{
    unique_ptr<DEPQ> test = make_unique<Deap>(vector<int>{2, 20, 12, 30, 40, 50, 60, 70});
    string command;
    int value;

    cout << "Deap CLI. Available commands: insert, getmin, getmax, deletemin, deletemax, print, quit" << endl;

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
            auto minValue = test->getMin();
            if (minValue.has_value())
            {
                cout << "Minimum value: " << minValue.value() << endl;
            }
            else
            {
                cout << "Heap is empty." << endl;
            }
        }
        else if (command == "getmax")
        {
            auto maxValue = test->getMax();
            if (maxValue.has_value())
            {
                cout << "Maximum value: " << maxValue.value() << endl;
            }
            else
            {
                cout << "Heap is empty." << endl;
            }
        }
        else if (command == "deletemin")
        {
            auto minValue = test->deleteMin();
            if (minValue.has_value())
            {
                cout << "Minimum value " << minValue.value() << " deleted." << endl;
            }
            else
            {
                cout << "Heap is empty or no minimum value to delete." << endl;
            }
        }
        else if (command == "deletemax")
        {
            auto maxValue = test->deleteMax();
            if (maxValue.has_value())
            {
                cout << "Maximum value " << maxValue.value() << " deleted." << endl;
            }
            else
            {
                cout << "Heap is empty or no maximum value to delete." << endl;
            }
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