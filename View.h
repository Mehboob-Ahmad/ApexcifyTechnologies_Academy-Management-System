#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include <iostream>
#include "Header.h"

using namespace std;

class View {
public:
    void displayAdminMenu();
    void displayTeacherMenu();
    void displayStudentMenu();
    void displayStaffMenu(bool isCanteenStaff);

    void getTeacherDetails(string &name, string &password, string &className, string &timing, string &subjects, double &salary);
    void getTeacherID(string& id);

    void getStudentDetails(string &name, string &password, string &className, string &courses, double &fee);
    void getStudentID(string& id);

    void getStaffDetails(string &name, string &password, string &role, string &department, double &salary);
    void getStaffID(string& id);

    void getCanteenItemDetails(int &id, string &name, double &price);
    void getCanteenItemID(int& id);
};

#endif