#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <random>

using namespace std;


class savable {
public:
    virtual void saveToFile(const string& filename) const = 0;
    virtual void loadFromFile(const string& filename) = 0;
    virtual ~savable() = default;
};

class Utilities {
private:
    string bills;
    string stock;
    string stationary;

public:
    Utilities() = default;
    Utilities(string b, string s, string st) : bills(b), stock(s), stationary(st) {}

    string getBills() const { return bills; }
    string getStock() const { return stock; }
    string getStationary() const { return stationary; }

    void saveToFile(ofstream& outFile) const {
        outFile << bills << "," << stock << "," << stationary << endl;
    }
};

class Account {
protected:
    string name, dateOfBirth, address, phoneNumber, email, accountType, accountID;

public:
    Account() = default; // Added default constructor
    Account(const string& n, const string& dob, const string& addr, const string& phone, const string& mail, const string& type)
        : name(n), dateOfBirth(dob), address(addr), phoneNumber(phone), email(mail), accountType(type) {}

    void setAccountID(const string& id) { accountID = id; }
    string getAccountID() const { return accountID; }
    string getName() const { return name; }
    string getDateOfBirth() const { return dateOfBirth; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }
    string getAccountType() const { return accountType; }
};

class Student : public Account { // Inherit from Account
private:
    string className;
    vector<string> courses;
    double fees;

public:
    Student() = default;
    Student(const string& n, const string& dob, const string& addr, const string& phone, const string& mail, const string& type,
        const string& id, const string& cls, const vector<string>& crs, double f)
        : Account(n, dob, addr, phone, mail, type), className(cls), courses(crs), fees(f) {
        accountID = id;
    }
    string getStudentID() const { return accountID; }
    string getClassName() const { return className; }
    const vector<string>& getCourses() const { return courses; }
    double getFees() const { return fees; }
};

class Teacher : public Account {
private:
    string subject;
    string classesAssigned;
    string salary;

public:
    Teacher() = default;
    Teacher(const string& n, const string& dob, const string& addr, const string& phone, const string& mail, const string& type,
        const string& id, const string& sub, const string& classes, const string& sal)
        : Account(n, dob, addr, phone, mail, type), subject(sub), classesAssigned(classes), salary(sal) {
        accountID = id;
    }
    string getTeacherID() const { return accountID; }
    string getSubject() const { return subject; }
    string getClassesAssigned() const { return classesAssigned; }
    string getSalary() const { return salary; }
};

class Staff : public Account {
private:
    string staffID;
    string position;
    string department;

public:
    Staff() = default;
    Staff(const string& n, const string& dob, const string& addr, const string& phone, const string& mail, const string& type,
        const string& id, const string& pos, const string& dept)
        : Account(n, dob, addr, phone, mail, type), staffID(id), position(pos), department(dept) {}

    string getStaffID() const { return staffID; }
    string getPosition() const { return position; }
    string getDepartment() const { return department; }
};

class Canteen {
private:
    string openingHours;
    string closingHours;
    vector<pair<string, string>> menuItems;

public:
    Canteen() = default;
    Canteen(const vector<pair<string, string>>& items, const string& open, const string& close)
        : menuItems(items), openingHours(open), closingHours(close) {}

    const vector<pair<string, string>>& getMenuItems() const { return menuItems; }
    string getOpeningHours() const { return openingHours; }
    string getClosingHours() const { return closingHours; }
};

class Admin : public Account, public savable {
private:
    string username;
    string password;

public:
    Admin(const string& user = "", const string& pass = "") : username(user), password(pass) {}
    void setUsername(const string& user) { username = user; }
    void setPassword(const string& pass) { password = pass; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    void saveToFile(const string& filename) const override {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }
        outFile << username << endl;
        outFile << password << endl;
        outFile.close();
    }
    void loadFromFile(const string& filename) override {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error opening file for reading: " << filename << endl;
            return;
        }
        getline(inFile, username);
        getline(inFile, password);
        inFile.close();
    }
};

#endif // HEADER_H