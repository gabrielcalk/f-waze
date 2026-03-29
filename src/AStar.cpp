#include "AStar.h"
#include "Haversine.h"
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

PathResult aStar(const Graph& graph, int sourceId, int destId) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = static_cast<int>(graph.size());
    std::vector<double> gCost(n, std::numeric_limits<double>::infinity());
    std::vector<bool> closed(n, false);
    std::vector<int> prev(n, -1);

    const City& dest = graph.getCity(destId);
    auto h = [&](int id) {
        const City& c = graph.getCity(id);
        return haversine(c.lat, c.lon, dest.lat, dest.lon);
    };

    using Entry = std::pair<double, int>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> pq;

    gCost[sourceId] = 0.0;
    pq.push({h(sourceId), sourceId});
    int citiesVisited = 0;

    while (!pq.empty()) {
        auto [f, u] = pq.top();
        pq.pop();

        if (closed[u]) continue;
        closed[u] = true;
        citiesVisited++;

        if (u == destId) break;

        for (const auto& [v, w] : graph.neighbors(u)) {
            if (closed[v]) continue;
            double newG = gCost[u] + w;
            if (newG < gCost[v]) {
                gCost[v] = newG;
                prev[v]  = u;
                pq.push({newG + h(v), v});
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::vector<int> path;
    if (gCost[destId] < std::numeric_limits<double>::infinity())
        path = reconstructPath(prev, destId);

    return PathResult{path, gCost[destId], citiesVisited, ms};
}
