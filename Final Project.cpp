// Final Project.cpp : Defines the entry point for the application.
//

#ifndef FINAL_PROJECT
#define FINAL_PROJECT
#include "Final Project.h"
#include <stdlib.h>
#include <string>
#include "customer.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/widgets/toolbar.hpp>
#include <nana/audio/player.hpp>
#include <nana/threads/pool.hpp>
#include <windows.h>
#include <iostream>
#include <mmsystem.h>
#include <stdlib.h>
#include <ctime>
#include <tchar.h>
#define NANA_ENABLE_AUDIO
#pragma comment(lib, "winmm.lib")
#define EMPTY_COMBO_VALUE 18446744073709551615



using namespace std;
using namespace nana;
//using namespace nana::audio::player;


int main()
{
	// GUI attributes such as buttons, forms and other necessary variables
	//*************************************************************************
	form fm{ rectangle{520,160,500,500} };
	label timeDisplay{ fm };
	timer clock{ std::chrono::seconds{0} };
	vector<Customer> customers;
	vector<Vehicle> vehicles;
	vector<RentalLocation> rentalLocations;
	timeDisplay.format(true);
	label lab{ fm, "<bold blue size=12 center>\t\t\t\t\t\t\t\tWelcome to the Car Rental System</>" };
	lab.format(true);
	button addCustButton{ fm,"Add Customer" };
	button removeCustButton{ fm,"Remove Customer" };
	button aboutButton{ fm, "About" };
	button quitBtn{ fm, "Quit" };
	button assignLocationtoVehicle{ fm,"Assign rental location to vehicle" };
	button addCar{ fm,"Add Vehicle" };
	button removeCar{ fm,"Remove Vehicle" };
	button addRentalLocation{ fm,"Add Rental Location" };
	button removeRentalLocation{ fm,"Remove Rental Location" };
	button displayAll{ fm,"Display Database" };
	button timerButton{ fm, "Display time" };
	button assignVehtoCust{ fm,"Assign vehicle to customer" };
	button preferred{ fm,"Set customer to preferred status" };
	button dateDisplay{ fm, "Display Current Date" };
	button returnRentedVeh{ fm, "Return rented car" };
	button editCustomer{ fm,"Edit Customer Info" };
	button editVehicle{fm,"Edit Vehicle Info"};
	button editRentalLocation{ fm, "Edit Rental Location Info" };
	time_t currentTime = time(0);
	char* dateInString = ctime(&currentTime);
	label dateDisplayLabel{fm};
	static int i = 0;
	//nana::audio::player pingring("sonicring.wav");
	//************************************************************************

	//Dummy objects to test the program's other features
	//*****************************

	Customer test1("Mike", "Wazowski", 55, "1234 Arsene Lupin ave");
	Customer test2("Sulley", "Goliath", 65, "6789 Snowman blvd");

	Vehicle testVeh1("Honda", "Yoda");
	Vehicle testVeh2("Mazda", "Dazda");

	RentalLocation* testRl1 = new RentalLocation(888, "Street Blvd", "BNG4TG");
	RentalLocation* testRl2 = new RentalLocation(555, "Address Street", "V9HQ3E");

	customers.push_back(test1);
	customers.push_back(test2);

	vehicles.push_back(testVeh1);		
	vehicles.push_back(testVeh2);

	testRl1->addVehicle(testVeh1);
	testRl2->addVehicle(testVeh2);

	rentalLocations.push_back(*testRl1);
	rentalLocations.push_back(*testRl2);
	//*******************************



	addCustButton.events().click([&] {
		form newForm(fm);
		label fnLab(newForm);
		label lnLab(newForm);
		label aLab(newForm);
		label saLab(newForm);

		fnLab.format(true);
		fnLab.caption("First Name: ");
		lnLab.format(true);
		lnLab.caption("Last Name: ");
		aLab.format(true);
		aLab.caption("Age: ");
		saLab.format(true);
		saLab.caption("Street Address: ");

		textbox fnText{ newForm };
		textbox lnText{ newForm };
		textbox ageText{ newForm };
		textbox saText{ newForm };


		button registerButton{ newForm, "Register Customer" };
		newForm.div("vert <<FNL><FN>> <<LNL><LN>> <<AL><A>> <<SAL><SA>> <RB>");
		newForm["FNL"] << fnLab;
		newForm["FN"] << fnText;
		newForm["LNL"] << lnLab;
		newForm["LN"] << lnText;
		newForm["AL"] << aLab;
		newForm["A"] << ageText;
		newForm["SAL"] << saLab;
		newForm["SA"] << saText;
		newForm["RB"] << registerButton;


		registerButton.events().click([&] {
			string fName;
			string lName;
			string age;
			string sa;
			fnText.getline(0, fName);
			lnText.getline(0, lName);
			ageText.getline(0, age);
			saText.getline(0, sa);
			Customer cust(fName, lName, 0, sa);
			try {
				cust.setAge(stoi(age));
			}
			catch (...) {
				msgbox ageInputError("Age Input Error");
				ageInputError << "Age Input Error";
				ageInputError.show();
				return;
			}
			cout << "Name is:" << fName;
			for (Customer c : customers) {
				if (c.getFirstName() == cust.getFirstName() && c.getLastName() == cust.getLastName() && c.getAge() == cust.getAge() && c.getStreetAddress() == cust.getStreetAddress()) {
					msgbox alreadyExistsMessageCustomer("Warning!!");
					alreadyExistsMessageCustomer << "Warning!! The customer with the first name " + c.getFirstName() + ", last name: " + c.getLastName() + ", age: " + std::to_string(c.getAge()) + " and with the street address: " + c.getStreetAddress() + " already exists!!";
					alreadyExistsMessageCustomer.show();
					return;
				}
			}
			if ((fName.empty() && lName.empty() && sa.empty()) || fName.empty() || lName.empty() || sa.empty()) {
				msgbox oneOrMoreEmpty("Empty Values Detected");
				oneOrMoreEmpty << "One or more attributes have been detected!\n Please make sure that all of the attributes have been filled";
				oneOrMoreEmpty.show();
				return;
			} else customers.push_back(cust);

			cout << "Customers in the database:" << endl;
			for (Customer c : customers) cout << "First Name: " << c.getFirstName() + ", last name: " + c.getLastName() + ", age: " + std::to_string(c.getAge()) + " and street address: " + c.getStreetAddress() << endl;
			});

		newForm.collocate();
		API::modal_window(newForm);
		});



	editCustomer.events().click([&] {
		form custList{fm};
		combox custBox{custList};
		string custName;
		button selectCustomer{ custList,"Select Customer" };
		custList.div("<cb> vert<<scb>>");
		custList["cb"] << custBox;
		custList["scb"] << selectCustomer;
		for (Customer c : customers) {
			custName = c.getFirstName() + " " + c.getLastName();
			custBox.push_back(custName);
		}

		selectCustomer.events().click([&] {
			string editNotice = "";
			string customerFirstName, customerLastName, customerAge, customerStreetAddress;
			for (Customer& c : customers) {
				custName = c.getFirstName() + " " + c.getLastName();
				if (custName == custBox.text(custBox.option())) {
					msgbox custFoundMsg("Customer Search Result!");
					custFoundMsg << "Customer " << custName << " has been successfully found!";
					custFoundMsg.show();

					form custEditor{custList};
					label fnLabel{custEditor,"First Name:"}, lnLabel{custEditor,"Last Name:"}, ageLabel{custEditor,"Age:"}, saLabel{custEditor,"Street Address:"};
					textbox fnTxt{custEditor}, lnTxt{custEditor}, ageTxt{custEditor}, saTxt{custEditor};
					button finishEditButton{ custEditor, "Edit occupied attributes"};

					custEditor.div("vert<<fnl><fntxt>> vert<<lnl><lntxt>> vert<<al><atxt>> vert<<sal><satxt>> <editButton>");

					custEditor["fnl"] << fnLabel;
					custEditor["fntxt"] << fnTxt;
					custEditor["lnl"] << lnLabel;
					custEditor["lntxt"] << lnTxt;
					custEditor["al"] << ageLabel;
					custEditor["atxt"] << ageTxt;
					custEditor["sal"] << saLabel;
					custEditor["satxt"] << saTxt;
					custEditor["editButton"] << finishEditButton;
					
					finishEditButton.events().click([&] {
						
						fnTxt.getline(0, customerFirstName);
						lnTxt.getline(0, customerLastName);
						ageTxt.getline(0, customerAge);
						saTxt.getline(0, customerStreetAddress);

						if (!customerFirstName.empty()) {
							c.setFirstName(customerFirstName);
							editNotice += "First Name: " + customerFirstName + "\n";
						}

						if (!customerLastName.empty()) {
							c.setLastName(customerLastName);
							editNotice += "Last Name : " + customerLastName + "\n";
						}
							
						if (!customerAge.empty()) {
							try {
								c.setAge(stoi(customerAge));
								if(isdigit(stoi(customerAge)))
								editNotice += "Age: " + std::to_string(c.getAge()) + "\n";
							}
							catch (...) {
								msgbox stoiError("Parsing Error");
								stoiError << "Value entered for age is invalid, Please enter an appropriate value for age or leave it empty ";
								stoiError.show();
								return;
							}
						}

						if (!customerStreetAddress.empty()) {
							c.setStreetAddress(customerStreetAddress);
							editNotice += "Street Address: " + c.getStreetAddress() + "\n";
						}

						msgbox customerEditResult("Customer Edit Result");
						customerEditResult << editNotice;
						customerEditResult.show();
						return;
						

					});

					custEditor.collocate();
					API::modal_window(custEditor);
				}
			}
			});
		custList.collocate();
		API::modal_window(custList);
		});




	removeCustButton.events().click([&] {
		form deleteForm(fm);
		button deleteButton{ deleteForm, "Remove Customer" };
		combox combo(deleteForm);
		deleteForm.div("vert <cbx> <b>");
		deleteForm["cbx"] << combo;
		deleteForm["b"] << deleteButton;
		if (customers.empty()) {
			msgbox emptList("Error!");
			emptList << "List of customers is empty!! Please add one or more customer before proceeding to deletion of customer";
			emptList.show();
			return;
		}
		for (Customer cust : customers) {
			
			combo.push_back(cust.getFirstName() + " " + cust.getLastName());
		}

		deleteButton.events().click([&] {
			int i = 0;
			cout << combo.text(0) << endl;
			if (combo.option() == EMPTY_COMBO_VALUE) {
				msgbox emptVal("Error!");
				emptVal << "Invalid Option Selected!";
				emptVal.show();
				return;
			}
			for (Customer cust : customers) {
				string firstLastName = cust.getFirstName() + " " + cust.getLastName();
				if (firstLastName == combo.text(combo.option())) {
					combo.erase(i);
					customers.erase(customers.begin() + i);
					msgbox deletedCust("Customer deletion status");
					deletedCust << "Customer " << firstLastName << ", Age " << cust.getAge() << " and living at " << cust.getStreetAddress() << " Has been successfully deleted";
					deletedCust.show();
					break;
				}
				i++;
			}
			});
		deleteForm.collocate();
		API::modal_window(deleteForm);
		});




	addCar.events().click([&] {
		form addCarForm(fm);

		label ccLab(addCarForm);
		label cnLab(addCarForm);
		textbox ccBox{ addCarForm };
		textbox cnBox{ addCarForm };
		button registerVehicle{ addCarForm, "Add Vehicle" };

		ccLab.format(true);
		ccLab.caption("Car Company: ");
		cnLab.format(true);
		cnLab.caption("Car Name: ");

		addCarForm.div("vert <<CCL><CCB>> <<CNL><CNB>> <RVB>");
		addCarForm["CCL"] << ccLab;
		addCarForm["CCB"] << ccBox;
		addCarForm["CNL"] << cnLab;
		addCarForm["CNB"] << cnBox;
		addCarForm["RVB"] << registerVehicle;

		registerVehicle.events().click([&] {
			string companyName;
			string vehicleName;
			ccBox.getline(0, companyName);
			cnBox.getline(0, vehicleName);
			Vehicle veh(companyName, vehicleName);
			for (Vehicle v : vehicles) {
				if (v.getCarName() == veh.getCarName() && v.getCarCompany() == veh.getCarCompany()) {
					msgbox alreadyExistsMessageVehicle("Warning!!");
					alreadyExistsMessageVehicle << "Warning!! The Vehicle with the Company : " + veh.getCarCompany() + " and with the Name : " + veh.getCarName() + " already exists!";
					alreadyExistsMessageVehicle.show();
					return;
				}
			}
			vehicles.push_back(veh);
			msgbox vehicleAddResult("Vehicle Creation Result!");
			vehicleAddResult << "The Vehicle " << veh.getCarCompany() << " " << veh.getCarName() << " has been successfully created";
			vehicleAddResult.show();
			using namespace nana;

			for (Vehicle v : vehicles) {
				if (vehicles.empty()) break;
				else cout << v.toString() << "\n";
			}
			});

		addCarForm.collocate();
		API::modal_window(addCarForm);
		});


	/*
	* Vehicle Attribute Alteration
	* Includes error detection for when the vehicles vector list is empty as well as leaving all values empty
	*/
	editVehicle.events().click([&] {
		if (vehicles.empty()) {
			msgbox emptVehList("Vehicle List Error");
			emptVehList << "Vehicle List is empty! Please add one or more vehicles before proceeding to editing vehicle attributes";
			emptVehList.show();
			return;
		}
		string* origCarCompany, *origCarName;
		string editNotice, newCarCompany, newCarName;
		form vehicleSelectForm{ fm };
		combox vehicleList{ vehicleSelectForm };
		button selectVehicle{vehicleSelectForm,"Search Vehicle"};

		vehicleSelectForm.div("vert<<vl>><sv>");
		vehicleSelectForm["vl"] << vehicleList;
		vehicleSelectForm["sv"] << selectVehicle;

		for (Vehicle v : vehicles)
			vehicleList.push_back(v.getCarCompany() + " " + v.getCarName());

		selectVehicle.events().click([&] {
			for (Vehicle v : vehicles) {
				if (vehicleList.option() == EMPTY_COMBO_VALUE) {
					msgbox emptOption("Empty Option Selected");
					emptOption << "Invalid Option detected!\nPlease select a valid choice";
					emptOption.show();
					return;
				}
				if ((v.getCarCompany() + " " + v.getCarName()) == vehicleList.text(vehicleList.option())) {
					msgbox vehFound("Vehicle Search Result");
					vehFound << "Vehicle Search Successful";
					vehFound.show();
					origCarCompany = &v.getCarCompany();
					origCarName = &v.getCarName();

					form vehicleEditor{ fm };
					label ccLabel{ vehicleEditor, "Car Company" }, cnLabel{ vehicleEditor, "Car Name" };
					textbox ccTxt{ vehicleEditor }, cnTxt{ vehicleEditor };
					button finalizeEdit{ vehicleEditor, "Edit Car Attributes" };

					vehicleEditor.div("vert<<ccl><cctxt>> vert<<cnl><cntxt>> <editButton>");
					vehicleEditor["ccl"] << ccLabel;
					vehicleEditor["cctxt"] << ccTxt;
					vehicleEditor["cnl"] << cnLabel;
					vehicleEditor["cntxt"] << cnTxt;
					vehicleEditor["editButton"] << finalizeEdit;

					finalizeEdit.events().click([&] {
						for (Vehicle& v : vehicles) {
							if ((v.getCarCompany() + " " + v.getCarName()) == vehicleList.text(vehicleList.option())) {
								if (ccTxt.empty() && cnTxt.empty()) {
									msgbox allEmptVals("No Values Entered!");
									allEmptVals << "All attributes have been left blank!\nPlease Fill at least one of the boxes before editing";
									allEmptVals.show();
									return;
								}
								if(!ccTxt.empty()) {
									ccTxt.getline(0, newCarCompany);
									v.setCarCompany(newCarCompany);
									editNotice += "Car Company: " + *origCarCompany + "  -> " + newCarCompany + "\n";
								}
								if (!cnTxt.empty()) {
									cnTxt.getline(0, newCarName);
									v.setCarName(newCarName);
									editNotice += "Car Name: " + *origCarName + "  -> " + v.getCarName() + "\n";
								}
								msgbox vehEditResult("Vehicle Edit Result");
								vehEditResult << "Vehicle has been successfully changed!\n" + editNotice;
								delete origCarCompany;
								delete origCarName;
								vehEditResult.show();
								break;
							}
						}
					});

					vehicleEditor.collocate();
					API::modal_window(vehicleEditor);
				}
			}
			});
		vehicleSelectForm.collocate();
		API::modal_window(vehicleSelectForm);
		});


	/*
	* Car Removal
	*/
	removeCar.events().click([&] {

		form removeCarForm(fm);
		combox removeCarCombo(removeCarForm);
		button finalizeCarRemoval{ removeCarForm,"Remove Vehicle" };

		removeCarForm.div("vert <CCMB><CCB>");
		removeCarForm["CCMB"] << removeCarCombo;
		removeCarForm["CCB"] << finalizeCarRemoval;

			if (vehicles.empty()) {
				msgbox emptVehListErr("Error!");
				emptVehListErr << "Error! Vehicle list is empty!! Please add one or more vehicles before attempting to delete a vehicle";
				emptVehListErr.show();
				return;
			}


		for (Vehicle v : vehicles)
			if (vehicles.empty())
				break;
			else removeCarCombo.push_back(v.getCarCompany() + " " + v.getCarName());

		finalizeCarRemoval.events().click([&] {
			int i = 0;
			string fullCarInfo;
			if (removeCarCombo.option() == EMPTY_COMBO_VALUE) {
				msgbox emptyVal("Error!");
				emptyVal << "Error! Invalid Option Selected";
				emptyVal.show();
				return;
			}
			for (Vehicle v : vehicles) {
				fullCarInfo = v.getCarCompany() + " " + v.getCarName();
				if (fullCarInfo == removeCarCombo.text(removeCarCombo.option())) {
					removeCarCombo.erase(i);
					vehicles.erase(vehicles.begin() + i);
					break;
				}
				i++;
			}
			});
		removeCarForm.collocate();
		API::modal_window(removeCarForm);
		});



	addRentalLocation.events().click([&] {
		form addRentalLocationForm(fm);
		label sNumLab(addRentalLocationForm);
		label sNameLab(addRentalLocationForm);
		label pcLab(addRentalLocationForm);

		textbox sNumBox{ addRentalLocationForm };
		textbox sNameBox{ addRentalLocationForm };
		textbox pcBox{ addRentalLocationForm };

		button createRL{ addRentalLocationForm,"Register Rental Location" };

		sNumLab.format(true);
		sNumLab.caption("Street Number: ");
		sNameLab.format(true);
		sNameLab.caption("Street Name: ");
		pcLab.format(true);
		pcLab.caption("Postal Code: ");

		addRentalLocationForm.div("vert <<SNUL><SNUB>> <<SNAL><SNAB>> <<PCL><PCB>> <REG>");
		addRentalLocationForm["SNUL"] << sNumLab;
		addRentalLocationForm["SNUB"] << sNumBox;
		addRentalLocationForm["SNAL"] << sNameLab;
		addRentalLocationForm["SNAB"] << sNameBox;
		addRentalLocationForm["PCL"] << pcLab;
		addRentalLocationForm["PCB"] << pcBox;
		addRentalLocationForm["REG"] << createRL;

		createRL.events().click([&] {
			string sNumber, sName, pCode;
			sNumBox.getline(0, sNumber);
			sNameBox.getline(0, sName);
			pcBox.getline(0, pCode);
			RentalLocation* rl{};
			
			try { 
				rl = new RentalLocation(stoi(sNumber), sName, pCode);
			}
			catch (...) {
				msgbox intErr("Input Error!");
				intErr << "Invalid input entered for street number! Please enter an integer";
				intErr.show();
				delete rl;
				return;
			}

			for (RentalLocation rLoc : rentalLocations) {
				if (rLoc.getStreetNumber() == rl->getStreetNumber() && rLoc.getStreetName() == rl->getStreetName() && rLoc.getPostalCode() == rl->getPostalCode()) {
					msgbox alreadyExistsMessageRL("Warning!!");
					alreadyExistsMessageRL << std::string() + "Warning!! The rental location with the Street Number : " + std::to_string(rl->getStreetNumber()) + " , with the Street Name : " + rl->getStreetName() + " and with the Postal Code: " + rl->getPostalCode() + " already exists!!";
					alreadyExistsMessageRL.show();
					delete rl;
					return;
				}
			}

			//Empty Value detection during Rental Location creation
			if ((sNumber.empty() && sName.empty() && pCode.empty()) || sNumber.empty() || sName.empty() || pCode.empty()) {
				msgbox emptyVal("Empty Input(s) detected!");
				emptyVal << "One or more empty values have been detected! Please enter values on the respective box";
				emptyVal.show();
				delete rl;
			}
			else {
				rentalLocations.push_back(*rl); 
				msgbox rlAddResult("Rental Location Addition Result"); //Message notifying user of a succesful addition of a new Rental Location
				rlAddResult << "The Rental Location " << rl->getStreetNumber() << " " << rl->getStreetName() << " with the postal code " << rl->getPostalCode() << " has been successfully created!";
				rlAddResult.show();
			}
			});


		addRentalLocationForm.collocate();
		API::modal_window(addRentalLocationForm);
		});



	editRentalLocation.events().click([&] {
		form rlSelectionMenu{ fm };
		combox rlList{ rlSelectionMenu };
		button selectRL{ rlSelectionMenu, "Select Rental Location"};
		int* origRLSnum;
		string*	origRLStrtName, origRLStrtPstlCode;
		string editNotice;
		
		rlSelectionMenu.div("vert<<rll>> <srl>");
		rlSelectionMenu["rll"] << rlList;
		rlSelectionMenu["srl"] << selectRL;

		for (RentalLocation rl : rentalLocations) {
			rlList.push_back(std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName() + " " + rl.getPostalCode());
		}

		selectRL.events().click([&] {
			for (RentalLocation& rl : rentalLocations) {
				if ((std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName() + " " + rl.getPostalCode()) == rlList.text(rlList.option())) {
					msgbox rlSearchSuccess("Rental Location Search Result");
					rlSearchSuccess << "Rental Location has been successfully found!";
					rlSearchSuccess.show();
					
					form rlEditMenu{ fm };
					label sNumLbl{rlEditMenu,"Street Number: "}, sNameLbl{rlEditMenu,"Street Name: "}, pcLbl{rlEditMenu,"Postal Code: "};
					textbox sNumTxt{ rlEditMenu }, sNameTxt{ rlEditMenu };
				}
			}
		});
		
		rlSelectionMenu.collocate();
		API::modal_window(rlSelectionMenu);
		
	});






	removeRentalLocation.events().click([&] {
		int i = 0;
		form removeRentalLocationForm(fm);
		button finalizeRLRemoval{ removeRentalLocationForm, "Remove Rental Location" };
		combox removeRLCombo(removeRentalLocationForm);
		removeRentalLocationForm.div("vert <DRLC><DRLB>");
		removeRentalLocationForm["DRLC"] << removeRLCombo;
		removeRentalLocationForm["DRLB"] << finalizeRLRemoval;
		if (rentalLocations.empty()) {
			msgbox emptyRlListMess("Error");
			emptyRlListMess << "Rental Location list is empty!";
			emptyRlListMess.show();
			return;
		}

		for (RentalLocation& rl : rentalLocations) {
			removeRLCombo.push_back(std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName() + " " + rl.getPostalCode());
			cout << std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName() + " " + rl.getPostalCode() << endl;
		}
		finalizeRLRemoval.events().click([&] {
			string fullRLInfo;

			if (removeRLCombo.option() == EMPTY_COMBO_VALUE) {
				msgbox emptyVal("Invalid Selection Error");
				emptyVal << "Invalid Option Selected! Please choose from one of the options listed in the combo box";
				emptyVal.show();
				return;
			}
			for (RentalLocation rl : rentalLocations) {
				fullRLInfo = std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName() + " " + rl.getPostalCode();
				if (fullRLInfo == removeRLCombo.text(removeRLCombo.option())) {
					cout << removeRLCombo.text(removeRLCombo.option()) << " " << removeRLCombo.option() << endl;
					removeRLCombo.erase(removeRLCombo.option());
					rentalLocations.erase(rentalLocations.begin() + i);
					break;
				}
				i++;
			}
			});
		removeRentalLocationForm.collocate();
		API::modal_window(removeRentalLocationForm);
		});



	assignLocationtoVehicle.events().click([&] {
		int snum = 0;
		string cc, cn, sn, pc;
		form assignVehicletoRL(fm);
		combox rlList(assignVehicletoRL);
		combox vehicleList(assignVehicletoRL);
		button setRL{ assignVehicletoRL, "Assign Rental Location to Vehicle" };
		assignVehicletoRL.div("vert <vl><rll><srl>");
		assignVehicletoRL["vl"] << vehicleList;
		assignVehicletoRL["rll"] << rlList;
		assignVehicletoRL["srl"] << setRL;

		for (RentalLocation rl : rentalLocations) rlList.push_back(std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName());
		for (Vehicle v : vehicles) vehicleList.push_back(v.getCarCompany() + " " + v.getCarName());

		setRL.events().click([&] {
			string baseRlInfo;
			string carInfo;
			cout << vehicleList.option() << endl;
			if (vehicleList.option() == EMPTY_COMBO_VALUE) {
				msgbox emptVal("Choice selection error"); //If empty value selected, display error message then stop process 
				emptVal << "Invalid choice selected! Please choose a valid option";
				emptVal.show();
				return;
			}
			for (Vehicle& v : vehicles) {
				carInfo = v.getCarCompany() + " " + v.getCarName();
				if (carInfo == vehicleList.text(vehicleList.option())) {
					cout << carInfo << endl;
					for (RentalLocation& rl : rentalLocations) {
						baseRlInfo = std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName();
						if (baseRlInfo == rlList.text(rlList.option())) {
							cout << baseRlInfo << endl;
							rl.addVehicle(v);
						}
					}
				}
			}
			});

		assignVehicletoRL.collocate();
		API::modal_window(assignVehicletoRL);
		});


	assignVehtoCust.events().click([&] {
		form registration(fm);
		label vehLab{ registration }, rentalLab{ registration }, custLab{ registration }, beginDateLab{ registration }, endDateLab{ registration };
		combox vehiclesList{ registration }, rentalLocationsList{ registration }, customerList{ registration };
		textbox beginDateInput{ registration }, endDateInput{ registration };
		button registrationButton{ registration,"Rent Vehicle" };

		custLab.format(true);
		custLab.caption("Customer: ");
		rentalLab.format(true);
		rentalLab.caption("Rental Location: ");
		vehLab.format(true);
		vehLab.caption("Vehicles: ");
		beginDateLab.format(true);
		beginDateLab.caption("Start Date: ");
		endDateLab.format(true);
		endDateLab.caption("End Date: ");

		registration.div("vert<<cl><cbx>> <<rll><rlbx>> <<vl><vbx>> <<bdl> <bdb>> <<edl><edb>> <reg>");
		registration["cl"] << custLab;
		registration["cbx"] << customerList;
		registration["rll"] << rentalLab;
		registration["rlbx"] << rentalLocationsList;
		registration["vl"] << vehLab;
		registration["vbx"] << vehiclesList;
		registration["bdl"] << beginDateLab;
		registration["bdb"] << beginDateInput;
		registration["edl"] << endDateLab;
		registration["edb"] << endDateInput;
		registration["reg"] << registrationButton;



		for (Customer c : customers) customerList.push_back(c.getFirstName() + " " + c.getLastName());
		for (RentalLocation rl : rentalLocations) rentalLocationsList.push_back(std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName());

		rentalLocationsList.events().selected([&] {
			string fullRLInfo;
			vehiclesList.clear();
			for (RentalLocation& rl : rentalLocations) {
				fullRLInfo = std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName();
				if (fullRLInfo == rentalLocationsList.text(rentalLocationsList.option())) {
					cout << "found" << endl;
					vector<Vehicle>& rlVehicles = rl.getVehiclesList();
					for (Vehicle v : rl.getVehiclesList()) {
						vehiclesList.push_back(v.getCarCompany() + " " + v.getCarName());
						cout << v.getCarCompany() << endl;
					}
				}
			}

			registrationButton.events().click([&] {
				string bd, ed, carInfo, custInfo,rLInfo;
				beginDateInput.getline(0, bd);
				endDateInput.getline(0, ed);
				for (Customer& c : customers) {
					custInfo = c.getFirstName() + " " + c.getLastName();
					if (custInfo == customerList.text(customerList.option())) {
						for (RentalLocation& rl : rentalLocations) {
							rLInfo = std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName();
							if (rLInfo == rentalLocationsList.text(rentalLocationsList.option())) {
								for (Vehicle& v : vehicles)	{
									carInfo = v.getCarCompany() + " " + v.getCarName();
									if (carInfo == vehiclesList.text(vehiclesList.option())) {
										int option = vehiclesList.option();
										c.addRentalVehToList(v);
										cout << "completed " << vehiclesList.option();
										vehicles.erase(vehicles.begin() + option);
										vehiclesList.erase(option);
										break;
									}
								}
							}
						}
					}
				}
				});

			});

		registration.collocate();
		API::modal_window(registration);
		});

	displayAll.events().click([&] {
		form lists(fm, rectangle{ 100,0,500,500 });
		label vLab{ lists }, rlLab{ lists }, cLab{ lists };
		listbox vehicle{ lists }, rentalLocation{ lists }, customer{ lists };

		vLab.format(true);
		vLab.caption("\n\n\n\n\n\t\t\t\t\t<bold size=14 center>Vehicle");
		rlLab.format(true);
		rlLab.caption("\n\n\n\n\n\t\t\t\t\t<bold size=14 center>Rental Locations");
		cLab.format(true);
		cLab.caption("\n\n\n\n\n\t\t\t\t\tt<bold size=14 center>Customers");
		lists.div("vert<<vL><vg>><<rlLa><rlLi>><<cLa><cLi>>");

		lists["vL"] << vLab;
		lists["vg"] << vehicle;
		lists["rlLa"] << rlLab;
		lists["rlLi"] << rentalLocation;
		lists["cLa"] << cLab;
		lists["cLi"] << customer;

		auto vehCategory = vehicle.at(0);
		auto custCategory = customer.at(0);
		auto rlCategory = rentalLocation.at(0);

		vehicle.append_header("Car Company");
		vehicle.append_header("Car Name");
		rentalLocation.append_header("Street Number");
		rentalLocation.append_header("Street Name");
		rentalLocation.append_header("Postal Code");
		customer.append_header("First Name");
		customer.append_header("Last Name");
		customer.append_header("Age");
		customer.append_header("Street Address");
		customer.append_header("Preferred Status");
		customer.append_header("Cars Rented");

		for (Vehicle v : vehicles) {
			vehCategory.append({ v.getCarCompany(),v.getCarName() });
		}

		for (RentalLocation rl : rentalLocations) {
			rlCategory.append({ std::to_string(rl.getStreetNumber()),rl.getStreetName(),rl.getPostalCode() });
			cout << std::to_string(rl.getStreetNumber()) + rl.getStreetName() + rl.getPostalCode() << endl;
		}

		for (Customer c : customers) {
			if (c.getPreferred() == 1)
				custCategory.append({ c.getFirstName(),c.getLastName(),std::to_string(c.getAge()),c.getStreetAddress(),"true" });
			else custCategory.append({ c.getFirstName(),c.getLastName(),std::to_string(c.getAge()),c.getStreetAddress(),"false" });
		}

		lists.collocate();
		API::modal_window(lists);
		});



	preferred.events().click([&] {
		form preference{ fm };
		combox cust{ preference };
		button preButton{ preference,"Set selected customer as preferred!" };
		preference.div("vert <cL> <sP>");
		preference["cL"] << cust;
		preference["sP"] << preButton;
		if (customers.empty()) {
			msgbox emptCustListErr("Error!");
			emptCustListErr << "Customer list is empty! Please add one or more customers!!";
			emptCustListErr.show();
			return;
		}
		for (Customer c : customers) {
			cust.push_back(c.getFirstName() + " " + c.getLastName());
		}
		preButton.events().click([&] {
			string custInfo;
			for (Customer& c : customers) {
				custInfo = c.getFirstName() + " " + c.getLastName();
				if (custInfo == cust.text(cust.option())) {
					bool b = true;
					c.setPreferred(b);
					cout << c.getPreferred() << endl;
				}
			}
			});
		preference.collocate();
		API::modal_window(preference);
		});

	returnRentedVeh.events().click([&] {
		string fullCustName, originListCustName, fullCarName, originListCarName;
		int i = 0;
		form returnForm{ fm };
		combox custBox{ returnForm };
		combox vehBox{ returnForm };
		button finalizeReturn{ returnForm, "Return Vehicle"};
		label custLab{ returnForm }, vehLab{ returnForm };
		custLab.format(true);
		vehLab.format(true);
		custLab.caption("Customer");
		vehLab.caption("Vehicle");

		returnForm.div("vert<<cl><cb>> vert<<vl><vb>> vert<<fr>>");
		returnForm["cl"] << custLab;
		returnForm["cb"] << custBox;
		returnForm["vl"] << vehLab;
		returnForm["vb"] << vehBox;
		returnForm["fr"] << finalizeReturn;
		
		for (Customer c : customers) {
			fullCustName = c.getFirstName() + " " + c.getLastName();
			custBox.push_back(fullCustName);
		}

		custBox.events().selected([&] {
			vehBox.clear();
			for(Customer c : customers) {
				originListCustName = c.getFirstName() + " " + c.getLastName();
				if (originListCustName == custBox.text(custBox.option())) {
					vector<Vehicle>& clVehicles = c.getVehicleList();
					for (Vehicle& v : clVehicles) {
						fullCarName = v.getCarCompany() + " " + v.getCarName();
						vehBox.push_back(fullCarName);
					}
				}
			}
			});

		finalizeReturn.events().click([&] {
			
			for (Customer c : customers) {
				originListCustName = c.getFirstName() + " " + c.getLastName();
				if (originListCustName == custBox.text(custBox.option())) {
					vector<Vehicle>& clVehicles = c.getVehicleList();
					for (Vehicle& v : clVehicles) {
						fullCarName = v.getCarCompany() + " " + v.getCarName();
						if (fullCarName == vehBox.text(vehBox.option())) {
							vehBox.erase(vehBox.option());
							clVehicles.erase(clVehicles.begin() + i);
							break;
						} 
						i++;
					}
				}
			}


			});


		returnForm.collocate();
		API::modal_window(returnForm);
		});

	aboutButton.events().click([&fm] {
		msgbox abtProjectmsg("About Project");
		abtProjectmsg << "This is a Rental Program where you can manage, i.e add or delete vehicles, customers and rental locations. It also allows for setting customers to the preferred status (Think VIP), display all vehicles, customers with their preferred status and rental locations that are currently in the system as well as assigning vehicles to a rental location of the user's choice along with the future addition of customers renting vehicles as well as returning them.\n\nCreated by: Malik Z\nProgrammed in Visual Studio using the C++ Programming Language and Nana GUI Library\nYou can check back on this project at my GitHub which is MHW-MZX where my project resides in the repository with the name Nana-Vehicle-GUI  ";
		abtProjectmsg.show();
		});

	dateDisplay.events().click([&] {dateDisplayLabel.caption("Current Date: " +  string(dateInString));});

	clock.elapse([&] {timeDisplay.caption(" Time: " + std::to_string(i++));});

	timerButton.events().click([&] {clock.start();});

	quitBtn.events().click([&fm] {fm.close();});



	//Layout management
	fm.div("vert <<text>> vert<<time><date>> vert<<button1><button2><button3>> vert<<button4><button5><button6>> vert<<button7><button8><button9>> vert<<button10><button11><button12>> vert<<button13><button14><button15>> <button16> <button17> <button18>");
	fm["text"] << lab;
	fm["time"] << timeDisplay;
	fm["date"] << dateDisplayLabel;
	fm["button1"] << addCustButton;
	fm["button2"] << editCustomer;
	fm["button3"] << removeCustButton;
	fm["button4"] << addRentalLocation;
	fm["button5"] << editRentalLocation;
	fm["button6"] << removeRentalLocation;
	fm["button7"] << addCar;
	fm["button8"] << editVehicle;
	fm["button9"] << removeCar;
	fm["button10"] << assignLocationtoVehicle;
	fm["button11"] << assignVehtoCust;
	fm["button12"] << returnRentedVeh;
	fm["button13"] << displayAll;
	fm["button14"] << preferred;
	fm["button15"] << dateDisplay;
	fm["button16"] << timerButton;
	fm["button17"] << aboutButton;
	fm["button18"] << quitBtn;


	fm.collocate();

	//Show the form
	fm.show();

	//Start to event loop process, it blocks until the form is closed.
	exec();
}
#endif