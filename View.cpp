#include "View.h"
#include "Header.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <vector>

using namespace std;

void View::displayAdminMenu() {
    cout << "==============================================" << endl;
    cout << "               ADMIN MENU" << endl;
    cout << "==============================================" << endl;
    cout << "1. Check bills" << endl;
    cout << "2. Add Teacher" << endl;
    cout << "3. Remove Teacher" << endl;
    cout << "4. Add Staff member" << endl;
    cout << "5. Remove Staff member" << endl;
    cout << "6. Add Student" << endl;
    cout << "7. Remove Student" << endl;
    cout << "8. Pay Salary" << endl;
    cout << "9. Issue Student Voucher" << endl;
    cout << "10. Add Canteen Items" << endl;
    cout << "11. Order Canteen Items" << endl;
    cout << "12. Remove Canteen items" << endl;
    cout << "13. Check for applications" << endl;
    cout << "14. Check for results" << endl;
    cout << "15. Make Announcements" << endl;
    cout << "16. Freeze account" << endl;
    cout << "17. Unfreeze account" << endl;
    cout << "0. Exit Admin menu" << endl;
    cout << "Enter your choice: ";
}

void View::displayTeacherMenu() {
    cout << "==============================================" << endl;
    cout << "              TEACHER MENU" << endl;
    cout << "==============================================" << endl;
    cout << "1. Apply for application" << endl;
    cout << "2. Check Schedule" << endl;
    cout << "3. Results of Students" << endl;
    cout << "4. Make announcement" << endl;
    cout << "5. My result" << endl;
    cout << "6. Take attendance" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

void View::displayStudentMenu() {
    cout << "==============================================" << endl;
    cout << "              STUDENT MENU" << endl;
    cout << "==============================================" << endl;
    cout << "1. Apply for application" << endl;
    cout << "2. My result" << endl;
    cout << "3. My courses" << endl;
    cout << "4. My teachers" << endl;
    cout << "5. My attendance" << endl;
    cout << "6. Fee Voucher" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

void View::displayStaffMenu(bool isCanteenStaff) {
    cout << "==============================================" << endl;
    cout << "               STAFF MENU" << endl;
    cout << "==============================================" << endl;
    cout << "1. Apply for application" << endl;
    if (isCanteenStaff) {
        cout << "2. Order Canteen items" << endl;
        cout << "3. Update prices for canteen items" << endl;
    }
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

void View::getTeacherDetails(string &name, string &password, string &className, string &timing, string &subjects, double &salary) {
    cout << "Enter teacher name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Set password: ";
    getline(cin, password);
    cout << "Enter class name to assign: ";
    getline(cin, className);
    cout << "Enter class timing (e.g., 9:00 AM - 11:00 AM): ";
    getline(cin, timing);
    cout << "Enter subjects: ";
    getline(cin, subjects);
    cout << "Enter salary: $";
    cin >> salary;
}

void View::getTeacherID(string& id) {
    cout << "Enter teacher ID to remove: ";
    cin >> id;
}

void View::getStudentDetails(string &name, string &password, string &className, string &courses, double &fee) {
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Set password: ";
    getline(cin, password);
    cout << "Enter class name: ";
    getline(cin, className);
    cout << "Enter courses: ";
    getline(cin, courses);
    cout << "Enter fee: $";
    cin >> fee;
}

void View::getStudentID(string& id) {
    cout << "Enter student ID to remove: ";
    cin >> id;
}

void View::getStaffDetails(string &name, string &password, string &role, string &department, double &salary) {
    cout << "Enter staff name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Set password: ";
    getline(cin, password);
    cout << "Enter role: ";
    getline(cin, role);
    cout << "Enter department: ";
    getline(cin, department);
    cout << "Enter salary: $";
    cin >> salary;
}

void View::getStaffID(string& id) {
    cout << "Enter staff ID to remove: ";
    cin >> id;
}

void View::getCanteenItemDetails(int &id, string &name, double &price) {
    cout << "Enter item ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter item name: ";
    getline(cin, name);
    cout << "Enter item price: $";
    cin >> price;
}

void View::getCanteenItemID(int& id) {
    cout << "Enter item ID to remove: ";
    cin >> id;
}