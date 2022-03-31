#ifndef CITY_H
#define CITY_H

#include <string>

struct City {
    std::string name, province_id, province;
    int         population;
    double      population_density, latitude, longitude;

    City()
        : name("N/A"), province_id("N/A"), province("N/A")
        , population(0)
        , population_density(0.0), latitude(0.0), longitude(0.0)
    { }
}; // struct City

bool operator ==(const City& c1, const City& c2){
    return (c1.name == c2.name &&
            c1.province == c2.province &&
            c1.province_id == c2.province_id &&
            c1.latitude == c2.latitude &&
            c1.longitude == c2.longitude &&
            c1.population == c2.population &&
            c1.population_density == c2.population_density);
}

#endif // CITY_H
