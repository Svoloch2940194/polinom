#include "polinom.h"

int main()
{
    Polinom a("x-1");
    Polinom  b("x+1");
    cout << a + b << endl;

    cout << a << endl << b << endl;
    Polinom c = a * b;
    cout << c << endl;
}

