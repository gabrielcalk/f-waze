#pragma once
#include <string>
#include <vector>

struct City {
    int id;
    std::string name;
    double lat, lon;
};

std::vector<City> fetchCities();
