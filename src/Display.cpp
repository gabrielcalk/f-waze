#include "Display.h"
#include <iostream>
#include <iomanip>
#include <sstream>

static std::string formatInt(long long n) {
    std::string s = std::to_string(n);
    int pos = static_cast<int>(s.length()) - 3;
    while (pos > 0) {
        s.insert(pos, ",");
        pos -= 3;
    }
    return s;
}

static std::string formatDouble(double d, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << d;
    return oss.str();
}

static void printRow(const std::string& algo, int visited, double ms) {
    std::string v = formatInt(visited);
    std::string t = formatDouble(ms, 1);
    std::cout << "│ " << std::left << std::setw(13) << algo
              << "│ " << std::setw(17) << v
              << "│ " << std::setw(12) << t << "│\n";
}

void printResults(const Graph& graph,
                  const PathResult& dijkstraResult,
                  const PathResult& aStarResult) {
    std::cout << "\n";
    std::cout << "┌───────────────────────────────────────────────┐\n";
    std::cout << "│ F-WAZE ROUTE RESULTS                          │\n";
    std::cout << "├──────────────┬──────────────────┬─────────────┤\n";
    std::cout << "│ Algorithm    │ Cities Visited   │ Time (ms)   │\n";
    std::cout << "├──────────────┼──────────────────┼─────────────┤\n";
    printRow("Dijkstra", dijkstraResult.citiesVisited, dijkstraResult.timeMs);
    printRow("A*", aStarResult.citiesVisited, aStarResult.timeMs);
    std::cout << "└──────────────┴──────────────────┴─────────────┘\n";

    const auto& path = dijkstraResult.path;
    if (path.empty()) {
        std::cout << "\nNo path found between those cities.\n\n";
        return;
    }

    std::cout << "\nBest Path:\n";
    std::string line = graph.getCity(path[0]).name;
    for (size_t i = 1; i < path.size(); i++) {
        std::string seg = " → " + graph.getCity(path[i]).name;
        if (line.length() + seg.length() > 78) {
            std::cout << line << "\n";
            line = "         \u2192 " + graph.getCity(path[i]).name;
        } else {
            line += seg;
        }
    }
    std::cout << line << "\n";

    std::cout << "\nTotal Distance: "
              << formatInt(static_cast<long long>(dijkstraResult.totalDistance))
              << " km\n\n";
}
