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
vector<City> Database::find_by_string(const string& datatype, bool substring, const string& data) const{
    vector<City> result = {};
    for(City c : _cities){
        string target;
        //Choose the target depending on data type
        if(datatype == "name"){
            target = c.name;
        } else if (datatype == "province_id"){
            target = c.province_id;
        } else if (datatype == "province"){
            target = c.province;
        } else {
            cmpt::error("Invalid datatype.\n");
        }

        //Compare the whole string or substring depending on the boolean "substring"
        if(substring == true){ //if this is a substring input
            //Note the find() method below is from <string> class
            if(target.find(data) != string::npos) 
                result.push_back(c);
        } else{ //has to match the exact string
            if(target == data) 
                result.push_back(c);
        }        
    }// end of for loop
    return result;
}

//Find the city by number inputs. If we compare the exact number, only data1 is used.
//If we are given a range, both data1 and data2 are used. In this case, data1 is the 
//min limit and data2 is the max limit
vector<City> Database::find_by_number
    (const string& datatype, bool range, const double& data1, const double& data2) const{
    vector<City> result = {};
    for(City c : _cities){
        double target;
        //Choose the target depending on data type
        if(datatype == "latitude"){
            target = c.latitude;
        } else if (datatype == "longitude"){
            target = c.longitude;
        } else if (datatype == "population"){
            target = (double)c.population;
        } else if (datatype == "population_density"){
            target = c.population_density;
        } else {
            cmpt::error("Invalid datatype.\n");
        }

        //Compare the exact number or range of number depending on the boolean "range"
        if(range == true){ //if this is a range of numbers
            double min = data1;
            double max = data2;
            if((target >= min) && (target <= max)) 
                result.push_back(c);
        } else{ //has to match the exact number
            if(target == data1) 
                result.push_back(c);
        }       
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////

//Add a new city to the database
//If the city is already in the database, do nothing
void Database::add(const City& city){
    for(City c : _cities){
        //if the city is already in the list
        if(c == city){
            cout << "The city is already in the list.\n";
            return;
        }
    }
    //confirmed the city is not in the list
    _cities.push_back(city);
    cout << "The city is added to the list.\n";
}

//Delete a city from database
//NEED TO MODIFY THIS FUNCITON SO IT TAKE A VECTOR OF CITY
void Database::delete_city(const City& city){
    int target_index = 0;
    while(target_index < _cities.size()){
        if(_cities.at(target_index) == city){
            _cities.erase(_cities.begin() + target_index);
            return;
        }
        target_index++;
    }
    //if the loop is finished, that means we did not find the target 
    //print a message to show users theres an error
    cmpt::error("Unable to delete because the city is not in the list.\n");
}

//Sort cities alphabetically
void Database::sort_city(){
    
}
