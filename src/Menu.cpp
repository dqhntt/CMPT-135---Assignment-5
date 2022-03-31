#include "Menu.h"
#include <algorithm>
#include <iostream>
// #include " any required header files "
// #include < any required library >

using namespace std;

// void Menu::foo() const {
//    
//     // This is just a sample function.
//     // TODO
// }

//Default constructor
Menu::Menu(){};

//Destructor
Menu::~Menu(){};

//////////////////////////////////////////////////////////////////////////////////////
//Finds the target data by the according data type and returns the index
//If it finds the city in database, return that city's index
//If it does not find it, return the last index + 1 (ie. size of the vector)
int Menu::find_by_name(const std::string& city_name) const{
    int index = 0;
    while(index < _cities.size()){
        if(_cities.at(index).name == city_name) return index;
        index++;
    }
    //If the city is not found in the list
    return index;
}

// Finds the target data by a substring of names
int Menu::find_by_name_sub(const std::string& city_name_sub) const{
    int index = 0;
    while(index < _cities.size()){
        //If the substring matches a string
        //Note the find() method below is from <string> class
        if(_cities.at(index).name.find(city_name_sub) != string::npos) return index;
        index++;
    }
    //If the city is not found in the list
    return index;
}

// Finds the target data by the exact latitude
int Menu::find_by_lat(const double& lat) const{
    int index = 0;
    while(index < _cities.size()){
        if(_cities.at(index).latitude == lat) return index;
        index++;
    }
    //If the city is not found in the list
    return index;
}

// Finds the target data by a range of latitude
int Menu::find_by_lat_range(const double& min_lat, const double& max_lat) const{
    int index = 0;
    while(index < _cities.size()){
        if((_cities.at(index).latitude >= min_lat) && (_cities.at(index).latitude <= max_lat)) 
            return index;
        index++;
    }
    //If the city is not found in the list
    return index;
}

//////////////////////////////////////////////////////////////////////////////////////

//Add a city
void Menu::add(){

}

//List the cities
void Menu::list_cities(){

}

//Delete a city
void delete_city(){

}

//Quit the menu
void quit(){

}

