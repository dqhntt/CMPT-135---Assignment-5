#include "util.h"
#include <cassert>
#include <iostream>
using namespace std;

void is_number_test()
{
    cout << "Testing " << __func__ << "() ...\n";
    using namespace util;
    
    assert(is_number("-1"));
    assert(is_number("-2.0"));
    assert(is_number("0"));
    assert(is_number("100.99"));

    assert(!is_number(""));
    assert(!is_number("Nanaimo"));
    assert(!is_number("six"));
    assert(!is_number("fifth")); // BUG: Fail for "5th".

    cout << "... " << __func__ << "() passed.\n";
}

int main()
{
    cout << "TEST SUITE:\n"
         << "  File: " << __FILE__ << "\n"
         << "  Date: " << __DATE__ << "\n"
         << "  Time: " << __TIME__ << "\n";

    is_number_test();
}
