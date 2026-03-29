# F-Waze

CLI shortest-path visualizer comparing Dijkstra's and A* on a geographic graph of US cities.

## Dependencies

- CMake ≥ 3.16
- C++17 compiler (clang++ or g++)
- libcurl (system)
- nlohmann/json (auto-downloaded by CMake)

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/fwaze
```

Enter cities in `City, ST` format (e.g. `Miami, FL`). Type `quit` to exit.

## Algorithms

| Algorithm | Strategy |
|---|---|
| Dijkstra | Min-heap priority queue; explores all directions uniformly |
| A* | Dijkstra + Haversine heuristic; guides search toward destination |

Both always return the optimal shortest path. A* visits significantly fewer cities.

## Data

Cities fetched live from the [BRIDGES US Cities API](https://bridgesdata.herokuapp.com/api/us_cities). Graph connects each city to its 4 nearest neighbors by Haversine distance.
