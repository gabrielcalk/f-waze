#include "Graph.h"
#include "Haversine.h"
#include "StringUtils.h"
#include <algorithm>

void Graph::build(const std::vector<City>& cities) {
    cities_ = cities;
    for (const auto& city : cities_)
        nameIndex_[toLower(city.name)] = city.id;

    constexpr int K = 4;
    int n = static_cast<int>(cities_.size());

    for (int i = 0; i < n; i++) {
        std::vector<std::pair<double, int>> dists;
        dists.reserve(n - 1);
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            double d = haversine(cities_[i].lat, cities_[i].lon,
                                 cities_[j].lat, cities_[j].lon);
            dists.push_back({d, j});
        }
        std::partial_sort(dists.begin(), dists.begin() + K, dists.end());
        for (int k = 0; k < K; k++) {
            edges_[i].push_back({dists[k].second, dists[k].first});
            edges_[dists[k].second].push_back({i, dists[k].first});
        }
    }

    for (auto& [id, nbrs] : edges_) {
        std::sort(nbrs.begin(), nbrs.end());
        nbrs.erase(std::unique(nbrs.begin(), nbrs.end()), nbrs.end());
    }
}

int Graph::findCity(const std::string& normalizedName) const {
    auto it = nameIndex_.find(normalizedName);
    return it != nameIndex_.end() ? it->second : -1;
}

const City& Graph::getCity(int id) const {
    return cities_[id];
}

const std::vector<std::pair<int, double>>& Graph::neighbors(int id) const {
    static const std::vector<std::pair<int, double>> empty;
    auto it = edges_.find(id);
    return it != edges_.end() ? it->second : empty;
}

size_t Graph::size() const {
    return cities_.size();
}

std::vector<int> reconstructPath(const std::vector<int>& prev, int destId) {
    std::vector<int> path;
    for (int at = destId; at != -1; at = prev[at])
        path.push_back(at);
    std::reverse(path.begin(), path.end());
    return path;
}
