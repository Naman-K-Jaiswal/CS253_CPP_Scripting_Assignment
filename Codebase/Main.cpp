#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Utilities.cpp"

using namespace std;

int main()
{
    CarQuerier carQuerier;
    CustomerQuerier customerQuerier;
    EmployeeQuerier employeeQuerier;
    ManagerQuerier managerQuerier;

    cout << "Welcome to the Car Management System built by Naman Kumar Jaiswal (220687) \n";

    while (true)
    {
        cout << "\nChoose appropriate command for Login: \n";
        cout << "1 for Customer \n";
        cout << "2 for Employee \n";
        cout << "3 for Manager \n";
        cout << "4 to Quit the interface \n";
        cout << "Input Command to continue (without any trailing spaces): ";

        string input;
        getline(cin, input);

        if (input.length() > 1)
        {
            cout << "\nInvalid Command. Please choose a valid option.\n";
            continue;
        }

        int command = stoi(input);
        if (command == 4)
        {
            return 0;
        }

        switch (command)
        {
        case 1:
        {
            // Customer Login
            cout << "Enter Customer UserID: ";
            string userID;
            getline(cin, userID);

            cout << "Enter Password: ";
            string password;
            getline(cin, password);

            int loginResult = customerQuerier.customerLogin(userID, password);

            if (loginResult == 2)
            {
                while (true)
                {
                    // Customer Options
                    cout << "Customer options go here\n\n";
                    cout << "1 for Browsing Available Cars\n";
                    cout << "2 for Browsing Rented Cars\n";
                    cout << "3 for Renting a Car\n";
                    cout << "4 to Quit the Terminal\n";
                    getline(cin, input);

                    if (input.length() > 1)
                    {
                        cout << "\nInvalid Command. Please choose a valid option.\n";
                        continue;
                    }

                    Customer Run1 = customerQuerier.GetCustomerById(userID);
                    Run1.SetRentedCars(carQuerier.ViewRentedCars(userID));

                    int command = stoi(input);
                    if (command == 4)
                    {
                        return 0;
                    }
                    else if (command == 1)
                    {
                        carQuerier.Browse(Run1.GetCustomerRecord());
                    }
                    else if (command == 2)
                    {
                        Run1.ViewRentedCars();
                    }
                    else if (command == 3)
                    {
                        // Renting a Car
                        string carModel;
                        int dueDay, dueMonth, dueYear;

                        cout << "Enter Car Model to Rent: ";
                        getline(cin, carModel);

                        cout << "Enter Due Date (DD MM YYYY):\n";
                        cout << "Day: ";
                        cin >> dueDay;
                        cout << "Month: ";
                        cin >> dueMonth;
                        cout << "Year: ";
                        cin >> dueYear;
                        cin.ignore(); // Clear the newline character from the input buffer

                        Date dueDate(dueDay, dueMonth, dueYear);

                        Car rentedCar = customerQuerier.RentCar(Run1.GetUserID(), carModel, dueDate, carQuerier);

                        if (rentedCar.GetRentedStatus() == 1)
                        {
                            cout << "Car rented successfully!\n";
                            rentedCar.SetAvailability(Run1.GetUserID(), dueDate);
                            vector<Car> rentedCars = Run1.GetRentedCars();
                            rentedCars.push_back(rentedCar);
                            Run1.SetRentedCars(rentedCars);
                        }
                        else
                        {
                            cout << "Car not available for rent or model not found!\n";
                        }
                    }
                    else
                    {
                        cout << "\nInvalid Command. Please choose a valid option.\n";
                    }
                }
            }
            else if (loginResult == 1)
            {
                cout << "Incorrect Password. Please try again.\n";
            }
            else
            {
                cout << "User (Customer) not found. Kindly Contact a Manager to Sign You Up.\n";
            }
            break;
        }

        case 2:
        {
            // Employee Login
            cout << "Enter Employee UserID: ";
            string userID;
            getline(cin, userID);

            cout << "Enter Password: ";
            string password;
            getline(cin, password);

            int loginResult = employeeQuerier.employeeLogin(userID, password);

            if (loginResult == 2)
            {
                while (true)
                {
                    // Employee Options
                    cout << "Employee options go here\n\n";
                    cout << "1 for Browsing Available Cars\n";
                    cout << "2 for Browsing Rented Cars\n";
                    cout << "3 for Renting a Car\n";
                    cout << "4 to Quit the Terminal\n";
                    getline(cin, input);

                    if (input.length() > 1)
                    {
                        cout << "\nInvalid Command. Please choose a valid option.\n";
                        continue;
                    }

                    Employee Run1 = employeeQuerier.GetEmployeeById(userID);
                    Run1.SetRentedCars(carQuerier.ViewRentedCars(userID));

                    int command = stoi(input);
                    if (command == 4)
                    {
                        return 0;
                    }
                    else if (command == 1)
                    {
                        carQuerier.Browse(Run1.GetEmployeeRecord());
                    }
                    else if (command == 2)
                    {
                        Run1.ViewRentedCars();
                    }
                    else if (command == 3)
                    {
                        // Renting a Car for a Customer
                        string carModel;
                        int dueDay, dueMonth, dueYear;
                        cout << "Enter Car Model to Rent: ";
                        getline(cin, carModel);

                        cout << "Enter Due Date (DD MM YYYY):\n";
                        cout << "Day: ";
                        cin >> dueDay;
                        cout << "Month: ";
                        cin >> dueMonth;
                        cout << "Year: ";
                        cin >> dueYear;
                        cin.ignore(); // Clear the newline character from the input buffer

                        Date dueDate(dueDay, dueMonth, dueYear);

                        Car rentedCar = employeeQuerier.RentCarForCustomer(Run1.GetUserID(), carModel, dueDate, carQuerier);

                        if (rentedCar.GetRentedStatus() == 1)
                        {
                            cout << "Car rented successfully!\n";
                            rentedCar.SetAvailability(Run1.GetUserID(), dueDate);
                            Customer customer = customerQuerier.GetCustomerById(Run1.GetUserID());
                            vector<Car> rentedCars = customer.GetRentedCars();
                            rentedCars.push_back(rentedCar);
                            customer.SetRentedCars(rentedCars);
                        }
                        else
                        {
                            cout << "Car not available for rent or model not found!\n";
                        }
                    }
                    else
                    {
                        cout << "\nInvalid Command. Please choose a valid option.\n";
                    }
                }
            }
            else if (loginResult == 1)
            {
                cout << "Incorrect Password. Please try again.\n";
            }
            else
            {
                cout << "User (Employee) not found. Kindly Contact a Manager to Sign You Up.\n";
            }
            break;
        }
        
        case 3:
        {
            // Manager Login
            cout << "Enter Manager UserID: ";
            string userID;
            getline(cin, userID);

            cout << "Enter Password: ";
            string password;
            getline(cin, password);

            int loginResult = managerQuerier.managerLogin(userID, password);

            if (loginResult == 2)
            {
                while (true)
                {
                    // Manager Options
                    cout << "\nManager options go here\n";
                    cout << "01 for Adding a Customer\n";
                    cout << "02 for Updating a Customer\n";
                    cout << "03 for Deleting a Customer\n";
                    cout << "04 for Adding a Employee\n";
                    cout << "05 for Updating a Employee\n";
                    cout << "06 for Deleting a Employee\n";
                    cout << "07 for Adding a Manager\n";
                    cout << "08 for Updating a Manager\n";
                    cout << "09 for Deleting a Manager\n";
                    cout << "10 for Adding a Car\n";
                    cout << "11 for Updating a Car\n";
                    cout << "12 for Deleting a Car\n";
                    cout << "13 to Validate a Car Return\n";
                    cout << "14 to Impose Due for a Customer\n";
                    cout << "15 to Clear Due for a Customer\n";
                    cout << "16 to Reduce Due for a Customer\n";
                    cout << "17 to Impose Due for an Employee\n";
                    cout << "18 to Clear Due for an Employee\n";
                    cout << "19 to Reduce Due for an Employee\n";
                    cout << "00 to Quit the Terminal\n";
                    getline(cin, input);

                    if (input.length() != 2)
                    {
                        cout << "\nInvalid Command. Please choose a valid option.\n";
                        continue;
                    }

                    if (input == "00")
                    {
                        return 0;
                    }

                    // Customer-related Operations
                    if (input == "01")
                    {
                        // Adding a Customer
                        string name, userID, password;
                        float customerRecord, fineDue;

                        cout << "\nEnter Customer Name: ";
                        getline(std::cin, name);

                        do
                        {
                            cout << "Enter Customer UserID (7-digit starting with 'CUST'): ";
                            getline(std::cin, userID);
                        } while (userID.length() != 7 || userID.substr(0, 4) != "CUST" || !customerQuerier.isUserIDUnique(userID));

                        cout << "Enter Password: ";
                        getline(std::cin, password);

                        Customer newCustomer(name, userID, password);
                        customerQuerier.AddCustomer(newCustomer);
                    }

                    if (input == "02")
                    { // Update a Customer
                        string userID;
                        cout << "Enter Customer UserID to update: ";
                        getline(cin, userID);

                        CustomerQuerier customerQuerier;
                        Customer existingCustomer = customerQuerier.GetCustomerById(userID);

                        if (existingCustomer.GetUserID() == "")
                        {
                            cout << "Customer with UserID " << userID << " not found.\n";
                        }
                        else
                        {
                            string name, password;
                            float customerRecord, fineDue;

                            cout << "\nEnter Updated Customer Name: ";
                            getline(cin, name);

                            cout << "Enter Updated Customer Password: ";
                            getline(cin, password);

                            cout << "Enter Updated Customer Record: ";
                            cin >> customerRecord;

                            cout << "Enter Updated Customer Fine Due: ";
                            cin >> fineDue;

                            Customer updatedCustomer(name, userID, password, customerRecord, fineDue);
                            customerQuerier.UpdateCustomer(updatedCustomer);
                            cout << "Customer updated successfully.\n";
                        }
                    }

                    if (input == "03")
                    {
                        // Deleting a Customer
                        cout << "\nEnter UserID: ";
                        string userID;
                        getline(cin, userID);
                        customerQuerier.DeleteCustomer(userID);
                    }

                    // Employee-related Operations
                    if (input == "04")
                    {
                        // Adding an Employee
                        string name, userID, password;
                        float employeeRecord, fineDue;

                        cout << "\nEnter Employee Name: ";
                        getline(std::cin, name);

                        do
                        {
                            cout << "Enter Employee UserID (7-digit starting with 'EMPL'): ";
                            getline(std::cin, userID);
                        } while (userID.length() != 7 || userID.substr(0, 4) != "EMPL" || employeeQuerier.isUserIDUnique(userID));

                        cout << "Enter Password: ";
                        getline(std::cin, password);

                        Employee newEmployee(name, userID, password);
                        employeeQuerier.AddEmployee(newEmployee);
                    }

                    if (input == "05")
                    { // Update an Employee
                        string userID;
                        cout << "Enter Employee UserID to update: ";
                        getline(cin, userID);

                        EmployeeQuerier employeeQuerier;
                        Employee existingEmployee = employeeQuerier.GetEmployeeById(userID);

                        if (existingEmployee.GetUserID() == "")
                        {
                            cout << "Employee with UserID " << userID << " not found.\n";
                        }
                        else
                        {
                            string name, password;
                            float employeeRecord, fineDue;

                            cout << "\nEnter Updated Employee Name: ";
                            getline(cin, name);

                            cout << "Enter Updated Employee Password: ";
                            getline(cin, password);

                            cout << "Enter Updated Employee Record: ";
                            cin >> employeeRecord;

                            cout << "Enter Updated Employee Fine Due: ";
                            cin >> fineDue;

                            Employee updatedEmployee(name, userID, password, employeeRecord, fineDue);
                            employeeQuerier.UpdateEmployee(updatedEmployee);
                            cout << "Employee updated successfully.\n";
                        }
                    }

                    if (input == "06")
                    {
                        // Deleting an Employee
                        cout << "\nEnter UserID: ";
                        string userID;
                        getline(cin, userID);
                        employeeQuerier.DeleteEmployee(userID);
                    }

                    // Manager-related Operations
                    if (input == "07")
                    {
                        // Adding a Manager
                        string name, userID, password;

                        cout << "\nEnter Manager Name: ";
                        getline(std::cin, name);

                        do
                        {
                            cout << "Enter Manager UserID (7-digit starting with 'MNGR'): ";
                            getline(std::cin, userID);
                        } while (userID.length() != 7 || userID.substr(0, 4) != "MNGR" || managerQuerier.isUserIDUnique(userID));

                        cout << "Enter Password: ";
                        getline(std::cin, password);

                        Manager newManager(name, userID, password);
                        managerQuerier.AddManager(newManager);
                    }

                    if (input == "08")
                    { // Update a Manager
                        string userID;
                        cout << "Enter Manager UserID to update: ";
                        getline(cin, userID);

                        ManagerQuerier managerQuerier;
                        Manager existingManager = managerQuerier.GetManagerById(userID);

                        if (existingManager.GetUserID() == "")
                        {
                            cout << "Manager with UserID " << userID << " not found.\n";
                        }
                        else
                        {
                            string name, password;

                            cout << "\nEnter Updated Manager Name: ";
                            getline(cin, name);

                            cout << "Enter Updated Manager Password: ";
                            getline(cin, password);

                            Manager updatedManager(name, userID, password);
                            managerQuerier.UpdateManager(updatedManager);
                            cout << "Manager updated successfully.\n";
                        }
                    }

                    if (input == "09")
                    {
                        // Deleting a Manager
                        cout << "\nEnter UserID: ";
                        string userID;
                        getline(cin, userID);
                        managerQuerier.DeleteManager(userID);
                    }

                    // Car-related Operations
                    if (input == "10")
                    {
                        // Adding a Car
                        string model;
                        float condition, maxSpeed, kmRun, minScoreNeeded, ratePerKm, ratePerDay;

                        cout << "Enter Car Model: ";
                        getline(cin, model);

                        cout << "Enter Car Condition: ";
                        cin >> condition;

                        cout << "Enter Maximum Speed: ";
                        cin >> maxSpeed;

                        cout << "Enter Kilometers Run: ";
                        cin >> kmRun;

                        cout << "Enter Minimum Score Needed: ";
                        cin >> minScoreNeeded;

                        cout << "Enter Rate per Km: ";
                        cin >> ratePerKm;

                        cout << "Enter Rate per Day: ";
                        cin >> ratePerDay;

                        cin.ignore(); // Ignore the newline character

                        Car newCar(model, condition, maxSpeed, kmRun, minScoreNeeded, ratePerKm, ratePerDay);
                        carQuerier.AddCar(newCar);
                        cout << "Car added successfully!\n";
                    }

                    if (input == "11")
                    {
                        // Updating a Car
                        string model;
                        float newCondition, newMaxSpeed, newKmRun, newMinScoreNeeded, newRatePerKm, newRatePerDay;

                        cout << "Enter Car Model to update: ";
                        getline(cin, model);

                        cout << "Enter New Car Condition: ";
                        cin >> newCondition;

                        cout << "Enter New Maximum Speed: ";
                        cin >> newMaxSpeed;

                        cout << "Enter New Kilometers Run: ";
                        cin >> newKmRun;

                        cout << "Enter New Minimum Score Needed: ";
                        cin >> newMinScoreNeeded;

                        cout << "Enter New Rate per Km: ";
                        cin >> newRatePerKm;

                        cout << "Enter New Rate per Day: ";
                        cin >> newRatePerDay;

                        cin.ignore(); // Ignore the newline character

                        Car updatedCar(model, newCondition, newMaxSpeed, newKmRun, newMinScoreNeeded, newRatePerKm, newRatePerDay);
                        carQuerier.UpdateCar(updatedCar);
                        cout << "Car updated successfully!\n";
                    }

                    if (input == "12")
                    {
                        // Deleting a Car
                        string modelToDelete;
                        cout << "Enter Car Model to delete: ";
                        getline(cin, modelToDelete);

                        carQuerier.DeleteCar(modelToDelete);
                        cout << "Car deleted successfully!\n";
                    }

                    if (input == "13")
                    {
                        // Validating Car Return
                        string carModel;
                        cout << "Enter the car model: ";
                        cin >> carModel;

                        authenticatePayment(carModel, carQuerier, customerQuerier, employeeQuerier);
                    }

                    // Due Operations for Customer
                    if (input == "14")
                    {
                        // Imposing Due for a Customer
                        string userID;
                        float amount;

                        cout << "Enter Customer UserID: ";
                        getline(cin, userID);

                        cout << "Enter Due Amount: ";
                        cin >> amount;
                        cin.ignore(); // Consume the newline character

                        customerQuerier.ImposeDue(userID, amount);
                    }

                    if (input == "15")
                    {
                        // Clearing Due for a Customer
                        string userID;

                        cout << "Enter Customer UserID: ";
                        getline(cin, userID);

                        customerQuerier.ClearDue(userID);
                    }

                    if (input == "16")
                    {
                        // Reducing Due for a Customer
                        string userID;
                        float amount;

                        cout << "Enter Customer UserID: ";
                        getline(cin, userID);

                        cout << "Enter Due Reduction Amount: ";
                        cin >> amount;
                        cin.ignore(); // Consume the newline character

                        customerQuerier.ReduceDue(userID, amount);
                    }

                    // Due Operations for Employee
                    if (input == "17")
                    {
                        // Imposing Due for an Employee
                        string userID;
                        float amount;

                        cout << "Enter Employee UserID: ";
                        getline(cin, userID);

                        cout << "Enter Due Amount: ";
                        cin >> amount;
                        cin.ignore(); // Consume the newline character

                        employeeQuerier.ImposeDue(userID, amount);
                    }

                    if (input == "18")
                    {
                        // Clearing Due for an Employee
                        string userID;

                        cout << "Enter Employee UserID: ";
                        getline(cin, userID);

                        employeeQuerier.ClearDue(userID);
                    }

                    if (input == "19")
                    {
                        // Reducing Due for an Employee
                        string userID;
                        float amount;

                        cout << "Enter Employee UserID: ";
                        getline(cin, userID);

                        cout << "Enter Due Reduction Amount: ";
                        cin >> amount;
                        cin.ignore(); // Consume the newline character

                        employeeQuerier.ReduceDue(userID, amount);
                    }
                }
            }
            else if (loginResult == 1)
            {
                cout << "Incorrect Password. Please try again.\n";
            }
            else
            {
                cout << "User (Manager) not found. Kindly Contact a Manager to Sign You Up.\n";
            }
            break;
        }

        default:
            cout << "\nInvalid Command. Please choose a valid option.\n";
        }
    }

    return 0;
}