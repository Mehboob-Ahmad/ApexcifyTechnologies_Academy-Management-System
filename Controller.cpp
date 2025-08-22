#include "Controller.h"
#include "Database.h"
#include "View.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ctime>
#include <cstdlib>
using namespace std;

void Controller::loadInitialData() {
    teacherDb.loadFromFile("teachers.txt");
    studentDb.loadFromFile("students.txt");
    staffDb.loadFromFile("staff.txt");
    canteenDb.loadFromFile("canteen.txt");
}

void Controller::adminLogin() {
    string name, password;
    cout << "==============================================" << endl;
    cout << "               ADMIN LOGIN" << endl;
    cout << "==============================================" << endl;
    cout << "Enter admin name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter password: ";
    getline(cin, password);

    if (name == "admin" && password == "admin123") {
        cout << "Login successful!" << endl;
        adminMenu();
    } else {
        cout << "Invalid admin credentials!" << endl;
    }
}

void Controller::teacherLogin() {
    string id, password;
    cout << "==============================================" << endl;
    cout << "              TEACHER LOGIN" << endl;
    cout << "==============================================" << endl;
    cout << "Enter teacher ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    if (teacherDb.verifyLogin(id, password)) {
        cout << "Login successful!" << endl;
        teacherMenu(id);
    } else {
        cout << "Invalid teacher credentials!" << endl;
    }
}

void Controller::studentLogin() {
    string id, password;
    cout << "==============================================" << endl;
    cout << "              STUDENT LOGIN" << endl;
    cout << "==============================================" << endl;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    if (studentDb.verifyLogin(id, password)) {
        cout << "Login successful!" << endl;
        studentMenu(id);
    } else {
        cout << "Invalid student credentials!" << endl;
    }
}

void Controller::staffLogin() {
    string id, password;
    cout << "==============================================" << endl;
    cout << "               STAFF LOGIN" << endl;
    cout << "==============================================" << endl;
    cout << "Enter staff ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    if (staffDb.verifyLogin(id, password)) {
        cout << "Login successful!" << endl;
        staffMenu(id);
    } else {
        cout << "Invalid staff credentials!" << endl;
    }
}

void Controller::adminMenu() {
    int choice;
    do {
        view.displayAdminMenu();
        cin >> choice;
        cout << "==============================================" << endl;

        switch (choice) {
            case 1: checkBills(); break;
            case 2: addTeacher(); break;
            case 3: removeTeacher(); break;
            case 4: addStaff(); break;
            case 5: removeStaff(); break;
            case 6: addStudent(); break;
            case 7: removeStudent(); break;
            case 8: paySalary(); break;
            case 9: issueStudentVoucher(); break;
            case 10: addCanteenItems(); break;
            case 11: orderCanteenItems(); break;
            case 12: removeCanteenItems(); break;
            case 13: checkApplications(); break;
            case 14: checkResults(); break;
            case 15: makeAnnouncements(); break;
            case 16: freezeAccount(); break;
            case 17: unfreezeAccount(); break;
            case 0: cout << "Exiting admin menu." << endl; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}

void Controller::teacherMenu(const string &teacherID) {
    int choice;
    do {
        view.displayTeacherMenu();
        cin >> choice;
        cout << "==============================================" << endl;

        switch (choice) {
            case 1: applyForApplicationTeacher(teacherID); break;
            case 2: checkScheduleTeacher(teacherID); break;
            case 3: checkStudentResultsTeacher(teacherID); break;
            case 4: makeAnnouncementTeacher(teacherID); break;
            case 5: checkMyResultTeacher(teacherID); break;
            case 6: takeAttendanceTeacher(teacherID); break;
            case 0: cout << "Logging out." << endl; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}

void Controller::studentMenu(const string &studentID) {
    int choice;
    do {
        view.displayStudentMenu();
        cin >> choice;
        cout << "==============================================" << endl;

        switch (choice) {
            case 1: applyForApplicationStudent(studentID); break;
            case 2: checkMyResultStudent(studentID); break;
            case 3: checkMyCoursesStudent(studentID); break;
            case 4: checkMyTeachersStudent(studentID); break;
            case 5: checkMyAttendanceStudent(studentID); break;
            case 6: checkFeeVoucherStudent(studentID); break;
            case 0: cout << "Logging out." << endl; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}

void Controller::staffMenu(const string &staffID) {
    int choice;
    bool isCanteenStaff = staffDb.isCanteenStaff(staffID);
    do {
        view.displayStaffMenu(isCanteenStaff);
        cin >> choice;
        cout << "==============================================" << endl;
        switch (choice) {
            case 1: applyForApplicationStaff(staffID); break;
            case 2: if (isCanteenStaff) orderCanteenItemsStaff(); else cout << "Invalid choice!" << endl; break;
            case 3: if (isCanteenStaff) updateCanteenPricesStaff(); else cout << "Invalid choice!" << endl; break;
            case 0: cout << "Logging out." << endl; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}

// Function implementations moved from main.cpp
void Controller::addTeacher() {
    string name, password, id, className, timing, subjects;
    double salary;
    view.getTeacherDetails(name, password, className, timing, subjects, salary);
    id = teacherDb.generateID('T'); // Assuming 'T' for Teacher
    teacherDb.saveTeacherData(id, password, name, className, timing, subjects, salary);
    cout << "Teacher added successfully! ID: " << id << endl;
}

void Controller::removeTeacher() {
    string id;
    view.getTeacherID(id);
    if (teacherDb.removeTeacher(id)) {
        cout << "Teacher with ID " << id << " removed successfully." << endl;
    } else {
        cout << "Teacher with ID " << id << " not found." << endl;
    }
}

void Controller::addStudent() {
    string name, password, id, className, courses;
    double fee;
    view.getStudentDetails(name, password, className, courses, fee);
    id = studentDb.generateID('S'); // Assuming 'S' for Student
    studentDb.saveStudentData(id, password, name, className, courses, fee);
    cout << "Student added successfully! ID: " << id << endl;
}

void Controller::removeStudent() {
    string id;
    view.getStudentID(id);
    if (studentDb.removeStudent(id)) {
        cout << "Student with ID " << id << " removed successfully." << endl;
    } else {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

void Controller::addStaff() {
    string name, password, id, role, department;
    double salary;
    view.getStaffDetails(name, password, role, department, salary);
    id = staffDb.generateID('F'); // Assuming 'F' for Staff
    staffDb.saveStaffData(id, password, name, role, department, salary);
    cout << "Staff member added successfully! ID: " << id << endl;
}

void Controller::removeStaff() {
    string id;
    view.getStaffID(id);
    if (staffDb.removeStaff(id)) {
        cout << "Staff member with ID " << id << " removed successfully." << endl;
    } else {
        cout << "Staff member with ID " << id << " not found." << endl;
    }
}

void Controller::checkBills() {
    cout << "Checking bills... (Not implemented in this version)" << endl;
}

void Controller::paySalary() {
    cout << "Paying salaries... (Not implemented in this version)" << endl;
}

void Controller::issueStudentVoucher() {
    cout << "Issuing student vouchers... (Not implemented in this version)" << endl;
}

void Controller::addCanteenItems() {
    int id;
    string name;
    double price;
    view.getCanteenItemDetails(id, name, price);
    canteenDb.addCanteenItem(id, name, price);
    cout << "Canteen item added successfully." << endl;
}

void Controller::orderCanteenItems() {
    cout << "Ordering canteen items... (Not implemented in this version)" << endl;
}

void Controller::removeCanteenItems() {
    int id;
    view.getCanteenItemID(id);
    canteenDb.removeCanteenItem(id);
    cout << "Canteen item removed successfully." << endl;
}

void Controller::checkApplications() {
    cout << "Checking applications... (Not implemented in this version)" << endl;
}

void Controller::checkResults() {
    cout << "Checking results... (Not implemented in this version)" << endl;
}

void Controller::makeAnnouncements() {
    cout << "Making announcements... (Not implemented in this version)" << endl;
}

void Controller::freezeAccount() {
    cout << "Freezing account... (Not implemented in this version)" << endl;
}

void Controller::unfreezeAccount() {
    cout << "Unfreezing account... (Not implemented in this version)" << endl;
}

void Controller::applyForApplicationTeacher(const string &teacherID) {
    cout << "Applying for application for teacher " << teacherID << "... (Not implemented in this version)" << endl;
}

void Controller::checkScheduleTeacher(const string &teacherID) {
    cout << "Checking schedule for teacher " << teacherID << "... (Not implemented in this version)" << endl;
}

void Controller::checkStudentResultsTeacher(const string &teacherID) {
    cout << "Checking student results for teacher " << teacherID << "... (Not implemented in this version)" << endl;
}

void Controller::makeAnnouncementTeacher(const string &teacherID) {
    cout << "Making announcement as teacher " << teacherID << "... (Not implemented in this version)" << endl;
}

void Controller::checkMyResultTeacher(const string &teacherID) {
    cout << "Checking my result as teacher " << teacherID << "... (Not implemented in this version)" << endl;
}

void Controller::takeAttendanceTeacher(const string &teacherID) {
    cout << "Taking attendance as teacher " << teacherID << "... (Not implemented in this version)" << endl;
}

void Controller::applyForApplicationStudent(const string &studentID) {
    cout << "Applying for application for student " << studentID << "... (Not implemented in this version)" << endl;
}

void Controller::checkMyResultStudent(const string &studentID) {
    cout << "Checking my result as student " << studentID << "... (Not implemented in this version)" << endl;
}

void Controller::checkMyCoursesStudent(const string &studentID) {
    cout << "Checking my courses as student " << studentID << "... (Not implemented in this version)" << endl;
}

void Controller::checkMyTeachersStudent(const string &studentID) {
    cout << "Checking my teachers as student " << studentID << "... (Not implemented in this version)" << endl;
}

void Controller::checkMyAttendanceStudent(const string &studentID) {
    cout << "Checking my attendance as student " << studentID << "... (Not implemented in this version)" << endl;
}

void Controller::checkFeeVoucherStudent(const string &studentID) {
    cout << "Checking fee voucher as student " << studentID << "... (Not implemented in this version)" << endl;
}

void Controller::applyForApplicationStaff(const string &staffID) {
    cout << "Applying for application for staff " << staffID << "... (Not implemented in this version)" << endl;
}

void Controller::orderCanteenItemsStaff() {
    cout << "Ordering canteen items as staff... (Not implemented in this version)" << endl;
}

void Controller::updateCanteenPricesStaff() {
    cout << "Updating canteen prices as staff... (Not implemented in this version)" << endl;
}