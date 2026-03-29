cmake_minimum_required(VERSION 3.16)
project(fwaze CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

find_package(CURL REQUIRED)

add_executable(fwaze
    src/main.cpp
    src/DataFetcher.cpp
    src/Graph.cpp
    src/Dijkstra.cpp
    src/AStar.cpp
    src/Display.cpp
)

target_include_directories(fwaze PRIVATE include)
target_link_libraries(fwaze PRIVATE nlohmann_json::nlohmann_json CURL::libcurl)
