#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

unordered_map<char, int> priority;

void init()
{
    priority['!'] = 7;
    priority['*'] = 6;
    priority['/'] = 6;
    priority['%'] = 6;
    priority['+'] = 5;
    priority['-'] = 5;
}

string infix_to_postfix(string s)
{
    string postfix = "";
    stack<char> temp;
    for (auto c : s)
    {
        if (c == '(')
        {
            temp.push(c);
        }
        else if (c == ')')
        {
            while (temp.top() != '(')
            {
                postfix += temp.top();
                temp.pop();
            }
            temp.pop();
        }
        else if (c == ' ')
        {
            continue;
        }
        else if (priority[c] == 0)
        {
            postfix += c;
        }
        else
        {
            while (!temp.empty() && priority[c] <= priority[temp.top()])
            {
                postfix += temp.top();
                temp.pop();
            }
            temp.push(c);
        }
    }
    while (!temp.empty())
    {
        postfix += temp.top();
        temp.pop();
    }
    return postfix;
}
int main()
{
    cout << "check" << endl;
    init();
    string test = "x+y*2";
    cout << infix_to_postfix(test) << endl;
}