#ifndef UTIL_PARSE_H
#define UTIL_PARSE_H

#include "Menu.h"
#include <sstream>
#include <string>

namespace util::parse {

Menu_Option convert_to_menu_option(const std::string& input, int max_options);
YesNo_Option convert_to_yesno_option(const std::string& input);

namespace ncurses {
    Menu_Option convert_to_menu_option(const std::string& input);
    YesNo_Option convert_to_yesno_option(const std::string& input);
} // namespace ncurses

// Trim str in-place.
const std::string& trim(std::string& str);
// Return trimmed str.
std::string trim(const std::string& str);
std::string to_lower(const std::string& str);
bool is_valid_DD_latitude(const std::string& str);
bool is_valid_DD_longitude(const std::string& str);

/**
 * @details
 * If function returns true, `str` can be fed to stoi and stod with no exception.
 * If returns false, stoi and stod may throw exceptions when converting `str`.
 *
 * Default template type of number is double.
 * Default second parameter is only for instantiating templates.
 */
template <typename Num_Type = double>
bool is_valid_num(const std::string& str, Num_Type = Num_Type()) {
    std::istringstream iss(str);
    Num_Type test_num;
    char test_char;
    // True if assignable to test_num and no remaining char after extraction.
    return (iss >> test_num) && !(iss >> test_char);
}

} // namespace util::parse

#endif // UTIL_PARSE_H