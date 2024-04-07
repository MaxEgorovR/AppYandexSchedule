#pragma once
#include <iostream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include < memory >

class Flight {
	std::string day;
	std::string month;
	std::string year;
	std::string cityFrom;
	std::string cityTo;
	httplib::Client* geoCli;
	httplib::Client* codeCli;
	std::string requestGeoFrom;
	std::string requestGeoTo;
	std::string requestCodeFrom;
	std::string requestCodeTo;
	nlohmann::json resultGeoFrom;
	nlohmann::json resultGeoTo;
	nlohmann::json resultCodeFrom;
	nlohmann::json resultCodeTo;
	std::string lonFrom;
	std::string latFrom;
	std::string lonTo;
	std::string latTo;
	std::string codeFrom;
	std::string codeTo;
	std::string requestSchedule;
	nlohmann::json resultSchedule;
	std::string requestNearestStation;
	nlohmann::json resultNearestStation;
	std::string requestInfoOfCarrier;
	nlohmann::json resultInfoOfCarrier;
	std::string distance;
	std::string requestNearestStationForType;
	std::string resultNearestStationForType;
	std::string typeOfStation;
	std::string codeOfCarrier;
public:
	Flight();

	Flight(std::string geoClient, std::string codeClient);

	void setCityFrom(std::string city);

	void setCityTo(std::string city);

	void setCodeOfCarrier(std::string codeOfCarrier);

	void setDistance(std::string distance);

	void setTypeOfStation(std::string typeOfStation);

	void setResultGeoFrom();

	void setResultGeoTo();

	void setLatLonFrom();

	void setResultCodeFrom();

	void setResultCodeTo();

	void setLatLonTo();

	void setRequestGeoFrom();

	void setRequestGeoTo();

	void setRequestCodeFrom();

	void setRequestCodeTo();

	void setCodeFrom();

	void setCodeTo();

	void setRequestSchedule();

	void setResultSchedule();

	void setData(std::string day, std::string month, std::string year);

	nlohmann::json getResultSchedule();

	void setRequestNearestStation();

	void setResultNearestStation();

	nlohmann::json getResultNearestStation();

	void setRequestInfoOfCarrier();

	void setResultInfoOfCarrier();

	nlohmann::json getResultInfoOfCarrier();

	void setRequestNearestStationForType();

	void setResultNearestStationForType();

	nlohmann::json getResultNearestStationForType();
};