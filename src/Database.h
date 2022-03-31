#ifndef DATABASE_H
#define DATABASE_H

#include "City.h"
#include <string>
#include <vector>

// TODO: Implement this class.

enum class Field {
    city_name,
    province_id,
    province,
    latitude,
    longitude,
    population,
    population_density
};

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

    // Question: (1 mark) When searching for strings, one kind of search
    // should print all records where the typed-in string from the user
    // exactly matches the appropriate field of a record.

    // Finds the target data by name
    // The Boolean "substring" determines if we want to compare substring or not
    std::vector<City> cities_matching_string(const Field& field, 
                                             bool substr_mode, const string& target_str) const;

    std::vector<City> cities_in_number_range(const Field& field, 
                                             double range_low, double range_high) const;
    std::vector<City> cities_matching_exact_number(const Field& field, double target_num) const;

    bool exists_record(const City& city) const;

    // Add a new city to the database
    void add_city(const City& city); // push-back, sort

    // Delete a city from database
    void delete_cities(const vector<City>& cities);

    // (1 mark) For each string field in your record, allow the user
    // to list all records in alphabetical order.

    void sort(const Field& field, bool reversed_mode);

private:
    std::string       _db_filename;
    std::vector<City> _cities;

}; // class Database

#endif // DATABASE_H