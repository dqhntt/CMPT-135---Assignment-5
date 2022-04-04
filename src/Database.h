#ifndef DATABASE_H
#define DATABASE_H

#include "City.h"
#include <string>
#include <vector>
using namespace std;

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


    // Question: (1 mark) When searching for strings, one kind of search 
    // should print all records where the typed-in string from the user
    // exactly matches the appropriate field of a record.


    // Finds the target data by name.
    //The allowed fields here are "name", "province_id", "province".
    //The Boolean "substring" determines if we want to compare substring or not.
    vector<City> cities_matching_string(const Field& field, bool substring, const string& target_data) const;

    //The below 2 functions find target cities by number.
    //The allowed fields here are "latitude", "longitude", "population" and "population_density"
    vector<City> cities_in_number_range(const Field& field, double range_low, double range_high) const;
    vector<City> cities_matching_exact_number(const Field& field, double target_num) const;

    //Checks if a city exists in the database
    bool exists_record(const City& city) const;

    // Add a new city to the database
    void add_city(const City& city); 

    //Delete a city from database
    void delete_city(const City& city);

    //Delete a list of cities from database
    void delete_cities(const vector<City>& cities);

    // (1 mark) For each string field in your record, allow the user 
    // to list all records in alphabetical order.

    //Sorts the city depending on the field. In here, all 7 fields are allowed. 
    //The boolean reversed_mode changes the order from ascending to descending
    void sort_cities(const Field& field, bool reversed_mode);

    //Gets the underlying city in the class. 
    const vector<City>& get_cities() const;

private:
    std::string       _db_filename;
    std::vector<City> _cities;
}; // class Database


#endif // DATABASE_H