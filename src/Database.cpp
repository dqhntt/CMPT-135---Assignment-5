#include "Database.h"
#include "cmpt_error.h"
#include "util.file.h"
#include <algorithm>
#include <iostream>
using namespace std;

Database::Database(const string& db_filename)
    : _db_filename(db_filename)
    , _cities(util::file::read_data(db_filename))
{ }

Database::~Database() { // Destructor must never let exception escape.
    if (_db_filename.empty())
        return;
    try {
        util::file::write_data(_cities, _db_filename);
    } catch (const exception& e) { cerr << e.what() << "\n"; }
}

void Database::open(const string& target_filename) {
    // Unload data first if any.
    if (!_db_filename.empty()) {
        util::file::write_data(_cities, _db_filename);
    }
    _cities = util::file::read_data(target_filename);
    _db_filename = target_filename;
}

//////////////////////////////////////////////////////////////////////////////////////
// Finds the target data by the according data types and returns the index
// If it finds the city in database, append the city to the result
// If it does not find it, return an empty vector
vector<City> Database::cities_matching_string(
    const Field& field, bool substring_mode, const string& target_data) const {
    vector<City> result;
    for (const City& c : _cities) {
        string target;
        // Choose the target depending on data types
        if (field == Field::city_name) {
            target = c.name;
        } else if (field == Field::province_id) {
            target = c.province_id;
        } else if (field == Field::province) {
            target = c.province;
        } else {
            cmpt::error("cities_matching_string: Invalid datatype.\n");
        }

        // Compare the whole string or substring depending on the boolean "substring"
        if (substring_mode == true) {
            if (target.find(target_data) != string::npos)
                result.push_back(c);
        } else {
            if (target == target_data)
                result.push_back(c);
        }
    } // end of for loop
    return result;
}

// Find the city by number inputs. If we compare the exact number, only 1 number is used.
vector<City> Database::cities_in_number_range(
    const Field& field, double range_low, double range_high) const {
    vector<City> result;
    for (const City& c : _cities) {
        double target;
        // Choose the target depending on data type
        if (field == Field::latitude) {
            target = c.latitude;
        } else if (field == Field::longitude) {
            target = c.longitude;
        } else if (field == Field::population) {
            target = c.population;
        } else if (field == Field::population_density) {
            target = c.population_density;
        } else {
            cmpt::error("cities_in_number_range: Invalid datatype.\n");
        }
        // Compare the exact number or range of number
        if ((target >= range_low) && (target <= range_high))
            result.push_back(c);
    } // end of for loop
    return result;
}

vector<City> Database::cities_matching_exact_number(const Field& field, double target_num) const {
    return cities_in_number_range(field, target_num, target_num);
}

//////////////////////////////////////////////////////////////////////////////////////

// Helper function made for sorting the vector<City>.
// The comparison logic is depending on the field
bool less_than(const City& city1, const City& city2, const Field& field) {
    switch (field) {
    case Field::city_name:
        return (city1.name < city2.name);
    case Field::province_id:
        return (city1.province_id < city2.province_id);
    case Field::province:
        return (city1.province < city2.province);
    case Field::latitude:
        return (city1.latitude < city2.latitude);
    case Field::longitude:
        return (city1.longitude < city2.longitude);
    case Field::population:
        return (city1.population < city2.population);
    case Field::population_density:
        return (city1.population_density < city2.population_density);
    default:
        cmpt::error("bool less_than: Invalid field.\n");
    }
    return true; // Never going to reach this line
}

// Sorts the data:
// In ascending order when reversed_mode is false, and
// descending order when reversed_mode is true.
void Database::sort_cities(const Field& field, bool reversed_mode, bool stable_sort) {
    auto compare = [&](const City& c1, const City& c2) {
        return (reversed_mode ? !less_than(c1, c2, field) : less_than(c1, c2, field));
    };
    stable_sort ? std::stable_sort(_cities.begin(), _cities.end(), compare)
                : std::sort(_cities.begin(), _cities.end(), compare);
}

bool Database::exists_record(const City& city) const {
    return (find(_cities.begin(), _cities.end(), city) != _cities.end());
}

// Add a new city to the database
void Database::add_city(const City& city) { _cities.push_back(city); }

// Returns a read-only reference to the underlying _cities vector
const vector<City>& Database::get_cities() const { return _cities; }

// Delete a city from database
void Database::delete_city(const City& city) {
    // https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    _cities.erase(remove(_cities.begin(), _cities.end(), city), _cities.end());
}

// Deletes a list of cities
void Database::delete_cities(const vector<City>& cities) {
    for (const City& c : cities) {
        delete_city(c);
    }
}
