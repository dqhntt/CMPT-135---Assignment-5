#include "Database.h"
#include <cassert>
#include <iostream>
#include <cassert>
using namespace std;

void database_test(){
    cout << "Testing " << __func__ << "() ...\n";

    const string filename = "../data/test_database.txt";
    Database test(filename);

    test.sort_cities(Field::population, true);
    assert(test.get_cities().size() == 1738);

    vector<City> vancouver = test.cities_matching_string(Field::city_name, false, "Vancouver");
    assert(vancouver.size() == 1);
    assert(vancouver[0].province == "British Columbia");
    assert(vancouver[0].population == 2264823);

    vector<City> ont = test.cities_matching_string(Field::province, true, "rio");
    assert(ont.size() == 345);
    assert(ont[0].province_id == "ON");
    for (int i = 0; i < ont.size() - 1; i++) {
        assert(ont[i].population >= ont[i + 1].population);
    }

    vector<City> coquitlam = test.cities_matching_exact_number(Field::population, 58612);
    assert(coquitlam.size() == 1);

    City ont_city = ont[5];
    test.delete_cities(ont);
    assert(test.exists_record(ont_city) == false);

    test.add_city(ont_city);
    assert(test.exists_record(ont_city));

    cout << "... " << __func__ << "() passed.\n";
}

int main() {
    cout << "TEST SUITE:\n"
         << "  File: " << __FILE__ << "\n"
         << "  Date: " << __DATE__ << "\n"
         << "  Time: " << __TIME__ << "\n";

    database_test();
}
