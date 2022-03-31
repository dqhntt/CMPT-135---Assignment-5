#ifndef DATABASE_H
#define DATABASE_H

#include "City.h"
#include <string>
#include <vector>

// TODO: Implement this class.

class Database {
public:

    Database() = default;

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Pre-condition:
    //    File I/O permissions are granted.
    // Post-condition:
    //    File at `db_filename` is opened and loaded into memory.
    Database(const std::string& db_filename);

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Pre-condition:
    //    File I/O permissions are granted.
    // Post-condition:
    //    Loaded file is overwritten with current data in memory.
    ~Database();

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Pre-condition:
    //    File I/O permissions are granted.
    // Post-condition:
    //    Loaded file, if any, is overwritten with current data in memory.
    //    File at `target_filename` is opened and loaded into memory.
    void open(const std::string& target_filename);

    // TODO

    // Finds the target data by name
    vector<City> Database::find_by_string(const string& datatype, bool substring, const string& city_name) const;

    vector<City> Database::find_by_number
        (const string& datatype, bool range, const double& data1, const double& data2) const;

    // Add a new city to the database
    void add(const City& city);

    //Delete a city from database
    void delete_city(const City& city);

    //Sort cities alphabetically
    void sort_city();




private:
    std::string       _db_filename;
    std::vector<City> _cities;
}; // class Database


#endif // DATABASE_H
