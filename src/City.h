#ifndef CITY_H
#define CITY_H

#include <string>

struct City {
    std::string name, province_id, province;
    double      latitude, longitude;
    int         population, population_density;

    City()
        : name(), province_id(), province()
        , latitude(0.0), longitude(0.0)
        , population(0), population_density(0) 
    { }
}; // struct City

#endif // CITY_H