#ifndef UTIL_H
#define UTIL_H

#include "util.file.h"
#include "util.RAII.h"

#include <string>

namespace util {

inline bool is_number(const std::string& str)
{
    try {
        const double n = std::stod(str);
        return (n == n); // NaN != NaN
    } catch (...) {
        return false;
    }
}

} // namespace util

#endif // UTIL_H