
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
	bool isRented = false; //Crucial for renting process
	bool rentendWithin1Day; //Crucial for renting process
public:
	//Default Constructor for the Vehicle Class
	Vehicle();
	/*
	* Parameterized Constructor for the Vehicle Class
	* @param company the car company's name of type string
	* @param cn the car's name of type string
	*/
	Vehicle(string company, string cn);

	/*
	* Initializes the vehicle's car company
	* @param cc the car company name of type string to be initialized
	* @return void
	*/
	void setCarCompany(string cc);

	/*
	* Initializes vehicle's car name
	* @param cn the car name of type string to be initialized
	* @return void
	*/
	void setCarName(string cn);

	/*
	* Initializes the vehicle's rental location to reside in
	* @param rentalLocation the object of type RentalLocation where the vehicle will reside
	* @return void
	*/
	void setRentalLocation(RentalLocation rentalLocation);

	/*
	* Initializes the vehicle's rental status as a method of indication
	* @param boolean the value of type bool that indicates the vehicle's rental status
	* @return void
	*/
	void setRentStatus(bool boolean);

	/*
	* Initializes vehicle's 1 day rental status as a method of indication
	* @param boolean the value of type bool that indicates the vehicle's 1 day rental status
	* @return void
	*/
	void set1DayRentStatus(bool boolean);

	/*
	* Returns the vehicle's car company
	* @return carCompany
	*/
	string getCarCompany();

	/*
	* Returns the vehicle's car name
	* @return carName 
	*/
	string getCarName();

	/*
	* Returns all the vehicle's attributes in type string
	* @return carCompany << carName 
	*/
	string toString();

	/*
	* Returns the 1 day rent status in type bool
	* @return rentedWithin1Day
	*/
	bool get1DayRentStatus();

	/*
	* Returns the vehicle's rent status
	* @return isRented
	*/
	bool getRentStatus();

};
#endif