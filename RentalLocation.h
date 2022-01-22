#include <string>
#include <string.h>
#include <iostream>
//#include "Vehicle.h"
#include <vector>
#ifndef RENTAL_H
#define RENTAL_H

//class prototype:
class Vehicle;
//i'll provide more later

using namespace std;
class RentalLocation {
private:
	int streetNumber;
	string streetName;
	string postalCode;
	vector<Vehicle> vehiclesForRent;

public:
	RentalLocation();
	RentalLocation(int sNum, string sn, string pc);
	void setStreetNumber(int sNum);
	void setStreetName(string streetName);
	void setPostalCode(string pc);
	int getStreetNumber();
	string getStreetName();
	string getPostalCode();
	void addVehicle(Vehicle&);// is really a long
	vector<Vehicle>& getVehiclesList();

};

#endif