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



using namespace std;
using namespace nana;


int main()
{
    //Define a form.
    form fm{ rectangle{520,160,500,500} };
    label time{ fm };
    
    timer clock{std::chrono::seconds{0}};
    vector<Customer> customers;
    vector<Vehicle> vehicles;
    vector<RentalLocation> rentalLocations;

    time.format(true);

    //Define a label and display a text.
    label lab{ fm, "<bold blue size=12>Welcome to the car rental system</>" };
    lab.format(true);

    button addCustButton{ fm,"Add Customer" };
    button removeCustButton{ fm,"Remove Customer" };

    //Define a button and answer the click event.
    button quitBtn{ fm, "Quit" };
    quitBtn.events().click([&fm] {fm.close();});

    button assignLocationtoVehicle{ fm,"Assign rental location to vehicle" };
    button addCar{ fm,"Add Vehicle" };
    button removeCar{ fm,"Remove Vehicle" };
    button addRentalLocation{ fm,"Add Rental Location" };
    button removeRentalLocation{ fm,"Remove Rental Location" };
    button displayAll{ fm,"Display Vehicles, Customers and Rental Locations" };
    button timerButton{ fm, "Display time counter" };
    button assignVehtoCust{fm,"Assign vehicle to customer"};
    button preferred{ fm,"Set customer to preferred status" };


    Customer test1("Mike", "Wazowski", 55, "1234 Arsene Lupin ave");
    Customer test2("Sulley", "Goliath", 65, "6789 Snowman blvd");

    Vehicle testVeh1("Honda", "Yoda");
    Vehicle testVeh2("Mazda", "Dazda");

    RentalLocation testRl1(888, "Street Blvd", "BNG4TG");
    RentalLocation testRl2(555, "Address Street", "V9HQ3E");

    customers.push_back(test1);
    customers.push_back(test2);

    vehicles.push_back(testVeh1);
    vehicles.push_back(testVeh2);

    rentalLocations.push_back(testRl1);
    rentalLocations.push_back(testRl2);


    
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
            Customer cust(fName, lName, stoi(age), sa);
            for (Customer c : customers) {
                if (c.getFirstName() == cust.getFirstName() && c.getLastName() == cust.getLastName() && c.getAge() == cust.getAge() && c.getStreetAddress() == cust.getStreetAddress()) {
                    msgbox alreadyExistsMessageCustomer("Warning!!");
                    alreadyExistsMessageCustomer << "Warning!! The customer with the first name " + c.getFirstName() + ", last name: " + c.getLastName() + ", age: " + std::to_string(c.getAge()) + " and with the street address: " + c.getStreetAddress() + " already exists!!";
                    alreadyExistsMessageCustomer.show();
                    return;
                }
            }
            customers.push_back(cust);
            cout << "Customers in the database:" << endl;
            for (Customer c : customers) cout << "First Name: " << c.getFirstName() + ", last name: " + c.getLastName() + ", age: " + std::to_string(c.getAge()) + " and street address: " + c.getStreetAddress() << endl;
            });

        newForm.collocate();
        API::modal_window(newForm); 
        });
    
    removeCustButton.events().click([&] {
        form deleteForm(fm);
        button deleteButton{ deleteForm, "Remove Customer" };
        combox combo(deleteForm);
        deleteForm.div("vert <cbx> <b>");
        deleteForm["cbx"] << combo;
        deleteForm["b"] << deleteButton;
        
        for (Customer cust : customers) {
            if (customers.empty())
                break;
            else combo.push_back(cust.getFirstName() + " " + cust.getLastName());
        }
        deleteButton.events().click([&] {
            int i = 0;
            cout << combo.text(0) << endl;
            for (Customer cust : customers) {
                string firstLastName = cust.getFirstName() + " " + cust.getLastName();
                if (firstLastName == combo.text(0)) {
                    cout << "Found" << endl;
                    combo.erase(i);
                    customers.erase(customers.begin() + i);
                }
                i++;
            }
            cout << "Not Found" << endl;
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
            for (Vehicle v : vehicles) {
                if (vehicles.empty()) break;
                else cout << v.toString();
            }
            });

        addCarForm.collocate();
        API::modal_window(addCarForm);
        });

    removeCar.events().click([&] {

        form removeCarForm(fm);
        combox removeCarCombo(removeCarForm);
        button finalizeCarRemoval{ removeCarForm,"Remove Vehicle" };


        removeCarForm.div("vert <CCMB><CCB>");
        removeCarForm["CCMB"] << removeCarCombo;
        removeCarForm["CCB"] << finalizeCarRemoval;

        for (Vehicle v : vehicles)
            if (vehicles.empty())
                break;
            else removeCarCombo.push_back(v.getCarCompany() + " " + v.getCarName());

        finalizeCarRemoval.events().click([&] {
            int i = 0;
            string fullCarInfo;
            for (Vehicle v : vehicles) {
                fullCarInfo = v.getCarCompany() + " " + v.getCarName();
                if (fullCarInfo == removeCarCombo.text(0)) {
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
            RentalLocation rl(stoi(sNumber), sName, pCode);

            for (RentalLocation rLoc : rentalLocations) {
                if (rLoc.getStreetNumber() == rl.getStreetNumber() && rLoc.getStreetName() == rl.getStreetName() && rLoc.getPostalCode() == rl.getPostalCode()) {
                    msgbox alreadyExistsMessageRL("Warning!!");
                    alreadyExistsMessageRL << std::string() + "Warning!! The rental location with the Street Number : " + std::to_string(rl.getStreetNumber()) + " , with the Street Name : " + rl.getStreetName() + " and with the Postal Code: " + rl.getPostalCode() + " already exists!!";
                    alreadyExistsMessageRL.show();
                    return;
                }
            }

            rentalLocations.push_back(rl);

            });


        addRentalLocationForm.collocate();
        API::modal_window(addRentalLocationForm);
        });

    removeRentalLocation.events().click([&] {
        form removeRentalLocationForm(fm);
        button finalizeRLRemoval{ removeRentalLocationForm, "Remove Rental Location" };
        combox removeRLCombo(removeRentalLocationForm);
        removeRentalLocationForm.div("vert <DRLC><DRLB>");
        removeRentalLocationForm["DRLC"] << removeRLCombo;
        removeRentalLocationForm["DRLB"] << finalizeRLRemoval;
        for (RentalLocation rl : rentalLocations) removeRLCombo.push_back(rl.getStreetNumber() + " " + rl.getStreetName() + " " + rl.getPostalCode());
        finalizeRLRemoval.events().click([&] {
            int i = 0;
            string fullRLInfo;
            for (RentalLocation rl : rentalLocations) {
                fullRLInfo = rl.getStreetNumber() + " " + rl.getStreetName() + " " + rl.getPostalCode();
                if (fullRLInfo == removeRLCombo.text(0)) {
                    removeRLCombo.erase(i);
                    rentalLocations.erase(rentalLocations.begin() + i);
                    return;

                }
            }
            });
        removeRentalLocationForm.collocate();
        API::modal_window(removeRentalLocationForm);
        });
    


    assignLocationtoVehicle.events().click([&] {
        int snum;
        string cc, cn,sn,pc;
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
        label vehLab{ registration }, rentalLab{ registration }, custLab{ registration },beginDateLab{registration},endDateLab{registration};
        combox vehiclesList{ registration }, rentalLocationsList{ registration }, customerList{ registration };
        textbox beginDateInput{ registration },endDateInput{registration};
        button registrationButton{registration,"Rent Vehicle"};

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
            for (RentalLocation& rl : rentalLocations) {
                fullRLInfo = std::to_string(rl.getStreetNumber()) + " " + rl.getStreetName();
                if (fullRLInfo == rentalLocationsList.text(rentalLocationsList.option())) {
                    vehiclesList.clear();
                    cout << "found" << endl;
                    vector<Vehicle>& rlVehicles = rl.getVehiclesList();
                    for (Vehicle v : rl.getVehiclesList()) {
                        vehiclesList.push_back(v.getCarCompany() + " " + v.getCarName());
                        cout << v.getCarCompany() << endl;
                    }
                }
            }

            registrationButton.events().click([&] {
                string bd, ed, carInfo,custInfo;
                beginDateInput.getline(0, bd);
                endDateInput.getline(0, ed);
                for (Customer& c : customers) {
                    custInfo = c.getFirstName() + " " + c.getLastName();
                    if (custInfo == customerList.text(customerList.option())) {
                        for (Vehicle& v : vehicles) {
                            carInfo = v.getCarCompany() + " " + v.getCarName();
                            if (carInfo == rentalLocationsList.text(rentalLocationsList.option())) {

                                c.addRentalVehToList(v);
                            }
                        }
                    }
                }
                });

            });

        registrationButton.events().click([&] {
            string rlInfo, vehInfo, custInfo;

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
            vehCategory.append({ v.getCarCompany(),v.getCarName()});
            
        }

        for (RentalLocation rl : rentalLocations) {
            rlCategory.append({ std::to_string(rl.getStreetNumber()),rl.getStreetName(),rl.getPostalCode() });
            
        }

        for (Customer c : customers) {
            if(c.getPreferred() == 1)
                custCategory.append({ c.getFirstName(),c.getLastName(),std::to_string(c.getAge()),c.getStreetAddress(),"true"});
            else custCategory.append({c.getFirstName(),c.getLastName(),std::to_string(c.getAge()),c.getStreetAddress(),"false"});
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



    clock.elapse([&] {
        static int i = 0;
        time.caption("Time: " + std::to_string(i++));
        });
        

    timerButton.events().click([&] {
        clock.start();
        });

    

    //Layout management
    fm.div("vert <<text><time>> vert<<button1><button2>> vert<<button3><button4>> vert<<button5><button6>> vert<<button7><button8>> vert<<button9><button10>> <button11><button12>");
    fm["text"] << lab;
    fm["time"] << time;
    fm["button1"] << addCustButton;
    fm["button2"] << removeCustButton;
    fm["button3"] << addCar;
    fm["button4"] << removeCar;
    fm["button5"] << addRentalLocation;
    fm["button6"] << removeRentalLocation;
    fm["button7"] << assignLocationtoVehicle;
    fm["button8"] << displayAll;
    fm["button9"] << assignVehtoCust;
    fm["button10"] << timerButton;
    fm["button11"] << preferred;
    fm["button12"] << quitBtn;
    
    fm.collocate();

    //Show the form
    fm.show();

    //Start to event loop process, it blocks until the form is closed.
    exec();
}
#endif