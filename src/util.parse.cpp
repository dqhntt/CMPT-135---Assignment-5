#include "util.parse.h"

#include <algorithm>
#include <cctype>
using namespace std;

// See: https://en.wikipedia.org/wiki/Decimal_degrees
bool util::parse::is_valid_DD_latitude(const string& str) {
    return is_valid_num<double>(str) && (stod(str) <= 90.0) && (stod(str) >= -90.0);
}

bool util::parse::is_valid_DD_longitude(const string& str) {
    return is_valid_num<double>(str) && (stod(str) <= 180.0) && (stod(str) >= -180.0);
}

// This version uses lambda and forward/reverse iterators.
// Ref: https://en.cppreference.com/w/cpp/string/byte/isspace
//      https://stackoverflow.com/a/2038101
string util::parse::trimmed(const string& str) {
    auto is_space = [](unsigned char c) -> bool { return std::isspace(c); };
    auto first_not_space = find_if_not(str.begin(), str.end(), is_space);
    auto last_not_space = find_if_not(str.rbegin(), str.rend(), is_space).base();
    return (first_not_space >= last_not_space) ? "" : string(first_not_space, last_not_space);
}

string util::parse::to_lower(const string& str) {
    string lower(str);
    for (char& c : lower) {
        c = tolower(c);
    }
    return lower;
}

YesNo_Options util::parse::convert_to_yesno_option(const string& input) {
    const string lowercase_input = to_lower(trimmed(input));
    return (lowercase_input == "y" || lowercase_input == "yes" || lowercase_input == "1")
        ? YesNo_Options::yes
        : (lowercase_input == "n" || lowercase_input == "no" || lowercase_input == "0")
        ? YesNo_Options::no
        : YesNo_Options::invalid_option;
}

Menu_Options util::parse::convert_to_menu_option(const string& input, int max_options) {
    const string lowercase_input = to_lower(trimmed(input));
    switch (max_options) {
    case 5:
        if (lowercase_input == "5" || lowercase_input == "five")
            return Menu_Options::five;
        [[fallthrough]];
    case 4:
        if (lowercase_input == "4" || lowercase_input == "four")
            return Menu_Options::four;
        [[fallthrough]];
    case 3:
        if (lowercase_input == "3" || lowercase_input == "three")
            return Menu_Options::three;
        [[fallthrough]];
    case 2:
        if (lowercase_input == "2" || lowercase_input == "two")
            return Menu_Options::two;
        [[fallthrough]];
    case 1:
        if (lowercase_input == "1" || lowercase_input == "one")
            return Menu_Options::one;
        [[fallthrough]];
    default:;
    }
    return Menu_Options::invalid_option;
}
