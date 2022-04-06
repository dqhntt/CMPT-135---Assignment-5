#include "util.parse.h"
#include <cassert>
#include <iostream>
using namespace std;

void is_number_test() {
    cout << "Testing " << __func__ << "() ...\n";
    using namespace util::parse;

    assert(is_valid_num("-1"));
    assert(is_valid_num(" -2.0"));
    assert(is_valid_num(" 0 "));
    assert(is_valid_num("100.99 "));

    assert(!is_valid_num(""));
    assert(!is_valid_num("Nanaimo"));
    assert(!is_valid_num("six"));
    assert(!is_valid_num("5f"));
    assert(!is_valid_num("f5"));
    assert(!is_valid_num("5 f"));

    cout << "... " << __func__ << "() passed.\n";
}

void trim_test() {
    cout << "Testing " << __func__ << "() ...\n";
    using namespace util::parse;

    assert(trim("") == "");
    assert(trim("  ") == "");
    assert(trim("-") == "-");
    assert(trim(" don ") == "don");
    assert(trim(" d o") == "d o");
    assert(trim("So p ") == "So p");

    cout << "... " << __func__ << "() passed.\n";
}

void to_lower_test() {
    cout << "Testing " << __func__ << "() ...\n";
    using namespace util::parse;

    assert(to_lower("") == "");
    assert(to_lower("-") == "-");
    assert(to_lower("don't") == "don't");
    assert(to_lower("Don''T") == "don''t");
    assert(to_lower("DONT") == "dont");
    assert(to_lower("H.m m.M ") == "h.m m.m ");

    cout << "... " << __func__ << "() passed.\n";
}

void parse_yesno_test() {
    cout << "Testing " << __func__ << "() ...\n";
    using namespace util::parse;

    assert(convert_to_yesno_option("") == YesNo_Option::invalid_option);
    assert(convert_to_yesno_option("-") == YesNo_Option::invalid_option);
    assert(convert_to_yesno_option("Okay") == YesNo_Option::invalid_option);
    assert(convert_to_yesno_option("nah") == YesNo_Option::invalid_option);
    assert(convert_to_yesno_option("Y") == YesNo_Option::yes);
    assert(convert_to_yesno_option("y") == YesNo_Option::yes);
    assert(convert_to_yesno_option("yes") == YesNo_Option::yes);
    assert(convert_to_yesno_option("Yes") == YesNo_Option::yes);
    assert(convert_to_yesno_option("YES") == YesNo_Option::yes);
    assert(convert_to_yesno_option("N") == YesNo_Option::no);
    assert(convert_to_yesno_option("n") == YesNo_Option::no);
    assert(convert_to_yesno_option("No") == YesNo_Option::no);
    assert(convert_to_yesno_option("no") == YesNo_Option::no);
    assert(convert_to_yesno_option("NO") == YesNo_Option::no);

    cout << "... " << __func__ << "() passed.\n";
}

void parse_menu_test() {
    cout << "Testing " << __func__ << "() ...\n";
    using namespace util::parse;

    assert(convert_to_menu_option("") == Menu_Option::invalid_option);
    assert(convert_to_menu_option("-") == Menu_Option::invalid_option);
    assert(convert_to_menu_option("z") == Menu_Option::invalid_option);
    assert(convert_to_menu_option("On") == Menu_Option::invalid_option);
    assert(convert_to_menu_option("y") == Menu_Option::invalid_option);
    assert(convert_to_menu_option("1") == Menu_Option::one);
    assert(convert_to_menu_option("2") == Menu_Option::two);
    assert(convert_to_menu_option("3") == Menu_Option::three);
    assert(convert_to_menu_option("4") == Menu_Option::four);
    assert(convert_to_menu_option("5") == Menu_Option::five);
    assert(convert_to_menu_option("8", 8) == Menu_Option::eight);
    assert(convert_to_menu_option("twenty-two") != Menu_Option::two);
    assert(convert_to_menu_option("0") == Menu_Option::invalid_option);
    assert(convert_to_menu_option("5", 4) == Menu_Option::invalid_option);
    assert(convert_to_menu_option("6", 3) == Menu_Option::invalid_option);

    cout << "... " << __func__ << "() passed.\n";
}

int main() {
    cout << "TEST SUITE:\n"
         << "  File: " << __FILE__ << "\n"
         << "  Date: " << __DATE__ << "\n"
         << "  Time: " << __TIME__ << "\n";

    is_number_test();
    trim_test();
    to_lower_test();
    parse_yesno_test();
    parse_menu_test();
}
