#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

class Date
{
private:
    time_t timestamp;

public:
    // Constructor
    Date(int day, int month, int year)
    {
        tm timeStruct = {};
        timeStruct.tm_mday = day;
        timeStruct.tm_mon = month - 1;    // tm_mon is 0-indexed
        timeStruct.tm_year = year - 1900; // tm_year is years since 1900
        timestamp = mktime(&timeStruct);
    }

    // Accessor functions
    int GetDay() const
    {
        tm timeStruct = *localtime(&timestamp);
        return timeStruct.tm_mday;
    }

    int GetMonth() const
    {
        tm timeStruct = *localtime(&timestamp);
        return timeStruct.tm_mon + 1; // tm_mon is 0-indexed
    }

    int GetYear() const
    {
        tm timeStruct = *localtime(&timestamp);
        return timeStruct.tm_year + 1900; // tm_year is years since 1900
    }

    // Compare dates (ignoring time)
    bool operator<(const Date &other) const
    {
        return timestamp < other.timestamp;
    }

    bool operator>(const Date &other) const
    {
        return timestamp > other.timestamp;
    }

    bool operator==(const Date &other) const
    {
        return timestamp == other.timestamp;
    }

    // Function to find the difference between two dates in terms of days
    int DifferenceInDays(const Date &other) const
    {
        const int secondsInDay = 24 * 60 * 60;
        return difftime(other.timestamp, timestamp) / secondsInDay;
    }

    // Function to output date as a string in "DD Month YYYY" format
    string ToString() const
    {
        tm timeStruct = *localtime(&timestamp);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%d %B %Y", &timeStruct);
        return buffer;
    }
};


class Car
{
private:
    string Model;
    float Condition;
    int RentedStatus;
    string UserID;
    Date DueDate;
    float MaximumSpeed;
    float KilometersRun;
    float MinScoreNeeded;
    float RatePerKm;
    float RatePerDay;

public:
    Car(const string &model, float condition, float maxSpeed = 200.0f, float kmRun = 0.0f,
        float minScoreNeeded = 50.0f, float ratePerKm = 10.0f, float ratePerDay = 250.0f)
        : Model(model), Condition(condition), RentedStatus(0), UserID(""), DueDate(1, 1, 2000),
          MaximumSpeed(maxSpeed), KilometersRun(kmRun),
          MinScoreNeeded(minScoreNeeded), RatePerKm(ratePerKm), RatePerDay(ratePerDay) {}

    // Accessor functions
    string GetModel() const { return Model; }
    float GetCondition() const { return Condition; }
    int GetRentedStatus() const { return RentedStatus; }
    string GetUserID() const { return UserID; }
    Date GetDueDate() const { return DueDate; }
    float GetMaximumSpeed() const { return MaximumSpeed; }
    float GetKilometersRun() const { return KilometersRun; }
    float GetMinScoreNeeded() const { return MinScoreNeeded; }
    float GetRatePerKm() const { return RatePerKm; }
    float GetRatePerDay() const { return RatePerDay; }

    void SetAvailability(const string &userID, const Date &dueDate, int rentedStatus = 1)
    {
        RentedStatus = rentedStatus;
        UserID = userID;
        DueDate = dueDate;
    }

    void SetKmRun(int newKmRun)
    {
        KilometersRun = newKmRun;
    };
};

// All the customerID start with 'CUST' and employeeID with 'EMPL' and manager with 'MNGR'

// All the customerID start with 'CUST' and employeeID with 'EMPL' and manager with 'MNGR'

class User
{
protected:
    string Name;
    string UserID;
    string Password;

public:
    User(const string &Name, const string &UserID, const string &Password)
        : Name(Name), UserID(UserID), Password(Password) {}

    string GetName() const { return Name; }
    string GetUserID() const { return UserID; }
    string GetPassword() const { return Password; }
};

class Customer : public User
{
protected:
    float CustomerRecord; // varies b/w 0 and 100
    float FineDue;
    vector<Car> RentedCars;

public:
    Customer(const string &Name, const string &UserID, const string &Password, float CustomerRecord = 50.0f, float FineDue = 0.0f)
        : User(Name, UserID, Password), CustomerRecord(CustomerRecord), FineDue(FineDue) {}

    float GetCustomerRecord() const { return CustomerRecord; }
    float GetFineDue() const { return FineDue; }
    const vector<Car> &GetRentedCars() const { return RentedCars; }

    void ClearDue()
    {
        this->FineDue = 0.0f;
    }

    void ImposeDue(float due)
    {
        this->FineDue += due;
    }

    void ViewRentedCars() const
    {
        cout << "Rented Cars:\n";
        for (const auto &car : RentedCars)
        {
            cout << "Model: " << car.GetModel() << ", Condition: " << car.GetCondition()
                 << ", Maximum Speed: " << car.GetMaximumSpeed() << ", Kilometers Run: " << car.GetKilometersRun()
                 << ", Due Date: " << car.GetDueDate().ToString() << ", Rate per Km: " << car.GetRatePerKm()
                 << ", Rate per Day: " << car.GetRatePerDay() << endl;
        }
    }

    void SetRentedCars(const vector<Car> &cars)
    {
        RentedCars = cars;
    }

    void ReduceDue(float amount)
    {
        if (amount >= 0)
        {
            FineDue -= amount;
        }
    }
};


class Employee : public User
{
protected:
    float EmployeeRecord; // varies b/w 0 and 100
    float FineDue;
    vector<Car> RentedCars;

public:
    Employee(const string &Name, const string &UserID, const string &Password, float EmployeeRecord = 60.0f, float FineDue = 0.0f)
        : User(Name, UserID, Password), EmployeeRecord(EmployeeRecord), FineDue(FineDue) {}

    float GetEmployeeRecord() const { return EmployeeRecord; }
    float GetFineDue() const { return FineDue; }
    const vector<Car> &GetRentedCars() const { return RentedCars; }

    void ClearDue()
    {
        this->FineDue = 0.0f;
    }

    void ImposeDue(float due)
    {
        this->FineDue += due;
    }

    void ViewRentedCars() const
    {
        cout << "Rented Cars:\n";
        for (const auto &car : RentedCars)
        {
            cout << "Model: " << car.GetModel() << ", Condition: " << car.GetCondition()
                 << ", Maximum Speed: " << car.GetMaximumSpeed() << ", Kilometers Run: " << car.GetKilometersRun()
                 << ", Due Date: " << car.GetDueDate().ToString() << ", Rate per Km: " << car.GetRatePerKm()
                 << ", Rate per Day: " << car.GetRatePerDay() << endl;
        }
    }

    void SetRentedCars(const vector<Car> &cars)
    {
        RentedCars = cars;
    }

    void ReduceDue(float amount)
    {
        if (amount >= 0)
        {
            FineDue -= amount;
        }
    }
};


class Manager : public User
{
public:
    Manager(const string &Name, const string &UserID, const string &Password)
        : User(Name, UserID, Password) {}

    /*
    void AddCustomer(Customer newCustomer, CustomerQuerier &customerQuerier)
    {
        customerQuerier.AddCustomer(newCustomer);
    }

    void DeleteCustomer(const string &customerID, CustomerQuerier &customerQuerier)
    {
        customerQuerier.DeleteCustomer(customerID);
    }

    void AddEmployee(Employee newEmployee, EmployeeQuerier &employeeQuerier)
    {
        employeeQuerier.AddEmployee(newEmployee);
    }

    void DeleteEmployee(const string &employeeID, EmployeeQuerier &employeeQuerier)
    {
        employeeQuerier.DeleteEmployee(employeeID);
    }

    void AddManager(Manager newManager, ManagerQuerier &managerQuerier)
    {
        managerQuerier.AddManager(newManager);
    }

    void DeleteManager(const string &managerID, ManagerQuerier &managerQuerier)
    {
        managerQuerier.DeleteManager(managerID);
    }
    */
};


class CarQuerier
{
private:
    vector<Car> Cars;

public:
    CarQuerier()
    {
        ifstream file("../Database/CarDatabase.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string model;
                float condition, maxSpeed, kmRun, minScoreNeeded, ratePerKm, ratePerDay;
                int rentedStatus;
                string userID;
                int day, month, year;

                getline(ss, model, ',');
                ss >> condition;
                ss.ignore(); // Ignore the comma
                ss >> rentedStatus;
                ss.ignore(); // Ignore the comma
                getline(ss, userID, ',');
                ss >> day;
                ss.ignore(); // Ignore the comma
                ss >> month;
                ss.ignore(); // Ignore the comma
                ss >> year;
                ss.ignore(); // Ignore the comma
                ss >> maxSpeed;
                ss.ignore(); // Ignore the comma
                ss >> kmRun;
                ss.ignore(); // Ignore the comma
                ss >> minScoreNeeded;
                ss.ignore(); // Ignore the comma
                ss >> ratePerKm;
                ss.ignore(); // Ignore the comma
                ss >> ratePerDay;

                Date dueDate(day, month, year);
                Car car(model, condition, maxSpeed, kmRun, minScoreNeeded, ratePerKm, ratePerDay);
                car.SetAvailability(userID, dueDate, rentedStatus);
                Cars.push_back(car);
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/CarDatabase.txt" << endl;
        }
    }

    vector<Car> GetCars() const
    {
        return Cars;
    }
    void SetCars(const vector<Car> &cars)
    {
        this->Cars = cars;
        UpdateCarDatabase();
    }

    void Browse(float Score) const
    {
        cout << "Available Cars:\n";
        for (const auto &car : this->Cars)
        {
            if (car.GetRentedStatus() == 0 && (car.GetMinScoreNeeded() <= Score))
            {
                cout << "Model: " << car.GetModel() << ", Condition: " << car.GetCondition()
                     << ", Maximum Speed: " << car.GetMaximumSpeed() << ", Kilometers Run: " << car.GetKilometersRun()
                     << ", Rate per Km: " << car.GetRatePerKm() << ", Rate per Day: " << car.GetRatePerDay() << endl;
            }
        }
    }

    vector<Car> ViewRentedCars(const string &userID) const
    {
        vector<Car> rentedCars;
        for (const auto &car : Cars)
        {
            if (car.GetUserID() == userID && car.GetRentedStatus() == 1)
            {
                rentedCars.push_back(car);
            }
        }
        return rentedCars;
    }

    // Function to add a new car
    void AddCar(const Car &newCar)
    {
        Cars.push_back(newCar);
        UpdateCarDatabase();
    }

    // Function to update an existing car
    void UpdateCar(const Car &updatedCar)
    {
        const string &model = updatedCar.GetModel();

        // Find the car with the same model and update its information
        for (auto &car : Cars)
        {
            if (car.GetModel() == model)
            {
                car = updatedCar;
                UpdateCarDatabase();
                return;
            }
        }

        // If the car with the specified model is not found, add it as a new car
        AddCar(updatedCar);
    }

    void UpdateCar1(const Car &updatedCar)
    {
        const string &model = updatedCar.GetModel();

        // Find the car with the specified model and update its information
        for (auto &car : Cars)
        {
            if (car.GetModel() == model)
            {
                car = updatedCar;
                // Call a function to update the car database file (optional)
                UpdateCarDatabase();
                return;
            }
        }

        cout << "Car with model " << model << " not found.\n";
    }

    // Function to delete an existing car
    void DeleteCar(const string &model)
    {
        Cars.erase(remove_if(Cars.begin(), Cars.end(),
                             [model](const Car &car)
                             {
                                 return car.GetModel() == model;
                             }),
                   Cars.end());
        UpdateCarDatabase();
    }

    void UpdateCarDatabase()
    {
        ofstream file("../Database/CarDatabase.txt");
        if (file.is_open())
        {
            for (const auto &car : Cars)
            {
                file << car.GetModel() << "," << car.GetCondition() << "," << car.GetRentedStatus() << ","
                     << car.GetUserID() << "," << car.GetDueDate().GetDay() << "," << car.GetDueDate().GetMonth() << ","
                     << car.GetDueDate().GetYear() << "," << car.GetMaximumSpeed() << "," << car.GetKilometersRun() << ","
                     << car.GetMinScoreNeeded() << "," << car.GetRatePerKm() << "," << car.GetRatePerDay() << endl;
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/CarDatabase.txt" << endl;
        }
    }
};


class CustomerQuerier
{
private:
    vector<Customer> Customers;

public:
    CustomerQuerier()
    {
        ifstream file("../Database/CustomerDatabase.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string name, userID, password;
                float CustomerRecord, fineDue;
                getline(ss, name, ',');
                getline(ss, userID, ',');
                getline(ss, password, ',');
                ss >> CustomerRecord;
                ss.ignore(); // Ignore the comma
                ss >> fineDue;
                ss.ignore(); // Ignore the comma

                Customer customer(name, userID, password, CustomerRecord, fineDue);
                Customers.push_back(customer);
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/CustomerDatabase.txt" << endl;
        }
    }

    vector<Customer> GetCustomers() const
    {
        return Customers;
    }

    int customerLogin(const string &userID, const string &password)
    {
        vector<Customer> customers = GetCustomers();
        string password1 = password;
        string userID1 = userID;
        while (true)
        {
            for (const auto &customer : customers)
            {
                if (customer.GetUserID() == userID1)
                {
                    if (customer.GetPassword() == password1)
                    {
                        // Successful login
                        return 2;
                    }
                    else
                    {
                        // Password incorrect
                        cout << "\nIncorrect Password. Please try again.\n";
                        cout << "\nIf You want to exit, put UserID1 as -1. \n";
                        cout << "\nEnter UserId: ";
                        getline(cin, userID1);

                        if (userID1 == "-1")
                        {
                            break; // exit loop
                        }

                        cout << "Enter Password: ";
                        getline(cin, password1);
                        break; // To re-check password
                    }
                }
            }
            return 0;
        }
    }

    Customer GetCustomerById(const string &customerId)
    {
        for (const auto &customer : Customers)
        {
            if (customer.GetUserID() == customerId)
            {
                return customer;
            }
        }

        // If the customer with the specified ID is not found, return a default-constructed customer
        return Customer("", "", "");
    }

    void AddCustomer(const Customer &newCustomer)
    {
        Customers.push_back(newCustomer);
        // Call a function to update the customer database file (optional)
        UpdateDatabase();
    }

    // Add a method to delete an existing customer
    void DeleteCustomer(const string &customerID)
    {
        Customers.erase(remove_if(Customers.begin(), Customers.end(),
                                  [customerID](const Customer &customer)
                                  {
                                      return customer.GetUserID() == customerID;
                                  }),
                        Customers.end());
        // Call a function to update the customer database file (optional)
        UpdateDatabase();
    }

    // Add a method to update the customer database file
    void UpdateDatabase()
    {
        // Code to write the vector to the customer database file
        ofstream file("../Database/CustomerDatabase.txt");
        if (file.is_open())
        {
            for (const auto &customer : Customers)
            {
                file << customer.GetName() << "," << customer.GetUserID() << ","
                     << customer.GetPassword() << "," << customer.GetCustomerRecord() << ","
                     << customer.GetFineDue() << "\n";
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/CustomerDatabase.txt" << endl;
        }
    }

    bool isUserIDUnique(const std::string &userID) const
    {
        for (const auto &customer : Customers)
        {
            if (customer.GetUserID() == userID)
            {
                return false; // UserID already exists
            }
        }
        return true; // UserID is unique
    }

    void UpdateCustomer(const Customer &updatedCustomer)
    {
        const std::string &userID = updatedCustomer.GetUserID();

        // Delete existing customer with the same userID
        DeleteCustomer(userID);

        // Add the updated customer
        AddCustomer(updatedCustomer);
    }

    void ReduceDue(const string &userID, float amount)
    {
        for (auto &customer : Customers)
        {
            if (customer.GetUserID() == userID)
            {
                customer.ReduceDue(amount);
                UpdateDatabase(); // Update the customer in the vector
                return;
            }
        }

        cout << "Customer with UserID " << userID << " not found.\n";
    }

    void ImposeDue(const string &userID, float amount)
    {
        for (auto &customer : Customers)
        {
            if (customer.GetUserID() == userID)
            {
                customer.ImposeDue(amount);
                UpdateDatabase(); // Update the customer in the vector
                return;
            }
        }

        cout << "Customer with UserID " << userID << " not found.\n";
    }

    // Function to clear due for a specific customer
    void ClearDue(const string &userID)
    {
        for (auto &customer : Customers)
        {
            if (customer.GetUserID() == userID)
            {
                customer.ClearDue();
                UpdateDatabase(); // Update the customer in the vector
                cout << "Due cleared successfully for customer " << userID << ".\n";
                return;
            }
        }

        cout << "Customer with UserID " << userID << " not found.\n";
    }

    Car RentCar(const string &userID, const string &carModel, const Date &dueDate, CarQuerier &carQuerier)
    {
        vector<Car> cars = carQuerier.GetCars();

        for (auto &car : cars)
        {
            if (car.GetModel() == carModel && car.GetRentedStatus() == 0)
            {
                car.SetAvailability(userID, dueDate);
                carQuerier.SetCars(cars);
                return car;
            }
        }

        // Return a default-constructed car if the requested car is not found or not available
        return Car("", 0.0f);
    }
};

class EmployeeQuerier
{
private:
    vector<Employee> Employees;

public:
    EmployeeQuerier()
    {
        ifstream file("../Database/EmployeeDatabase.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string name, userID, password;
                float employeeRecord, fineDue;
                getline(ss, name, ',');
                getline(ss, userID, ',');
                getline(ss, password, ',');
                ss >> employeeRecord;
                ss.ignore(); // Ignore the comma
                ss >> fineDue;
                ss.ignore(); // Ignore the comma

                Employee employee(name, userID, password, employeeRecord, fineDue);
                Employees.push_back(employee);
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/EmployeeDatabase.txt" << endl;
        }
    }

    vector<Employee> GetEmployees() const
    {
        return Employees;
    }

    int employeeLogin(const string &userID, const string &password)
    {
        vector<Employee> employees = GetEmployees();
        string password1 = password;
        string userID1 = userID;
        while (true)
        {
            for (const auto &employee : employees)
            {
                if (employee.GetUserID() == userID1)
                {
                    if (employee.GetPassword() == password1)
                    {
                        // Successful login
                        return 2;
                    }
                    else
                    {
                        // Password incorrect
                        cout << "\nIncorrect Password. Please try again.\n";
                        cout << "\nIf You want to exit, put UserID1 as -1. \n";
                        cout << "\nEnter UserId: ";
                        getline(cin, userID1);

                        if (userID1 == "-1")
                        {
                            break; // exit loop
                        }

                        cout << "Enter Password: ";
                        getline(cin, password1);
                        break; // To re-check password
                    }
                }
            }

            return 0;
        }
    }

    Employee GetEmployeeById(const string &employeeId)
    {
        for (const auto &employee : Employees)
        {
            if (employee.GetUserID() == employeeId)
            {
                return employee;
            }
        }

        // If the employee with the specified ID is not found, return a default-constructed employee
        return Employee("", "", "");
    }

    bool isUserIDUnique(const std::string &userID) const
    {
        for (const auto &employee : Employees)
        {
            if (employee.GetUserID() == userID)
            {
                return false; // UserID is not unique
            }
        }
        return true; // UserID is unique
    }

    void AddEmployee(const Employee &employee)
    {
        Employees.push_back(employee);
        UpdateEmployeeDatabase();
    }

    void DeleteEmployee(const std::string &employeeID)
    {
        Employees.erase(std::remove_if(Employees.begin(), Employees.end(),
                                       [employeeID](const Employee &employee)
                                       { return employee.GetUserID() == employeeID; }),
                        Employees.end());
        UpdateEmployeeDatabase();
    }

    void UpdateEmployeeDatabase()
    {
        ofstream file("../Database/EmployeeDatabase.txt");
        if (file.is_open())
        {
            for (const auto &employee : Employees)
            {
                file << employee.GetName() << "," << employee.GetUserID() << "," << employee.GetPassword() << ","
                     << employee.GetEmployeeRecord() << "," << employee.GetFineDue() << endl;
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/EmployeeDatabase.txt" << endl;
        }
    }

    void UpdateEmployee(const Employee &updatedEmployee)
    {
        DeleteEmployee(updatedEmployee.GetUserID());
        AddEmployee(updatedEmployee);
    }

    void ReduceDue(const string &userID, float amount)
    {
        for (auto &employee : Employees)
        {
            if (employee.GetUserID() == userID)
            {
                employee.ReduceDue(amount);
                UpdateEmployeeDatabase();
                return;
            }
        }

        cout << "Employee with UserID " << userID << " not found.\n";
    }

    void ImposeDue(const string &userID, float amount)
    {
        for (auto &employee : Employees)
        {
            if (employee.GetUserID() == userID)
            {
                employee.ImposeDue(amount);
                UpdateEmployeeDatabase(); // Update the employee in the vector
                return;
            }
        }

        cout << "Employee with UserID " << userID << " not found.\n";
    }

    // Function to clear due for a specific employee
    void ClearDue(const string &userID)
    {
        for (auto &employee : Employees)
        {
            if (employee.GetUserID() == userID)
            {
                employee.ClearDue();
                UpdateEmployeeDatabase(); // Update the employee in the vector
                cout << "Due cleared successfully for employee " << userID << ".\n";
                return;
            }
        }

        cout << "Employee with UserID " << userID << " not found.\n";
    }

    Car RentCarForCustomer(const string &userID, const string &carModel, const Date &dueDate, CarQuerier carQuerier)
    {
        vector<Car> cars = carQuerier.GetCars();

        for (auto &car : cars)
        {
            if (car.GetModel() == carModel && car.GetRentedStatus() == 0)
            {
                car.SetAvailability(userID, dueDate);
                return car;
            }
        }

        // Return a default-constructed car if the requested car is not found or not available
        return Car("", 0.0f);
    }
};


class ManagerQuerier
{
private:
    vector<Manager> Managers;

public:
    ManagerQuerier()
    {
        ifstream file("../Database/ManagerDatabase.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string name, userID, password;
                getline(ss, name, ',');
                getline(ss, userID, ',');
                getline(ss, password, ',');

                Manager manager(name, userID, password);
                Managers.push_back(manager);
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/ManagerDatabase.txt" << endl;
        }
    }

    vector<Manager> GetManagers() const
    {
        return Managers;
    }

    int managerLogin(const string &userID, const string &password)
    {
        vector<Manager> managers = GetManagers();
        for (const auto &manager : managers)
        {
            if (manager.GetUserID() == userID)
            {
                if (manager.GetPassword() == password)
                {
                    // Successful login
                    return 2;
                }
                else
                {
                    return 1;
                }
            }
        }
        return 0;
    }

    Manager GetManagerById(const string &managerId)
    {
        for (const auto &manager : Managers)
        {
            if (manager.GetUserID() == managerId)
            {
                return manager;
            }
        }

        // If the manager with the specified ID is not found, return a default-constructed manager
        return Manager("", "", "");
    }

    bool isUserIDUnique(const std::string &userID) const
    {
        for (const auto &manager : Managers)
        {
            if (manager.GetUserID() == userID)
            {
                return false; // UserID is not unique
            }
        }
        return true; // UserID is unique
    }

    void AddManager(const Manager &manager)
    {
        Managers.push_back(manager);
        UpdateManagerDatabase();
    }

    void DeleteManager(const std::string &managerID)
    {
        Managers.erase(std::remove_if(Managers.begin(), Managers.end(),
                                      [managerID](const Manager &manager)
                                      { return manager.GetUserID() == managerID; }),
                       Managers.end());
        UpdateManagerDatabase();
    }

    void UpdateManagerDatabase()
    {
        ofstream file("../Database/ManagerDatabase.txt");
        if (file.is_open())
        {
            for (const auto &manager : Managers)
            {
                file << manager.GetName() << "," << manager.GetUserID() << "," << manager.GetPassword() << endl;
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: ../Database/ManagerDatabase.txt" << endl;
        }
    }

    void UpdateManager(const Manager &updatedManager)
    {
        DeleteManager(updatedManager.GetUserID());
        AddManager(updatedManager);
    }
};


void authenticatePayment(const string &carModel, CarQuerier &carQuerier, CustomerQuerier &customerQuerier, EmployeeQuerier &employeeQuerier)
{
    // Get the list of cars from the car database
    vector<Car> cars = carQuerier.GetCars();
    
    // Use the actual current date
    Date currentDate(1, 2, 2024);

    // Iterate over the list of cars
    for (auto &car : cars)
    {
        // Check if the car model matches and the car is rented
        if (car.GetModel() == carModel && car.GetRentedStatus() == 1)
        {
            // Get user ID, due date, and previous kilometers run
            string userID = car.GetUserID();
            Date dueDate = car.GetDueDate();
            float kmRunEarlier = car.GetKilometersRun();

            // Take input for the current kilometers run
            float currentKmRun;
            cout << "Enter current kilometers run for car " << carModel << ": ";
            cin >> currentKmRun;

            // Calculate the payable upfront amount
            float payableUpfront = (currentKmRun - kmRunEarlier) * car.GetRatePerKm() +
                                   car.GetRatePerDay() * currentDate.DifferenceInDays(dueDate);

            // Impose the payable upfront as due on the user
            if (userID.find("CUST") == 0)
            {
                customerQuerier.ImposeDue(userID, payableUpfront);

                // Remove the car from the customer's list of rented cars
                Customer customer = customerQuerier.GetCustomerById(userID);
                vector<Car> rentedCars = customer.GetRentedCars();
                rentedCars.erase(remove_if(rentedCars.begin(), rentedCars.end(),
                                           [carModel](const Car &rentedCar)
                                           { return rentedCar.GetModel() == carModel; }),
                                 rentedCars.end());
                customer.SetRentedCars(rentedCars);
                customerQuerier.UpdateCustomer(customer);
            }
            else if (userID.find("EMPL") == 0)
            {
                employeeQuerier.ImposeDue(userID, payableUpfront);

                // Remove the car from the employee's list of rented cars
                Employee employee = employeeQuerier.GetEmployeeById(userID);
                vector<Car> rentedCars = employee.GetRentedCars();
                rentedCars.erase(remove_if(rentedCars.begin(), rentedCars.end(),
                                           [carModel](const Car &rentedCar)
                                           { return rentedCar.GetModel() == carModel; }),
                                 rentedCars.end());
                employee.SetRentedCars(rentedCars);
                employeeQuerier.UpdateEmployee(employee);
            }

            // Update the car's status and database
            car.SetAvailability("", Date(1, 1, 2000), 0);
            car.SetKmRun(currentKmRun);
            carQuerier.UpdateCarDatabase();
            
            // Print a success message
            cout << "Payment authenticated successfully for car " << carModel << ".\n";
            return;
        }
    }

    // Print a message if the car is not found or not rented
    cout << "Car with model " << carModel << " not found or not rented.\n";
}