#include <iostream>
#include <string>
using namespace std;
class Deque
{
    int *arr;
    int capacity;
    int front;
    int rear;
    int size;

public:
    Deque(int size)
    {
        arr = new int[size];
        capacity = size;
        front = 0;
        rear = 0;
        this->size = 0;
    }

    ~Deque()
    {
        delete[] arr;
    }

    void insertfront(int key);
    void insertrear(int key);
    void deletefront();
    void deleterear();
    bool isFull();
    bool isEmpty();
    int getFront();
    int getRear();
    void print();
};

void Deque::print()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "front: " << front << " rear: " << rear << endl;
}

bool Deque::isFull()
{
    return (size == capacity);
}

bool Deque::isEmpty()
{
    return (size == 0);
}

void Deque::insertfront(int key)
{
    if (isFull())
    {
        std::cout << "Deque is full" << std::endl;
        return;
    }
    if (size == 0)
    {
        rear = front;
    }
    front = (front - 1 + capacity) % capacity;
    arr[front] = key;
    size++;
}

void Deque::insertrear(int key)
{
    if (isFull())
    {
        std::cout << "Deque is full" << std::endl;
        return;
    }
    if (size == 0)
    {
        front = rear;
    }
    arr[rear] = key;
    rear = (rear + 1) % capacity;
    size++;
}

void Deque::deletefront()
{
    if (isEmpty())
    {
        std::cout << "Deque is empty" << std::endl;
        return;
    }
    arr[front] = -1;
    front = (front + 1) % capacity;
    size--;
}

void Deque::deleterear()
{
    if (isEmpty())
    {
        std::cout << "Deque is empty" << std::endl;
        return;
    }
    rear = (rear - 1 + capacity) % capacity;
    arr[rear] = -1;
    size--;
}

int Deque::getFront()
{
    if (isEmpty())
    {
        std::cout << "Deque is empty" << std::endl;
        return -1;
    }

    // If no element is inserted at the front, return the rear element
    return arr[front];
}

int Deque::getRear()
{
    if (isEmpty())
    {
        std::cout << "Deque is empty" << std::endl;
        return -1;
    }
    return arr[(rear - 1 + capacity) % capacity];
}

int main()
{
    Deque *dq = nullptr;
    string s;
    int n;
    while (cin >> s)
    {
        if (s == "q")
            break;
        if (s == "ir")
        {
            cin >> n;
            dq->insertrear(n);
            dq->print();
        }
        else if (s == "if")
        {
            cin >> n;
            dq->insertfront(n);
            dq->print();
        }
        else if (s == "dr")
        {
            dq->deleterear();
            dq->print();
        }
        else if (s == "df")
        {
            dq->deletefront();
            dq->print();
        }
        else if (s == "gr")
        {
            cout << dq->getRear() << endl;
        }
        else if (s == "gf")
        {
            cout << dq->getFront() << endl;
        }
        else if (s == "print")
        {
            dq->print();
        }
        else if (s == "init")
        {
            delete dq;
            cin >> n;
            dq = new Deque(n);
        }
        else
        {
            cout << "wrong input" << endl;
        }
    }

    return 0;
}
