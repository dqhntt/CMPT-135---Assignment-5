#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include "City.h"

#include <string>
#include <vector>

namespace util::file {

///////////////////////////////////////////////////////////////////////////////
//
// Description:
//    Parse data from a database file of `City` records.
// Pre-condition:
//    - `filename` points to a formatted existing file.
//      +) e.g. "../data/database.txt"
//    - All lines in file excluding headers have the following format:
//      +) city name, province abbreviation, province name,
//         latitude, longitude, population, population density
//      +) Use semicolons ';' as delimiters.
//      +) Have exactly 6 semicolons per line.
// Post-condition:
//    - Ignore `skip_lines` number of rows before parsing. Default is 1.
//    - Return a vector of all records in the file excluding last empty lines.
std::vector<City> read_data(const std::string& filename, int skip_lines = 1);

///////////////////////////////////////////////////////////////////////////////
//
// Description:
//    Write database records to file.
// Pre-condition:
//    - `filename` points to an existing file that can be overwritten.
//      +) e.g. "../data/database.txt"
// Post-condition:
//    - Overwrite existing file pointed to by `filename`.
//    - Semicolons ';' are used as delimiters.
//    - One header row will be created with the names of all fields.
//    - All lines after that will have the following format:
//      +) city name, province abbreviation, province name,
//         latitude, longitude, population, population density
//      +) Fields that are floating point numbers will have the
//         number of digits after the decimal point == `precision`. Default is 5.
void write_data(const std::vector<City>& data, const std::string& filename, int precision = 5);

} // namespace util::file

#endif // UTIL_FILE_H