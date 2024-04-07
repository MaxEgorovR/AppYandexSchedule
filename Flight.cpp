#include "Flight.h"

std::string OW_API_KEY = "e7c0bce5516c376f0d980ddc956bb225";
std::string YA_API_KEY = "ec846f28-142d-4543-aba7-ec9a3195a6ff";


Flight::Flight(std::string geoClient, std::string codeClient) {
    this->geoCli = new httplib::Client(geoClient);
    this->codeCli = new httplib::Client(codeClient);
}

void Flight::setCityFrom(std::string city) {
    this->cityFrom = city;
}

void Flight::setCityTo(std::string city) {
    this->cityTo = city;
}

void Flight::setCodeOfCarrier(std::string codeOfCarrier) {
    this->codeOfCarrier = codeOfCarrier;
}

void Flight::setDistance(std::string distance) {
    this->distance = distance;
}

void Flight::setTypeOfStation(std::string typeOfStation) {
    this->typeOfStation=typeOfStation;
}

void Flight::setResultGeoFrom() {
    if (auto response = this->geoCli->Get(this->requestGeoFrom)) {
        if (response->status == 200) {
            this->resultGeoFrom = nlohmann::json::parse(response->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

void Flight::setResultGeoTo() {
    if (auto response = this->geoCli->Get(this->requestGeoTo)) {
        if (response->status == 200) {
            this->resultGeoTo = nlohmann::json::parse(response->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

void Flight::setResultCodeFrom() {
    if (auto response = this->codeCli->Get(this->requestCodeFrom)) {
        if (response->status == 200) {
            this->resultCodeFrom = nlohmann::json::parse(response->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

void Flight::setResultCodeTo() {
    if (auto response = this->codeCli->Get(this->requestCodeTo)) {
        if (response->status == 200) {
            this->resultCodeTo = nlohmann::json::parse(response->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

void Flight::setLatLonFrom() {
    this->lonFrom = to_string(this->resultGeoFrom[0]["lon"]);
    this->latFrom = to_string(this->resultGeoFrom[0]["lat"]);
}

void Flight::setLatLonTo() {
    this->lonTo = to_string(this->resultGeoTo[0]["lon"]);
    this->latTo = to_string(this->resultGeoTo[0]["lat"]);
}

void Flight::setRequestGeoFrom() {
    this->requestGeoFrom = "/geo/1.0/direct?";
    this->requestGeoFrom += "q=" + this->cityFrom;
    this->requestGeoFrom += "&limit=" + '10';
    this->requestGeoFrom += "&appid=" + OW_API_KEY;
}

void Flight::setRequestGeoTo() {
    this->requestGeoTo = "/geo/1.0/direct?";
    this->requestGeoTo += "q=" + this->cityTo;
    this->requestGeoTo += "&limit=" + '10';
    this->requestGeoTo += "&appid=" + OW_API_KEY;
}

void Flight::setRequestCodeFrom() {
    this->requestCodeFrom = "/v3.0/nearest_settlement/?";
    this->requestCodeFrom += "apikey=" + YA_API_KEY;
    this->requestCodeFrom += "&format=json";
    this->requestCodeFrom += "&lat=" + this->latFrom;
    this->requestCodeFrom += "&lng=" + this->lonFrom;
}

void Flight::setRequestCodeTo() {
    this->requestCodeTo = "/v3.0/nearest_settlement/?";
    this->requestCodeTo += "apikey=" + YA_API_KEY;
    this->requestCodeFrom += "&format=json";
    this->requestCodeTo += "&lat=" + this->latFrom;
    this->requestCodeTo += "&lng=" + this->lonFrom;
}

void Flight::setCodeFrom() {
    this->codeFrom = resultCodeFrom["code"].get<std::string>();
}

void Flight::setCodeTo() {
    this->codeTo = resultCodeTo["code"].get<std::string>();
}

void Flight::setRequestSchedule() {
    this->requestSchedule = "/v3.0/search/?";
    this->requestSchedule += "&format=json";
    this->requestSchedule += "apikey=" + YA_API_KEY;
    this->requestSchedule += "&from=" + this->codeFrom;
    this->requestSchedule += "&to=" + this->codeTo;
    this->requestSchedule += "&date=" + this->year + "-" + this->month + "-" + this->day;
}

void Flight::setResultSchedule() {
    if (auto responseSchedule = this->codeCli->Get(this->requestSchedule)) {
        if (responseSchedule->status == 200) {
            this->resultSchedule = nlohmann::json::parse(responseSchedule->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

void Flight::setData(std::string day, std::string month, std::string year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

nlohmann::json Flight::getResultSchedule() {
    return this->resultSchedule;
}

void Flight::setRequestNearestStation() {
    this->requestNearestStation = "/v3.0/nearest_stations/?";
    this->requestNearestStation += "apikey=" + YA_API_KEY;
    this->requestNearestStation += "&format=json";
    this->requestNearestStation += "&lat=" + this->latFrom;
    this->requestNearestStation += "&lng=" + this->lonFrom;
    this->requestNearestStation += "&distance=" + this->distance;
}

void Flight::setResultNearestStation() {
    if (auto response = this->codeCli->Get(this->requestNearestStation)) {
        if (response->status == 200) {
            this->resultNearestStation = nlohmann::json::parse(response->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

nlohmann::json Flight::getResultNearestStation() {
    return resultNearestStation;
}

void Flight::setRequestInfoOfCarrier() {
    this->requestInfoOfCarrier = "/v3.0/carrier/?";
    this->requestInfoOfCarrier += "apikey=" + YA_API_KEY;
    this->requestInfoOfCarrier += "&format=json";
    this->requestInfoOfCarrier += "&code=" + this->codeOfCarrier;
}

void Flight::setResultInfoOfCarrier() {
    if (auto response = this->codeCli->Get(this->requestInfoOfCarrier)) {
        if (response->status == 200) {
            this->resultInfoOfCarrier = nlohmann::json::parse(response->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

nlohmann::json Flight::getResultInfoOfCarrier() {
    return resultInfoOfCarrier;
}

void Flight::setRequestNearestStationForType() {
    this->requestNearestStationForType = "/v3.0/nearest_stations/?";
    this->requestNearestStationForType += "apikey=" + YA_API_KEY;
    this->requestNearestStationForType += "&format=json";
    this->requestNearestStationForType += "&lat=" + this->latFrom;
    this->requestNearestStationForType += "&lng=" + this->lonFrom;
    this->requestNearestStationForType += "&distance=" + this->distance;
    this->requestNearestStationForType += "&station_types=" + this->typeOfStation;
}

void Flight::setResultNearestStationForType() {
    if (auto response = this->codeCli->Get(this->requestNearestStationForType)) {
        if (response->status == 200) {
            this->resultNearestStationForType = nlohmann::json::parse(response->body);
        }
        else {
            std::cout << "Bad request" << std::endl;
        }
    }
}

nlohmann::json Flight::getResultNearestStationForType() {
    return resultNearestStationForType;
}