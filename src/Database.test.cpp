#include "Database.h"
#include <cassert>
#include <iostream>
#include <cassert>
using namespace std;

void database_test(){
    cout << "Testing " << __func__ << "() ...\n";

    const string filename = "../data/test_database.txt";
    Database test_db(filename);

    test_db.sort_cities(Field::population, true);
    assert(test_db.get_cities().size() == 1738);

    const vector<City> vancouver = test_db.cities_matching_string(Field::city_name, false, "Vancouver");
    assert(vancouver.size() == 1);
    assert(vancouver[0].province == "British Columbia");
    assert(vancouver[0].population == 2264823);

    const vector<City> ont = test_db.cities_matching_string(Field::province, true, "rio");
    assert(ont.size() == 345);
    assert(ont[0].province_id == "ON");
    for (int i = 0; i < ont.size() - 1; i++) {
        assert(ont[i].population >= ont[i + 1].population);
    }

    const vector<City> coquitlam = test_db.cities_matching_exact_number(Field::population, 58612);
    assert(coquitlam.size() == 1);

    const City ont_city = ont[5];
    test_db.delete_cities(ont);
    assert(test_db.exists_record(ont_city) == false);

    test_db.add_city(ont_city);
    assert(test_db.exists_record(ont_city));

    cout << "... " << __func__ << "() passed.\n";
}

int main() {
    cout << "TEST SUITE:\n"
         << "  File: " << __FILE__ << "\n"
         << "  Date: " << __DATE__ << "\n"
         << "  Time: " << __TIME__ << "\n";

    database_test();
}
