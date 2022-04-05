#include "util.parse.h"
#include "cmpt_error.h"
#include <algorithm>
#include <cctype>
using namespace std;

string util::parse::retrieve_data(const City& city, const Field& field) {
    switch (field) {
    case Field::city_name:
        return city.name;
    case Field::province:
        return city.province;
    case Field::province_id:
        return city.province_id;
    default:
        cmpt::error("Not a valid string field in " + string(__func__) + "()");
    }
    return "";
}

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
string util::parse::trim(const string& str) {
    auto is_space = [](unsigned char c) -> bool { return std::isspace(c); };
    auto first_not_space = find_if_not(str.begin(), str.end(), is_space);
    auto last_not_space = find_if_not(str.rbegin(), str.rend(), is_space).base();
    return (first_not_space >= last_not_space) ? "" : string(first_not_space, last_not_space);
}

const string& util::parse::trim(string& str) {
    auto       is_space = [](unsigned char c) -> bool { return std::isspace(c); };
    const auto last_not_space = find_if_not(str.rbegin(), str.rend(), is_space).base();
    str.erase(last_not_space, str.end());
    const auto first_not_space = find_if_not(str.begin(), str.end(), is_space);
    str.erase(str.begin(), first_not_space);
    return str;
}

string util::parse::to_lower(const string& str) {
    string lower(str);
    for (char& c : lower) {
        c = tolower(c);
    }
    return lower;
}

YesNo_Options util::parse::convert_to_yesno_option(const string& input) {
    const string lowercase_input = to_lower(trim(input));
    return (lowercase_input == "y" || lowercase_input == "yes" || lowercase_input == "1")
        ? YesNo_Options::yes
        : (lowercase_input == "n" || lowercase_input == "no" || lowercase_input == "0")
        ? YesNo_Options::no
        : YesNo_Options::invalid_option;
}

Menu_Options util::parse::convert_to_menu_option(const string& input, int max_options) {
    const string lowercase_input = to_lower(trim(input));
    switch (max_options) {
    case 8:
        if (lowercase_input == "8" || lowercase_input == "eight")
            return Menu_Options::eight;
        [[fallthrough]];
    case 7:
        if (lowercase_input == "7" || lowercase_input == "seven")
            return Menu_Options::seven;
        [[fallthrough]];
    case 6:
        if (lowercase_input == "6" || lowercase_input == "six")
            return Menu_Options::six;
        [[fallthrough]];
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
