#ifndef DATABASE_H
#define DATABASE_H

#include "City.h"
#include <string>
#include <vector>

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

    // Gets the underlying city in the class.
    const std::vector<City>& get_cities() const;

    // Finds the target data by name.
    // The allowed fields here are "name", "province_id", "province".
    // The Boolean "substr_mode" determines if we want to compare substring or not.
    std::vector<City> cities_matching_string(
        const Field& field, bool substr_mode, const std::string& target_data) const;

    // The below 2 functions find target cities by number.
    // The allowed fields here are "latitude", "longitude", "population" and "population_density"
    std::vector<City> cities_in_number_range(
        const Field& field, double range_low, double range_high) const;
    std::vector<City> cities_matching_exact_number(const Field& field, double target_num) const;

    // Checks if a city exists in the database
    bool exists_record(const City& city) const;

    // Add a new city to the database
    void add_city(const City& city);

    // Delete a city from database
    void delete_city(const City& city);

    // Delete a list of cities from database
    void delete_cities(const std::vector<City>& cities);

    // Sorts the city depending on the field. In here, all 7 fields are allowed.
    // The boolean reversed_mode changes the order from ascending to descending.
    // stable_sort when true ensures relative order of equal elements remain the same.
    void sort_cities(const Field& field, bool reversed_mode = false, bool stable_sort = false);

private:
    std::string _db_filename;
    std::vector<City> _cities;
}; // class Database

#endif // DATABASE_H