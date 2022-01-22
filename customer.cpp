#ifndef CUSTOMER_C
#define CUSTOMER_C
#include "customer.h"
#include <string.h>
#include "RentalLocation.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


Customer::Customer() {
	cout << "Hello fellow customer" << endl;
}


Customer::Customer(string fn, string ln, int ageYears, string sa) {
	firstName = fn;
	lastName = ln;
	age = ageYears;
	streetAddress = sa;

	//cout << "First Name: " << firstName << " Last Name: " << lastName << " Age: " << age << " Street Address: " << streetAddress  << endl;
}


void Customer::setFirstName(string fn) {
	firstName = fn;
}



void Customer::setLastName(string ln) {
	lastName = ln;
}



void Customer::setAge(int ageInYears) {
	age = ageInYears;
}



void Customer::setStreetAddress(string sa) {
	streetAddress = sa;
}

void Customer::setRentalLocation(RentalLocation rl) { rentalLocation = rl; }



string Customer::getFirstName() {
	return firstName;
}


string Customer::getLastName() {
	return lastName;
}


int Customer::getAge() {
	return age;
}


string Customer::getStreetAddress() {
	return streetAddress;
}



void Customer::addRentalVehToList(Vehicle& veh) { vehicles.push_back(veh); }

void Customer::setPreferred(bool& boolean) { isPreferred = boolean; }

bool Customer::getPreferred() { return isPreferred; }

#endif