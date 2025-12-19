#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

using namespace std;

struct Employee {
    int id;
    string name;
    double salary;
};

/* -------- Display Function -------- */

void displayEmployee(const Employee& emp) {
    cout << "ID: " << emp.id
         << " | Name: " << emp.name
         << " | Salary: " << emp.salary << endl;
}

/* -------- Functions -------- */

void showAllEmployees(const vector<Employee>& employees) {
    cout << "\n--- All Employees ---\n";
    for_each(employees.begin(), employees.end(), displayEmployee);
}

void sortBySalary(vector<Employee>& employees) {
    sort(employees.begin(), employees.end(),
        [](const Employee& e1, const Employee& e2) {
            return e1.salary > e2.salary;
        });

    cout << "\nEmployees sorted by Salary (High to Low):\n";
    showAllEmployees(employees);
}

void showHighEarners(const vector<Employee>& employees) {
    vector<Employee> highEarners;

    copy_if(employees.begin(), employees.end(),
        back_inserter(highEarners),
        [](const Employee& e) {
            return e.salary > 60000;
        });

    cout << "\n--- High Earners (Salary > 60000) ---\n";
    for_each(highEarners.begin(), highEarners.end(), displayEmployee);
}

void showSalaryStats(const vector<Employee>& employees) {
    double totalSalary = accumulate(
        employees.begin(), employees.end(), 0.0,
        [](double sum, const Employee& e) {
            return sum + e.salary;
        });

    double averageSalary = totalSalary / employees.size();

    cout << "\nTotal Salary: " << totalSalary << endl;
    cout << "Average Salary: " << averageSalary << endl;
}

void showHighestPaid(const vector<Employee>& employees) {
    auto highestPaid = max_element(
        employees.begin(), employees.end(),
        [](const Employee& e1, const Employee& e2) {
            return e1.salary < e2.salary;
        });

    cout << "\n--- Highest Paid Employee ---\n";
    displayEmployee(*highestPaid);
}

void addEmployee(vector<Employee>& employees) {
    Employee e;
    cout << "\nEnter Employee ID: ";
    cin >> e.id;
    cout << "Enter Name: ";
    cin >> e.name;
    cout << "Enter Salary: ";
    cin >> e.salary;

    employees.push_back(e);
    cout << "Employee added successfully!\n";
}

/* -------- Main -------- */

int main() {
    vector<Employee> employees = {
        {101,"Hitesh",100000},
        {102,"Rahul",70000},
        {103,"Aruj",60000},
        {104,"Satyam",180000},
        {105,"Aman",50000}
    };

    int choice;
    do {
        cout << "\n==============================\n";
        cout << " Employee Management System\n";
        cout << "==============================\n";
        cout << "1. View All Employees\n";
        cout << "2. Sort Employees by Salary\n";
        cout << "3. View High Earners\n";
        cout << "4. View Salary Statistics\n";
        cout << "5. View Highest Paid Employee\n";
        cout << "6. Add New Employee\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: showAllEmployees(employees); break;
            case 2: sortBySalary(employees); break;
            case 3: showHighEarners(employees); break;
            case 4: showSalaryStats(employees); break;
            case 5: showHighestPaid(employees); break;
            case 6: addEmployee(employees); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
