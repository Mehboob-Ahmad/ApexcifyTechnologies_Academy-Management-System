#include "Database.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Teacherdatabase implementations
void Teacherdatabase::saveTeacherData(const string &id, const string &password, const string &name,
                                      const string &className, const string &timing, const string &subjects, double salary) {
    ofstream file("teachers.txt", ios::app);
    file << id << " " << password << " " << name << " " << className << " "
         << timing << " " << subjects << " " << salary << endl;
    file.close();
    teachers[id] = password;
}

bool Teacherdatabase::verifyLogin(const string &id, const string &password) {
    if (teachers.find(id) != teachers.end() && teachers[id] == password) {
        return true;
    }
    return false;
}

string Teacherdatabase::generateID(char type) {
    int num = 100000 + rand() % 900000;
    return type + to_string(num);
}

bool Teacherdatabase::removeTeacher(const string& id) {
    if (teachers.erase(id) > 0) {
        ofstream outFile("teachers.txt");
        for (const auto& entry : teachers) {
            outFile << entry.first << " " << entry.second << endl;
        }
        return true;
    }
    return false;
}

void Teacherdatabase::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    string id, password;
    while (inFile >> id >> password) {
        teachers[id] = password;
        string dummy;
        getline(inFile, dummy);
    }
}

// Studentdatabase implementations
void Studentdatabase::saveStudentData(const string &id, const string &password, const string &name,
                                      const string &className, const string &courses, double fee) {
    ofstream file("students.txt", ios::app);
    file << id << " " << password << " " << name << " " << className << " "
         << courses << " " << fee << endl;
    file.close();
    students[id] = password;
}

bool Studentdatabase::verifyLogin(const string &id, const string &password) {
    if (students.find(id) != students.end() && students[id] == password) {
        return true;
    }
    return false;
}

string Studentdatabase::generateID(char type) {
    int num = 100000 + rand() % 900000;
    return type + to_string(num);
}

bool Studentdatabase::removeStudent(const string& id) {
    if (students.erase(id) > 0) {
        ofstream outFile("students.txt");
        for (const auto& entry : students) {
            outFile << entry.first << " " << entry.second << endl;
        }
        return true;
    }
    return false;
}

void Studentdatabase::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    string id, password;
    while (inFile >> id >> password) {
        students[id] = password;
        string dummy;
        getline(inFile, dummy);
    }
}

// Staffdatabase implementations
void Staffdatabase::saveStaffData(const string &id, const string &password, const string &name,
                                  const string &role, const string &department, double salary) {
    ofstream file("staff.txt", ios::app);
    file << id << " " << password << " " << name << " " << role << " "
         << department << " " << salary << endl;
    file.close();
    staff[id] = make_pair(password, role);
}

bool Staffdatabase::verifyLogin(const string &id, const string &password) {
    if (staff.find(id) != staff.end() && staff[id].first == password) {
        return true;
    }
    return false;
}

string Staffdatabase::generateID(char type) {
    int num = 100000 + rand() % 900000;
    return type + to_string(num);
}

bool Staffdatabase::isCanteenStaff(const string& id) {
    if (staff.find(id) != staff.end() && staff[id].second == "canteen") {
        return true;
    }
    return false;
}

bool Staffdatabase::removeStaff(const string& id) {
    if (staff.erase(id) > 0) {
        ofstream outFile("staff.txt");
        for (const auto& entry : staff) {
            outFile << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
        }
        return true;
    }
    return false;
}

void Staffdatabase::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    string id, password, role;
    while (inFile >> id >> password >> role) {
        staff[id] = make_pair(password, role);
        string dummy;
        getline(inFile, dummy);
    }
}

// Canteendatabase implementations
void Canteendatabase::addCanteenItem(int id, const string& name, double price) {
    ofstream file("canteen.txt", ios::app);
    file << id << " " << name << " " << price << endl;
    file.close();
    canteenItems[id] = make_pair(name, price);
}

bool Canteendatabase::removeCanteenItem(int id) {
    if (canteenItems.erase(id) > 0) {
        ofstream outFile("canteen.txt");
        for (const auto& entry : canteenItems) {
            outFile << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
        }
        return true;
    }
    return false;
}

void Canteendatabase::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    int id;
    string name;
    double price;
    while (inFile >> id >> name >> price) {
        canteenItems[id] = make_pair(name, price);
    }
}