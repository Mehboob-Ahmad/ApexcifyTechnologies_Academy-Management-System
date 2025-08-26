#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include "Database.h"
#include "View.h"
#include "Header.h"

using namespace std;

class Controller {
private:
    Teacherdatabase teacherDb;
    Studentdatabase studentDb;
    Staffdatabase staffDb;
    Canteendatabase canteenDb;
    View view;
    string getCurrentDate();
    void createClassFile(const string &className, const string &teacherID, const string &teacherName,
                            const string &subject, const string &timing);
    void addStudentToClass(const string &className, const string &studentID, const string &studentName);
    vector<pair<string, string>> getStudentsInClass(const string &className);
    string getTeacherClass(const string &teacherID);

public:
    void loadInitialData();

    void adminLogin();
    void teacherLogin();
    void studentLogin();
    void staffLogin();

    void adminMenu();
    void teacherMenu(const string &teacherID);
    void studentMenu(const string &studentID);
    void staffMenu(const string &staffID);

    void addTeacher();
    void removeTeacher();
    void addStudent();
    void removeStudent();
    void addStaff();
    void removeStaff();

    void checkBills();
    void paySalary();
    void issueStudentVoucher();
    void addCanteenItems();
    void orderCanteenItems();
    void removeCanteenItems();
    void checkApplications();
    void checkResults();
    void makeAnnouncements();
    void freezeAccount();
    void unfreezeAccount();

    void applyForApplicationTeacher(const string &teacherID);
    void checkScheduleTeacher(const string &teacherID);
    void checkStudentResultsTeacher(const string &teacherID);
    void makeAnnouncementTeacher(const string &teacherID);
    void checkMyResultTeacher(const string &teacherID);
    void takeAttendanceTeacher(const string &teacherID);

    void applyForApplicationStudent(const string &studentID);
    void checkMyResultStudent(const string &studentID);
    void checkMyCoursesStudent(const string &studentID);
    void checkMyTeachersStudent(const string &studentID);
    void checkMyAttendanceStudent(const string &studentID);
    void checkFeeVoucherStudent(const string &studentID);

    void applyForApplicationStaff(const string &staffID);
    void orderCanteenItemsStaff();
    void updateCanteenPricesStaff();
};

#endif