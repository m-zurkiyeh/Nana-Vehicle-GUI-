#include <string>
#include "Vehicle.h"
#include <iostream>
#include <format>
#ifndef VEHICLE_C
#define VEHICLE_C
using namespace std;

Vehicle::Vehicle() {}

Vehicle::Vehicle(string company, string cn) {
	carCompany = company;
	carName = cn;
}

void Vehicle::setCarCompany(string cc) { carCompany = cc; }

void Vehicle::setCarName(string cn) { carName = cn; }

void Vehicle::setRentalLocation(RentalLocation rentalLocation) { rl = rentalLocation; }

void Vehicle::setRentStatus(bool boolean) { isRented = boolean;}

bool Vehicle::getRentStatus() { return isRented; }

string Vehicle::getCarCompany() { return carCompany; }

string Vehicle::getCarName() { return carName; }

string Vehicle::toString() {return "Car Company: " + carCompany + " Car Name: " + carName; }
#endif