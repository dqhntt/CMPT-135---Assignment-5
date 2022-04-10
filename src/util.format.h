#ifndef UTIL_FORMAT_H
#define UTIL_FORMAT_H

#include <locale>
#include <ostream>

namespace util::format {

// Format numbers with commas while object is in scope.
// Reset to previous format once out of scope.
// e.g., outputs 10,000,000 instead of 10000000.
// https://en.cppreference.com/w/cpp/locale/locale
class Commas_thousands_separator {
public:
    // Format on given ostream.
    Commas_thousands_separator(std::ostream& target_ostream)
        : out(target_ostream) {
        out.imbue(std::locale("en_US.UTF8"));
    }
    // Reset format.
    ~Commas_thousands_separator() { out.imbue(std::locale()); }

private:
    std::ostream& out;
}; // class Commas_thousands_separator

} // namespace util::format

#endif // UTIL_FORMAT_H