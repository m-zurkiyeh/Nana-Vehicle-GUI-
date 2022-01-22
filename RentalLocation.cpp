#include "RentalLocation.h"
#include <iostream>
#ifndef RENTAL_C
#define RENTAL_C
using namespace std;

#include "Vehicle.h"

RentalLocation::RentalLocation() {}

RentalLocation::RentalLocation(int sNum, string sn, string pc) {
	streetNumber = sNum;
	streetName = sn;
	postalCode = pc;
}

void RentalLocation::setStreetNumber(int sNum) {streetNumber = sNum;}

void RentalLocation::setStreetName(string sn) {streetName = sn;}

void RentalLocation::setPostalCode(string pc) {postalCode = pc;}

void RentalLocation::addVehicle(Vehicle& veh) { vehiclesForRent.push_back(veh); }

int RentalLocation::getStreetNumber() { return streetNumber; }

string RentalLocation::getStreetName() { return streetName; }

string RentalLocation::getPostalCode() { return postalCode; }

vector<Vehicle>& RentalLocation::getVehiclesList() { return vehiclesForRent; }
#endif