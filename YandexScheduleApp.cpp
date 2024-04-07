// YandexScheduleApp.cpp: определяет точку входа для приложения.


#include "YandexScheduleApp.h"
using namespace std;


int main()
{
	using json = nlohmann::json;
	setlocale(LC_ALL, "RUS");
	Flight Cli("http://api.openweathermap.org", "http://api.rasp.yandex.net");
	std::string cityFrom, cityTo, day, month, year,distance, typeOfStations, codeOfCarrier;
	bool flag = true;
	int choise;
	nlohmann::json resultInfo;
	nlohmann::json resultNearestStation;
	nlohmann::json resultInfoOfCarrier;
	nlohmann::json resultTypeOfStations;

	while (flag) {
		cout << "1 - Просмотр рейсовпо заданной дате из одного пункта в другой\n2 - Просмотр десяти ближайших станций\n3 - Просмотр информации о перевозчике\n4 - Просмотр информации по определённому типу станций в заданном диапазоне\n5 - Выход\n";
		cin >> choise;
		if (choise == 1) {
			cout << "Введите город отправления:\n";
			cin >> cityFrom;
			cout << "Введите город назначения:\n";
			cin >> cityTo;
			cout << "Введите день рейса(DD):\n";
			cin >> day;
			cout << "Введите месяц рейса(MM):\n";
			cin >> month;
			cout << "Введите год рейса(YYYY):\n";
			cin >> year;
			Cli.setCityFrom(cityFrom);
			Cli.setCityTo(cityTo);
			Cli.setData(day,month,year);
			Cli.setRequestGeoFrom();
			Cli.setRequestGeoTo();
			Cli.setResultGeoFrom();
			Cli.setResultGeoTo();
			Cli.setLatLonFrom();
			Cli.setLatLonTo();
			Cli.setRequestCodeFrom();
			Cli.setRequestCodeTo();
			Cli.setResultCodeFrom();
			Cli.setResultCodeTo();
			Cli.setCodeFrom();
			Cli.setCodeTo();
			Cli.setRequestSchedule();
			Cli.setResultSchedule();
			resultInfo = Cli.getResultSchedule();
			for (int i = 0; i < 10; i++) {
				cout << " " << resultInfo["interval_segments"][i]["thread"]["title"] << " " << resultInfo["interval_segments"][i]["from"]["transport_type"] << " " << resultInfo["interval_segments"][i]["thread"]["interval"]["begin_time"] << " " << resultInfo["interval_segments"][i]["thread"]["interval"]["end_time"] << endl;
			}
		}
		else if (choise == 2) {
			cout << "Введите город :\n";
			cin >> cityFrom;
			cout << "Введите радиус в километрах:\n";
			cin >> distance;
			Cli.setCityFrom(cityFrom);
			Cli.setDistance(distance);
			Cli.setRequestGeoFrom();
			Cli.setResultGeoFrom();
			Cli.setLatLonFrom();
			Cli.setRequestNearestStation();
			Cli.setResultNearestStation();
			resultNearestStation = Cli.getResultNearestStation();
			for (int i = 0; i < 10; i++) {
				cout <<"Дистанция до станции: " << resultNearestStation["stations"][i]["distance"] << " Тип станции: " << resultNearestStation["stations"][i]["station_type"] << " Транспорт: " << resultNearestStation["stations"][i]["transport_type"] << endl;
			}
		}
		else if (choise == 3) {
			cout << "Введите код :\n";
			cin >> codeOfCarrier;
			Cli.setCodeOfCarrier(codeOfCarrier);
			Cli.setRequestInfoOfCarrier();
			Cli.setResultInfoOfCarrier();
			resultInfoOfCarrier = Cli.getResultInfoOfCarrier();
			for (int i = 0; i < 10; i++) {
				cout << "Контакты: " << resultInfoOfCarrier["carriers"][i]["contacts"] << " Адрес: " << resultInfoOfCarrier["carriers"][i]["address"] << " Почта: " << resultInfoOfCarrier["carriers"][i]["email"]<<endl;
			}
		}
		else if (choise == 4) {
			cout << "Введите город :\n";
			cin >> cityFrom;
			cout << "Введите радиус в километрах:\n";
			cin >> distance;
			cout << "Введите тип станций:\nstation — станция;\nplatform — платформа;\nstop — остановочный пункт;\ncheckpoint — блок - пост;\npost — пост;\ncrossing — разъезд;\novertaking_point — обгонный пункт;\ntrain_station — вокзал;\nairport — аэропорт;\nbus_station — автовокзал;\nbus_stop — автобусная остановка;\nunknown — станция без типа;\nport — порт;\nport_point — портпункт;\nwharf — пристань;\nriver_port — речной вокзал;\nmarine_station — морской вокзал.\n";
			cin >> typeOfStations;
			Cli.setCityFrom(cityFrom);
			Cli.setDistance(distance);
			Cli.setTypeOfStation(typeOfStations);
			Cli.setRequestGeoFrom();
			Cli.setResultGeoFrom();
			Cli.setLatLonFrom();
			Cli.setRequestNearestStationForType();
			Cli.setResultNearestStationForType();
			resultTypeOfStations = Cli.getResultNearestStationForType();
			for (int i = 0; i < 10; i++) {
				cout << "Дистанция до станции: " << resultTypeOfStations["stations"][i]["distance"] << " Тип станции: " << resultTypeOfStations["stations"][i]["station_type"] << " Транспорт: " << resultTypeOfStations["stations"][i]["transport_type"] << endl;
			}
		}
		else {
			flag = false;
		}
	}
}
