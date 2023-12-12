#include <iostream>
#include <math.h>
using namespace std;

int modular_exponentiation(int b, int n, int m)
{
    int x = 1;
    int power = b % m;
    while (n > 0)
    {
        int current_bit = n % 2;
        n /= 2;
        if (current_bit == 1)
        {
            x = (x * power) % m;
        }
        power = (power * power) % m;
    }

    return x; // b^n mod m
}

int main()
{
    cout << modular_exponentiation(3, 644, 645) << endl;
    cout << int(pow(3, 644)) % 645 << endl;
}