# CS253_CPP_Scripting_Assignment
The Submission repository for CS253 CPP Scripting Assignment.

# Instructions for Running the code
This is a very simple CPP project. To run this project:
  1. Clone this Repository onto your local machine.
  2. Go to Main.cpp
  3. Run the code in any cpp compiler.

# Fundamental Assumptions taken
There are some fundamentals assumptions taken for the user to follow while operating/handling this Software. These are:
  1. All the UserID's is of the following format, "CUSTXXX" for Customers, "EMPLXXX" for Employees, "MNGRXXX" for Managers. The rest three digits are numbers.
  2. Duplicate entries are not allowed, neither are UserIDs that do not follow this format.Upon Failure, the user is asked to again give the inputs.
  3. The code assumes that the database files for customers, employees, managers, and cars are located at specific paths ("../Database/"). If these paths or files are not present, the program fails to initialize.
  4. When marking a car as available or unavailable, a default date (January 1, 2000) is used. This might not be suitable for all scenarios, and the assumption is that this date is a placeholder.
  5. There is inherent assumption that any payment or transfer of funds is handled separately by another technology. This is only a Car Rental Management System.

# Interaction with the software
You are required to interact with the command line using the provided options. The software offers functionalities for Customer, Employee, Manager, and Car management. To navigate through the menu, enter the corresponding two-digit / one-digit option. Key functionalities include adding, updating, and deleting records for customers, employees, managers, and cars. Additionally, there are options for handling due amounts for customers and employees.

# Login
For specific operations, login is required. Managers should input their UserID and password. If the login is successful, a menu with manager-specific options will be displayed. These options cover various administrative tasks such as managing customers, employees, managers, and cars.

# Customer and Employee Operations
Customers and Employees must also login. For customer and employee operations, user information is collected, including name, UserID, and password. Ensure the entered UserID follows the specified format to avoid issues.

# Car Operations
Car-related operations involve entering details such as model, condition, maximum speed, kilometers run, minimum score needed, rate per kilometer, and rate per day.

# Due Operations
There are options to impose, clear, and reduce due amounts for both customers and employees.

Follow the command line instructions and input the relevant data as prompted to interact effectively with the software. Ensure that the provided assumptions and formatting guidelines are followed for a seamless experience.
