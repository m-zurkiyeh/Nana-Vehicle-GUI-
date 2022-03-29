#include <string.h>
#include <string>
#include "RentalLocation.h"
#include "Vehicle.h"
#ifndef CUSTOMER_H
#define CUSTOMER_H
#define MAX_CUSTOMERS 5

using namespace std;
class Customer {
private:
	string firstName, lastName, streetAddress, beginRentDate,beginEndDate;
	bool isPreferred;
	int age = 0, counter = 0;
	RentalLocation rentalLocation;
	vector<Vehicle> vehicles;
	

public:
	
	Customer();
	Customer(string fn, string ln, int ageYears, string sa);
	void addCustomer(Customer cust);
	void setFirstName(string fn);
	void setLastName(string ln);
	void setStreetAddress(string sa);
	void setAge(int ageInYears);
	void setPreferred(bool& preferedStatus);
	void setRentalLocation(RentalLocation rl);
	void addRentalVehToList(Vehicle& veh);
	void setBeginDate(string& brd);
	void setEndDate(string& erd);
	string getFirstName();
	string getLastName();
	string getStreetAddress();
	string getBeginDate();
	string getEndDate();
	int getAge();
	bool getPreferred();
	RentalLocation getRentalLocation();
	vector<Vehicle> getVehicleList();


};

#endif