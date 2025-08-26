#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "Header.h"

using namespace std;

class Teacherdatabase {
private:
    map<string, string> teachers;
public:
    void saveTeacherData(const string &id, const string &password, const string &name,
                         const string &className, const string &timing, const string &subjects, double salary);
    bool verifyLogin(const string &id, const string &password);
    string generateID(char type);
    bool removeTeacher(const string& id);
    void loadFromFile(const string& filename);
};

class Studentdatabase {
private:
    map<string, string> students;
public:
    void saveStudentData(const string &id, const string &password, const string &name,
                         const string &className, const string &courses, double fee);
    bool verifyLogin(const string &id, const string &password);
    string generateID(char type);
    bool removeStudent(const string& id);
    void loadFromFile(const string& filename);
};

class Staffdatabase {
private:
    map<string, pair<string, string>> staff;
public:
    void saveStaffData(const string &id, const string &password, const string &name,
                       const string &role, const string &department, double salary);
    bool verifyLogin(const string &id, const string &password);
    string generateID(char type);
    bool isCanteenStaff(const string& id);
    bool removeStaff(const string& id);
    void loadFromFile(const string& filename);
};

class Canteendatabase {
private:
    map<int, pair<string, double>> canteenItems;
public:
    void addCanteenItem(int id, const string& name, double price);
    bool removeCanteenItem(int id);
    void loadFromFile(const string& filename);
};

#endif