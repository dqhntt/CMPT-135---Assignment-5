#include "Menu.h"
#include <iostream>
using namespace std;

void unit_test_something()
{
    cout << "Testing " << __func__ << "() ...\n";

    // TODO

    cout << "... " << __func__ << "() passed.\n";
}

int main()
{
    cout << "TEST SUITE:\n"
         << "  File: " << __FILE__ << "\n"
         << "  Date: " << __DATE__ << "\n"
         << "  Time: " << __TIME__ << "\n";

    // TODO

    unit_test_something();
}
