#ifndef CITY_H
#define CITY_H

#include <string>

struct City {
    std::string name, province_id, province;
    int         population;
    double      population_density, latitude, longitude;

    City()
        : name(), province_id(), province()
        , population(0)
        , population_density(0.0), latitude(0.0), longitude(0.0)
    { }
}; // struct City

#endif // CITY_H