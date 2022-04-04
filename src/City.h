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

    bool operator ==(const City& c) const{
    return (name == c.name &&
            province == c.province &&
            province_id == c.province_id &&
            latitude == c.latitude &&
            longitude == c.longitude &&
            population == c.population &&
            population_density == c.population_density);
    }
}; // struct City



#endif // CITY_H