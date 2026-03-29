#pragma once
#include "DataFetcher.h"
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

struct PathResult {
    std::vector<int> path;
    double totalDistance;
    int citiesVisited;
    double timeMs;
};

std::vector<int> reconstructPath(const std::vector<int>& prev, int destId);

class Graph {
public:
    void build(const std::vector<City>& cities);
    int findCity(const std::string& normalizedName) const;
    const City& getCity(int id) const;
    const std::vector<std::pair<int, double>>& neighbors(int id) const;
    size_t size() const;

private:
    std::vector<City> cities_;
    std::unordered_map<int, std::vector<std::pair<int, double>>> edges_;
    std::unordered_map<std::string, int> nameIndex_;
};
