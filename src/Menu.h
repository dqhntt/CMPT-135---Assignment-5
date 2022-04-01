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
