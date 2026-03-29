#pragma once
#include <cmath>

// The Haversine formula calculates the great-circle distance (shortest path along Earth's curved surface) between two points given their latitude/longitude coordinates.
inline double haversine(double lat1, double lon1, double lat2, double lon2) {
    constexpr double R  = 6371.0;
    constexpr double PI = 3.14159265358979323846;
    auto toRad = [](double deg) { return deg * PI / 180.0; };
    double dLat = toRad(lat2 - lat1);
    double dLon = toRad(lon2 - lon1);
    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(toRad(lat1)) * std::cos(toRad(lat2)) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    return R * 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
}
