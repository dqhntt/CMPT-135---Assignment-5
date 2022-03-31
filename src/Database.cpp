#include "Database.h"
#include "util.file.h"
#include "cmpt_error.h"
#include <algorithm>
#include <iostream>
using namespace std;

Database::Database(const string& db_filename)
    : _db_filename(db_filename)
    , _cities(util::file::read_data(db_filename))
{ }

Database::~Database() // Destructor must never let exception escape.
{
    if (_db_filename.empty())
        return;

    try {
        util::file::write_data(_cities, _db_filename);
    } catch (const exception& e) {
        cerr << e.what() << "\n";
    }
}

void Database::open(const string& target_filename)
{
    if (!_db_filename.empty()) {
        util::file::write_data(_cities, _db_filename);
    } else {
        _cities = util::file::read_data(target_filename);
        _db_filename = target_filename;
    }
}

// TODO

//Finds the target data by name and returns the index
//If it finds the city in database, return that city's index
//If it does not find it, return the last index + 1 (ie. size of the vector)
int Database::find(const std::string& city_name) const{
    int index = 0;
    while(index < _cities.size()){
        if(_cities.at(index).name == city_name) return index;
        index++;
    }
    //If the city is not found in the list
    return index;
}

//Add a new city to the database
//If the city is already in the database, do nothing
void Database::add(City city){
    if(Database::find(city.name) == _cities.size()){
        _cities.push_back(city);
        cout << "The city is added to the list.\n";
    }
    else{
        cout << "The city is already in the list.\n";
    }
}

//Delete a city from database
void Database::delete_city(City city){
    int target_index = Database::find(city.name);
    if(target_index == _cities.size())
        cmpt::error("Unable to delete because the city is not in the list.\n");
    _cities.erase(_cities.begin() + target_index);
}

//Sort cities alphabetically
void Database::sort_city(){
    sort(_cities.begin(), _cities.end());
}
