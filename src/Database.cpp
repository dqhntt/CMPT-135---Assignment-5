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

//////////////////////////////////////////////////////////////////////////////////////
//Finds the target data by the according data types and returns the index
//If it finds the city in database, append the city to the result
//If it does not find it, return an empty vector
vector<City> Database::cities_matching_string(const Field& field, bool substring, const string& target_data) const{
    vector<City> result;
    for(City c : _cities){
        string target;
        //Choose the target depending on data typeSS
        if(field == Field::city_name){
            target = c.name;
        } else if (field == Field::province_id){
            target = c.province_id;
        } else if (field == Field::province){
            target = c.province;
        } else {
            cmpt::error("cities_matching_string: Invalid datatype.\n");
        }

        //Compare the whole string or substring depending on the boolean "substring"
        if(substring == true){ //if this is a substring input
            //Note the find() method below is from <string> class
            if(target.find(target_data) != string::npos) 
                result.push_back(c);
        } else{ //has to match the exact string
            if(target == target_data) 
                result.push_back(c);
        }        
    }// end of for loop
    return result;
}

//Find the city by number inputs. If we compare the exact number, only data1 is used.
//
vector<City> Database::cities_in_number_range(const Field& field, double range_low, double range_high) const{
    vector<City> result;
    for(City c : _cities){
        double target;
        //Choose the target depending on data type
        if(field == Field::latitude){
            target = c.latitude;
        } else if (field == Field::longitude){
            target = c.longitude;
        } else if (field == Field::population){
            target = (double)c.population;
        } else if (field == Field::population_density){
            target = c.population_density;
        } else {
            cmpt::error("cities_in_number_range: Invalid datatype.\n");
        }
        //Compare the exact number or range of number
        if((target >= range_low) && (target <= range_high)) 
            result.push_back(c);
    }// end of for loop
    return result;
}

vector<City> Database::cities_matching_exact_number(const Field& field, double target_num) const{
    return cities_in_number_range(field, target_num, target_num);
}

//////////////////////////////////////////////////////////////////////////////////////

//Helper function made for sorting the vector<City>. 
//The comparison logic is depending on the field
bool less_than(const City& city1 , const City& city2, const Field& field){
    switch(field){
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
    return true; //Never going to reach this line
}

//Sorts the data:
//In ascending order when reversed_mode is false, and
//descending order when reversed_mode is true.
void Database::sort_cities(const Field& field, bool reversed_mode){
    if(reversed_mode){ //the order is reversed, we are sorting in descending order
        std::sort(_cities.begin(), _cities.end(),
            [field](const City& c1 , const City& c2) -> bool{return !less_than(c1,c2,field);});
    } else{// sorting in ascending order
        std::sort(_cities.begin(), _cities.end(),
            [field](const City& c1 , const City& c2) -> bool{return less_than(c1,c2,field);});
    }
}

bool Database::exists_record(const City& city) const{
    for(City c : _cities){
        //if the city is already in the list
        if(c == city){
            return true;
        }
    }
    return false;
}

//Add a new city to the database
//If the city is already in the database, do nothing
void Database::add_city(const City& city){
    if(!exists_record(city))
        _cities.push_back(city);
}

//Delete a city from database
void Database::delete_city(const City& city){
    int target_index = 0;
    while(target_index < _cities.size()){
        if(_cities[target_index] == city){
            _cities.erase(_cities.begin() + target_index);
            return;
        }
        target_index++;
    }
    //if the loop is finished, that means we did not find the target 
    //print a message to show users theres an error
    cmpt::error("Unable to delete because the city is not in the list.\n");
}

//Deletes a list of cities
void Database::delete_cities(const vector<City>& cities){
    for(City c : cities){
        delete_city(c);
    }
}

//Returns the underlying _cities vector
vector<City> Database::get_cities() const{
    return _cities;
}