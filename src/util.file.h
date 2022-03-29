#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include "City.h"

#include <string>
#include <vector>

namespace util::file {

std::vector<City> read_data(const std::string& filename);
void              write_data(const std::vector<City>& data, const std::string& filename);

} // namespace util::file

#endif // UTIL_FILE_H