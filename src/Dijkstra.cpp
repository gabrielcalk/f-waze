#include "Dijkstra.h"
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

PathResult dijkstra(const Graph& graph, int sourceId, int destId) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = static_cast<int>(graph.size());
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> prev(n, -1);

    using Entry = std::pair<double, int>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> pq;

    dist[sourceId] = 0.0;
    pq.push({0.0, sourceId});
    int citiesVisited = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;
        citiesVisited++;

        if (u == destId) break;

        for (const auto& [v, w] : graph.neighbors(u)) {
            double newDist = dist[u] + w;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                prev[v] = u;
                pq.push({newDist, v});
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::vector<int> path;
    if (dist[destId] < std::numeric_limits<double>::infinity())
        path = reconstructPath(prev, destId);

    return PathResult{path, dist[destId], citiesVisited, ms};
}
