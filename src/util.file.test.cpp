#include "util.file.h"

#include "util.h"

#include <cassert>
#include <iostream>
using namespace std;

void print(const City& city)
{
    cout << city.name << ";"
         << city.province_id << ";"
         << city.province << ";"
         << city.latitude << ";"
         << city.longitude << ";"
         << city.population << ";"
         << city.population_density << endl;
}

void database_format_test()
{
    cout << "Testing " << __func__ << "() ...\n";

    const string filename = "../data/test_database.txt";
    vector<City> data     = util::file::read_data(filename);

    // Assert properties of each record in the database.
    // Assuming no empty strings.
    for (const City& city : data) {
        assert(city.population >= 0);
        assert(city.population_density >= 0);
        assert(!util::is_number(city.name));
        assert(!util::is_number(city.province));
        assert(!util::is_number(city.province_id));
    }
    util::file::write_data(data, filename);

    cout << "... " << __func__ << "() passed.\n";
}

int main()
{
    cout << "TEST SUITE:\n"
         << "  File: " << __FILE__ << "\n"
         << "  Date: " << __DATE__ << "\n"
         << "  Time: " << __TIME__ << "\n";

    const int trials_num = 2;
    for (int i = 0; i < trials_num; i++) {
        database_format_test();
    }
}
