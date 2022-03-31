#ifndef MENU_H
#define MENU_H

// #include " only headers required for declarations "
#include "City.h"
#include <string>
#include <vector>

class Menu {

    // TODO
    //Default constructor
    Menu(){};

    //Destructor
    ~Menu(){};

    // Finds the target data by name
    int find_by_name(const std::string& city_name) const;

    // Finds the target data by a substring of names
    int find_by_name_sub(const std::string& city_name_sub) const;

    // Finds the target data by the exact latitude
    int find_by_lat(const double& lat) const;

    // Finds the target data by a range of latitude
    int find_by_lat_range(const double& min_lat, const double& max_lat) const;

    //Add a city
    void add();

    //List the cities
    void list_cities();

    //Delete a city
    void delete_city();

    //Quit the menu
    void quit();




}; // class Menu

#endif // MENU_H
