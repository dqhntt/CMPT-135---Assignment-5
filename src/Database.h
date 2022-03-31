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
    vector<City> Database::find_by_string(const string& datatype, bool substring, const string& city_name);

    vector<City> find_by_name(const std::string& city_name) const;

    // Finds the target data by a substring of names
    vector<City> find_by_name_sub(const std::string& city_name_sub) const;

    // Finds the target data by the exact latitude
    vector<City> find_by_lat(const double& lat) const;

    // Finds the target data by a range of latitude
    vector<City> find_by_lat_range(const double& min_lat, const double& max_lat) const;

    // Add a new city to the database
    void add(City city);

    //Delete a city from database
    void delete_city(City city);

    //Sort cities alphabetically
    void sort_city();




private:
    std::string       _db_filename;
    std::vector<City> _cities;
}; // class Database

#endif // DATABASE_H
