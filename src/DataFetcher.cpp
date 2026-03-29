#include "DataFetcher.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>

static size_t writeCallback(char* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

static std::string httpGet(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) throw std::runtime_error("curl_easy_init failed");
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "f-waze/1.0");
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) throw std::runtime_error(curl_easy_strerror(res));
    return response;
}

std::vector<City> fetchCities() {
    auto raw = httpGet("https://bridgesdata.herokuapp.com/api/us_cities");
    auto json = nlohmann::json::parse(raw);
    auto& arr = json.is_array() ? json : json.at("data");

    std::vector<City> cities;
    cities.reserve(arr.size());
    int id = 0;
    for (auto& entry : arr) {
        City city;
        city.id   = id++;
        city.name = entry.at("city").get<std::string>() + ", " +
                    entry.at("state").get<std::string>();
        city.lat  = entry.at("lat").get<double>();
        city.lon  = entry.at("lon").get<double>();
        cities.push_back(city);
    }
    return cities;
}
