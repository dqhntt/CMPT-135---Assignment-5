#include "util.file.h"
#include "cmpt_error.h"

#include <fstream>
#include <string>
using namespace std;

// = INT_MAX and < streamsize
const int BIG_NUMBER = 2147483647;
const int ESTIMATED_DB_SIZE = 1750;
const char SEPARATOR = ';';

vector<City> util::file::read_data(const string& filename, int skip_lines) {
    ifstream file(filename);
    if (!file) {
        cmpt::error("Error loading data from file: " + filename);
    }
    for (int i = 0; i < skip_lines; i++) {
        file.ignore(BIG_NUMBER, '\n');
    }
    vector<City> data;
    data.reserve(ESTIMATED_DB_SIZE);
    City city;
    string field;
    char next = file.peek();
    // Parse each line in file.
    while (file.good() && // Not end of file.
           next != EOF && next != '\r' && next != '\n') {
        getline(file, city.name, SEPARATOR);
        getline(file, city.province_id, SEPARATOR);
        getline(file, city.province, SEPARATOR);
        try {
            getline(file, field, SEPARATOR);
            city.latitude = stod(field);
            getline(file, field, SEPARATOR);
            city.longitude = stod(field);
            getline(file, field, SEPARATOR);
            city.population = stoi(field);
            getline(file, field, '\n');
            city.population_density = stod(field);
        } catch (const invalid_argument& e) {
            cmpt::error("Error converting \"" + field + "\" to a number: " + e.what());
        }
        data.push_back(city);
        next = file.peek();
    } // while
    return data;
}

void util::file::write_data(const vector<City>& data, const string& filename, int precision) {
    ofstream file(filename);
    if (!file) {
        cmpt::error("Error writing data to file: " + filename);
    }
    file << "city_name" << SEPARATOR << "province_id" << SEPARATOR << "province"   << SEPARATOR
         << "latitude"  << SEPARATOR << "longitude"   << SEPARATOR << "population" << SEPARATOR
         << "population_density" << endl;
    file << fixed;
    file.precision(precision);
    for (const City& city : data) {
        file << city.name      << SEPARATOR << city.province_id << SEPARATOR 
             << city.province  << SEPARATOR << city.latitude    << SEPARATOR
             << city.longitude << SEPARATOR << city.population  << SEPARATOR 
             << city.population_density << "\n";
    } // for
    file.flush(); // Write buffer to file.
}
