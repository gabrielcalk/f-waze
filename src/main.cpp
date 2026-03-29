#include <iostream>
#include <string>
#include "DataFetcher.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "Display.h"
#include "StringUtils.h"

static int promptCity(const Graph& graph,
                      const std::string& prompt,
                      int excludeId = -1) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);

        if (toLower(input) == "quit") return -2;

        int id = graph.findCity(toLower(input));
        if (id == -1) {
            std::cout << "City not found. Try: 'City, ST' format.\n";
            continue;
        }
        if (id == excludeId) {
            std::cout << "Source and destination must be different.\n";
            continue;
        }
        return id;
    }
}

int main() {
    std::cout << "Fetching US cities from BRIDGES API...\n";
    std::vector<City> cities;
    try {
        cities = fetchCities();
    } catch (const std::exception& e) {
        std::cerr << "Error fetching data: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Building graph (" << cities.size() << " cities, 4 neighbors each)...\n";
    Graph graph;
    graph.build(cities);
    std::cout << "Ready. Type 'quit' to exit.\n\n";

    while (true) {
        int sourceId = promptCity(graph, "Enter source city (e.g. Miami, FL): ");
        if (sourceId == -2) break;

        int destId = promptCity(graph, "Enter destination city (e.g. Seattle, WA): ", sourceId);
        if (destId == -2) break;

        PathResult dijkstraResult = dijkstra(graph, sourceId, destId);
        PathResult aStarResult    = aStar(graph, sourceId, destId);

        printResults(graph, dijkstraResult, aStarResult);

        std::cout << "Search again? [y/n]: ";
        std::string answer;
        std::getline(std::cin, answer);
        if (trim(toLower(answer)) != "y") break;
        std::cout << "\n";
    }

    return 0;
}
