
#include <string>
#include "RentalLocation.h"


#ifndef VEHICLE_H
#define VEHICLE_H
using namespace std;
class Vehicle {
private:
	string carCompany;
	string carName;
	RentalLocation rl;
	bool isRented = false;
public:
	Vehicle();
	Vehicle(string company, string cn);
	void setCarCompany(string cc);
	void setCarName(string cn);
	void setRentalLocation(RentalLocation rentalLocation);
	void setRentStatus(bool boolean);
	string getCarCompany();
	string getCarName();
	string toString();
	bool getRentStatus();

};
#endif