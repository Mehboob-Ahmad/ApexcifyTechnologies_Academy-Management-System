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
#include <sstream>
#include <iomanip>
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

// Helper functions
string Controller::getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year);
    return date;
}

void Controller::createClassFile(const string &className, const string &teacherID, const string &teacherName,
                                const string &subject, const string &timing) {
    ofstream file("class_" + className + ".txt");
    if (file.is_open()) {
        file << "Class: " << className << endl;
        file << "Teacher: " << teacherID << " | " << teacherName << " | " << subject << " | " << timing << endl;
        file << "Students:" << endl;
        file.close();
        cout << "Class file created successfully for class " << className << endl;
    } else {
        cout << "Error creating class file." << endl;
    }
}

void Controller::addStudentToClass(const string &className, const string &studentID, const string &studentName) {
    ofstream file("class_" + className + ".txt", ios::app);
    if (file.is_open()) {
        file << studentID << " | " << studentName << endl;
        file.close();
    } else {
        cout << "Error adding student to class file. Class might not exist." << endl;
    }
}

vector<pair<string, string>> Controller::getStudentsInClass(const string &className) {
    vector<pair<string, string>> students;
    ifstream file("class_" + className + ".txt");
    if (file.is_open()) {
        string line;
        bool studentsSection = false;
        while (getline(file, line)) {
            if (line == "Students:") {
                studentsSection = true;
                continue;
            }
            if (studentsSection && !line.empty()) {
                size_t pos = line.find("|");
                if (pos != string::npos) {
                    string id = line.substr(0, pos - 1);
                    string name = line.substr(pos + 2);
                    students.push_back(make_pair(id, name));
                }
            }
        }
        file.close();
    }
    return students;
}

string Controller::getTeacherClass(const string &teacherID) {
    ifstream file("teachers.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(teacherID);
            if (pos != string::npos) {
                // Extract class name from teacher record
                vector<string> tokens;
                string token;
                istringstream tokenStream(line);
                while (getline(tokenStream, token, ' ')) {
                    tokens.push_back(token);
                }
                if (tokens.size() >= 4) {
                    return tokens[3]; // Assuming class name is the 4th token
                }
            }
        }
        file.close();
    }
    return "";
}

// Function implementations
void Controller::addTeacher() {
    string name, password, id, className, timing, subjects;
    double salary;
    view.getTeacherDetails(name, password, className, timing, subjects, salary);
    id = teacherDb.generateID('T');
    teacherDb.saveTeacherData(id, password, name, className, timing, subjects, salary);

    // Create class file for this teacher
    createClassFile(className, id, name, subjects, timing);

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
    id = studentDb.generateID('S');
    studentDb.saveStudentData(id, password, name, className, courses, fee);

    // Add student to class file
    addStudentToClass(className, id, name);

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
    id = staffDb.generateID('F');
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
    cout << "=== BILLS MANAGEMENT ===" << endl;
    cout << "1. View Current Bills" << endl;
    cout << "2. Add New Bill" << endl;
    cout << "3. Mark Bill as Paid" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            ifstream file("bills.txt");
            if (file.is_open()) {
                string line;
                cout << "=== CURRENT BILLS ===" << endl;
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
            } else {
                cout << "No bills found." << endl;
            }
            break;
        }
        case 2: {
            string billType, amount, dueDate;
            cout << "Enter bill type (electricity/water/internet/other): ";
            cin.ignore();
            getline(cin, billType);
            cout << "Enter amount: $";
            getline(cin, amount);
            cout << "Enter due date (DD-MM-YYYY): ";
            getline(cin, dueDate);

            ofstream file("bills.txt", ios::app);
            file << billType << " - $" << amount << " - Due: " << dueDate << " - Status: PENDING" << endl;
            file.close();
            cout << "Bill added successfully!" << endl;
            break;
        }
        case 3: {
            string billType;
            cout << "Enter bill type to mark as paid: ";
            cin.ignore();
            getline(cin, billType);
            cout << "Bill marked as paid (simulated)." << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::paySalary() {
    cout << "=== SALARY PAYMENT ===" << endl;
    string id;
    cout << "Enter employee ID: ";
    cin >> id;

    double amount;
    cout << "Enter salary amount: $";
    cin >> amount;

    string month;
    cout << "Enter month (e.g., January 2024): ";
    cin.ignore();
    getline(cin, month);


    ifstream teacherFile("teachers.txt");
    bool isTeacher = false;
    if (teacherFile.is_open()) {
        string line;
        while (getline(teacherFile, line)) {
            istringstream iss(line);
            string teacherId;
            iss >> teacherId;
            if (teacherId == id) {
                isTeacher = true;
                break;
            }
        }
        teacherFile.close();
    }


    ifstream staffFile("staff.txt");
    bool isStaff = false;
    if (staffFile.is_open()) {
        string line;
        while (getline(staffFile, line)) {
            istringstream iss(line);
            string staffId;
            iss >> staffId;
            if (staffId == id) {
                isStaff = true;
                break;
            }
        }
        staffFile.close();
    }

    if (isTeacher) {
        ofstream file("salary_payments.txt", ios::app);
        file << "Teacher " << id << " - $" << amount << " - " << month << " - Paid on: " << getCurrentDate() << endl;
        file.close();
        cout << "Salary paid successfully to teacher!" << endl;
    }
    else if (isStaff) {
        ofstream file("salary_payments.txt", ios::app);
        file << "Staff " << id << " - $" << amount << " - " << month << " - Paid on: " << getCurrentDate() << endl;
        file.close();
        cout << "Salary paid successfully to staff!" << endl;
    }
    else {
        cout << "Employee ID not found!" << endl;
    }
}

void Controller::issueStudentVoucher() {
    cout << "=== FEE VOUCHER ISSUANCE ===" << endl;
    string studentId;
    cout << "Enter student ID: ";
    cin >> studentId;

    if (studentDb.verifyLogin(studentId, "dummy")) {
        double amount;
        cout << "Enter fee amount: $";
        cin >> amount;

        string dueDate;
        cout << "Enter due date (DD-MM-YYYY): ";
        cin.ignore();
        getline(cin, dueDate);

        ofstream file("fee_vouchers.txt", ios::app);
        file << "Student " << studentId << " - Amount: $" << amount << " - Due: " << dueDate << " - Issued on: " << getCurrentDate() << endl;
        file.close();

        cout << "Fee voucher issued successfully!" << endl;
    } else {
        cout << "Student ID not found!" << endl;
    }
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
    cout << "=== CANTEEN ORDERING ===" << endl;

    // Display available items
    ifstream file("canteen.txt");
    if (file.is_open()) {
        string line;
        cout << "Available items:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No canteen items available." << endl;
        return;
    }

    string itemId, quantity;
    cout << "Enter item ID to order: ";
    cin >> itemId;
    cout << "Enter quantity: ";
    cin >> quantity;

    string customerType, customerId;
    cout << "Customer type (student/teacher/staff): ";
    cin >> customerType;
    cout << "Enter " << customerType << " ID: ";
    cin >> customerId;

    ofstream orderFile("canteen_orders.txt", ios::app);
    orderFile << "Order: " << itemId << " x" << quantity << " - " << customerType << " " << customerId << " - " << getCurrentDate() << endl;
    orderFile.close();

    cout << "Order placed successfully!" << endl;
}

void Controller::removeCanteenItems() {
    int id;
    view.getCanteenItemID(id);
    canteenDb.removeCanteenItem(id);
    cout << "Canteen item removed successfully." << endl;
}

void Controller::checkApplications() {
    cout << "=== APPLICATIONS MANAGEMENT ===" << endl;
    cout << "1. View Pending Applications" << endl;
    cout << "2. Process Application" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            ifstream file("applications.txt");
            if (file.is_open()) {
                string line;
                cout << "=== PENDING APPLICATIONS ===" << endl;
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
            } else {
                cout << "No applications found." << endl;
            }
            break;
        }
        case 2: {
            string appId;
            cout << "Enter application ID to process: ";
            cin >> appId;
            string decision;
            cout << "Decision (approve/reject): ";
            cin >> decision;

            ofstream processFile("processed_applications.txt", ios::app);
            processFile << "Application " << appId << " - Decision: " << decision << " - Processed on: " << getCurrentDate() << endl;
            processFile.close();

            cout << "Application processed successfully!" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::checkResults() {
    cout << "=== RESULTS MANAGEMENT ===" << endl;
    cout << "1. View All Results" << endl;
    cout << "2. Add New Results" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            ifstream file("exam_results.txt");
            if (file.is_open()) {
                string line;
                cout << "=== EXAM RESULTS ===" << endl;
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
            } else {
                cout << "No results found." << endl;
            }
            break;
        }
        case 2: {
            string className, subject, results;
            cout << "Enter class name: ";
            cin.ignore();
            getline(cin, className);
            cout << "Enter subject: ";
            getline(cin, subject);
            cout << "Enter results (format: StudentID1:Grade1, StudentID2:Grade2, ...): ";
            getline(cin, results);

            ofstream file("exam_results.txt", ios::app);
            file << "Class: " << className << " - Subject: " << subject << " - Results: " << results << " - Date: " << getCurrentDate() << endl;
            file.close();

            cout << "Results added successfully!" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::makeAnnouncements() {
    cout << "=== MAKE ANNOUNCEMENT ===" << endl;
    string title, content, target;

    cout << "Enter announcement title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter announcement content: ";
    getline(cin, content);
    cout << "Enter target audience (all/students/teachers/staff/specific class): ";
    getline(cin, target);

    ofstream file("announcements.txt", ios::app);
    file << "Title: " << title << " | Target: " << target << " | Date: " << getCurrentDate() << endl;
    file << "Content: " << content << endl;
    file << "----------------------------------------" << endl;
    file.close();

    cout << "Announcement posted successfully!" << endl;
}

void Controller::freezeAccount() {
    cout << "=== FREEZE ACCOUNT ===" << endl;
    string id, accountType, reason;

    cout << "Enter account ID to freeze: ";
    cin >> id;
    cout << "Enter account type (student/teacher/staff): ";
    cin >> accountType;
    cout << "Enter reason for freezing: ";
    cin.ignore();
    getline(cin, reason);

    ofstream file("frozen_accounts.txt", ios::app);
    file << accountType << " " << id << " - Reason: " << reason << " - Frozen on: " << getCurrentDate() << endl;
    file.close();

    cout << "Account frozen successfully!" << endl;
}

void Controller::unfreezeAccount() {
    cout << "=== UNFREEZE ACCOUNT ===" << endl;
    string id, accountType;

    cout << "Enter account ID to unfreeze: ";
    cin >> id;
    cout << "Enter account type (student/teacher/staff): ";
    cin >> accountType;

    ofstream file("unfrozen_accounts.txt", ios::app);
    file << accountType << " " << id << " - Unfrozen on: " << getCurrentDate() << endl;
    file.close();

    cout << "Account unfrozen successfully!" << endl;
}

void Controller::applyForApplicationTeacher(const string &teacherID) {
    cout << "=== TEACHER APPLICATION ===" << endl;
    string applicationType, details;

    cout << "Application type (leave/course change/resource request/other): ";
    cin.ignore();
    getline(cin, applicationType);
    cout << "Enter application details: ";
    getline(cin, details);

    ofstream file("teacher_applications.txt", ios::app);
    file << "Teacher " << teacherID << " - Type: " << applicationType << " - Date: " << getCurrentDate() << endl;
    file << "Details: " << details << endl;
    file << "----------------------------------------" << endl;
    file.close();

    cout << "Application submitted successfully!" << endl;
}

void Controller::checkScheduleTeacher(const string &teacherID) {
    cout << "=== TEACHER SCHEDULE ===" << endl;
    cout << "1. View Current Schedule" << endl;
    cout << "2. Request Schedule Change" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            ifstream file("teacher_schedules.txt");
            if (file.is_open()) {
                string line;
                bool found = false;
                while (getline(file, line)) {
                    if (line.find(teacherID) != string::npos) {
                        cout << line << endl;
                        found = true;
                    }
                }
                file.close();
                if (!found) {
                    cout << "No schedule found for teacher " << teacherID << endl;
                }
            } else {
                cout << "No schedules available." << endl;
            }
            break;
        }
        case 2: {
            string currentTiming, requestedTiming, reason;
            cout << "Enter current timing: ";
            cin.ignore();
            getline(cin, currentTiming);
            cout << "Enter requested timing: ";
            getline(cin, requestedTiming);
            cout << "Enter reason for change: ";
            getline(cin, reason);

            ofstream file("schedule_change_requests.txt", ios::app);
            file << "Teacher " << teacherID << " - Current: " << currentTiming << " - Requested: " << requestedTiming << endl;
            file << "Reason: " << reason << " - Date: " << getCurrentDate() << endl;
            file.close();

            cout << "Schedule change request submitted!" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::checkStudentResultsTeacher(const string &teacherID) {
    cout << "=== ENTER STUDENT RESULTS ===" << endl;

    // Get the class this teacher teaches
    string className = getTeacherClass(teacherID);
    if (className.empty()) {
        cout << "No class assigned to this teacher." << endl;
        return;
    }

    cout << "Entering results for class: " << className << endl;

    // Get students in this class
    vector<pair<string, string>> students = getStudentsInClass(className);
    if (students.empty()) {
        cout << "No students found in this class." << endl;
        return;
    }

    string subject;
    cout << "Enter subject: ";
    cin.ignore();
    getline(cin, subject);

    string examType;
    cout << "Enter exam type (e.g., Midterm, Final): ";
    getline(cin, examType);

    double totalMarks = 0;
    int studentCount = 0;

    ofstream resultFile("exam_results_" + className + "_" + subject + "_" + examType + ".txt");
    resultFile << "Class: " << className << " | Subject: " << subject << " | Exam: " << examType << " | Date: " << getCurrentDate() << endl;
    resultFile << "Teacher: " << teacherID << endl;
    resultFile << "----------------------------------------" << endl;

    for (const auto& student : students) {
        double marks;
        cout << "Enter marks for " << student.second << " (" << student.first << "): ";
        cin >> marks;

        resultFile << student.first << " | " << student.second << " | " << marks << endl;
        totalMarks += marks;
        studentCount++;
    }

    double average = studentCount > 0 ? totalMarks / studentCount : 0;
    resultFile << "----------------------------------------" << endl;
    resultFile << "Class Average: " << fixed << setprecision(2) << average << endl;
    resultFile.close();

    cout << "Results recorded successfully! Class average: " << average << endl;
}

void Controller::makeAnnouncementTeacher(const string &teacherID) {
    cout << "=== TEACHER ANNOUNCEMENT ===" << endl;
    string className, announcement;

    cout << "Enter class name: ";
    cin.ignore();
    getline(cin, className);
    cout << "Enter announcement: ";
    getline(cin, announcement);

    ofstream file("class_announcements.txt", ios::app);
    file << "Class: " << className << " - Teacher: " << teacherID << " - Date: " << getCurrentDate() << endl;
    file << "Announcement: " << announcement << endl;
    file << "----------------------------------------" << endl;
    file.close();

    cout << "Announcement posted to class " << className << "!" << endl;
}

void Controller::checkMyResultTeacher(const string &teacherID) {
    cout << "=== TEACHER PERFORMANCE ===" << endl;
    cout << "1. View Performance Report" << endl;
    cout << "2. View Student Feedback" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            cout << "Performance Report for Teacher " << teacherID << ":" << endl;
            cout << "Overall Rating: 4.5/5" << endl;
            cout << "Students Pass Percentage: 92%" << endl;
            cout << "Attendance: 98%" << endl;
            cout << "Classes Assigned: 4" << endl;
            break;
        }
        case 2: {
            ifstream file("teacher_feedback.txt");
            if (file.is_open()) {
                string line;
                bool found = false;
                while (getline(file, line)) {
                    if (line.find(teacherID) != string::npos) {
                        cout << line << endl;
                        found = true;
                    }
                }
                file.close();
                if (!found) {
                    cout << "No feedback found for teacher " << teacherID << endl;
                }
            } else {
                cout << "No feedback available." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::takeAttendanceTeacher(const string &teacherID) {
    cout << "=== TAKE ATTENDANCE ===" << endl;
    string className, date;
    int totalStudents, presentStudents;

    cout << "Enter class name: ";
    cin.ignore();
    getline(cin, className);
    cout << "Enter date (DD-MM-YYYY): ";
    getline(cin, date);
    cout << "Enter total number of students: ";
    cin >> totalStudents;
    cout << "Enter number of present students: ";
    cin >> presentStudents;

    double attendancePercentage = (static_cast<double>(presentStudents) / totalStudents) * 100;

    ofstream file("attendance_records.txt", ios::app);
    file << "Class: " << className << " - Teacher: " << teacherID << " - Date: " << date << endl;
    file << "Present: " << presentStudents << "/" << totalStudents << " (" << fixed << setprecision(2) << attendancePercentage << "%)" << endl;
    file << "----------------------------------------" << endl;
    file.close();

    cout << "Attendance recorded successfully!" << endl;
}

void Controller::applyForApplicationStudent(const string &studentID) {
    cout << "=== STUDENT APPLICATION ===" << endl;
    string applicationType, details;

    cout << "Application type (course change/fee concession/leave/other): ";
    cin.ignore();
    getline(cin, applicationType);
    cout << "Enter application details: ";
    getline(cin, details);

    ofstream file("student_applications.txt", ios::app);
    file << "Student " << studentID << " - Type: " << applicationType << " - Date: " << getCurrentDate() << endl;
    file << "Details: " << details << endl;
    file << "----------------------------------------" << endl;
    file.close();

    cout << "Application submitted successfully!" << endl;
}

void Controller::checkMyResultStudent(const string &studentID) {
    cout << "=== MY RESULTS ===" << endl;
    cout << "1. View All Results" << endl;
    cout << "2. View Result by Subject" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            // Simulate fetching results
            cout << "Results for Student " << studentID << ":" << endl;
            cout << "Mathematics: 85%" << endl;
            cout << "Science: 92%" << endl;
            cout << "English: 88%" << endl;
            cout << "History: 79%" << endl;
            cout << "Overall Grade: B+" << endl;
            break;
        }
        case 2: {
            string subject;
            cout << "Enter subject: ";
            cin.ignore();
            getline(cin, subject);

            // Simulate fetching specific subject result
            cout << subject << " result for Student " << studentID << ": 85%" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::checkMyCoursesStudent(const string &studentID) {
    cout << "=== MY COURSES ===" << endl;
    cout << "1. View Current Courses" << endl;
    cout << "2. Request Course Change" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            // Simulate fetching courses
            cout << "Courses for Student " << studentID << ":" << endl;
            cout << "1. Mathematics" << endl;
            cout << "2. Science" << endl;
            cout << "3. English" << endl;
            cout << "4. Computer Science" << endl;
            break;
        }
        case 2: {
            string currentCourse, requestedCourse, reason;
            cout << "Enter current course: ";
            cin.ignore();
            getline(cin, currentCourse);
            cout << "Enter requested course: ";
            getline(cin, requestedCourse);
            cout << "Enter reason for change: ";
            getline(cin, reason);

            ofstream file("course_change_requests.txt", ios::app);
            file << "Student " << studentID << " - Current: " << currentCourse << " - Requested: " << requestedCourse << endl;
            file << "Reason: " << reason << " - Date: " << getCurrentDate() << endl;
            file.close();

            cout << "Course change request submitted!" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::checkMyTeachersStudent(const string &studentID) {
    cout << "=== MY TEACHERS ===" << endl;
    // Simulate fetching teachers
    cout << "Teachers for Student " << studentID << ":" << endl;
    cout << "Mathematics: Mr. Smith" << endl;
    cout << "Science: Ms. Johnson" << endl;
    cout << "English: Mr. Williams" << endl;
    cout << "Computer Science: Dr. Brown" << endl;
}

void Controller::checkMyAttendanceStudent(const string &studentID) {
    cout << "=== MY ATTENDANCE ===" << endl;
    cout << "1. View Overall Attendance" << endl;
    cout << "2. View Attendance by Subject" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice) {
        case 1: {
            // Simulate fetching attendance
            cout << "Overall Attendance for Student " << studentID << ": 95%" << endl;
            cout << "Days Present: 95/100" << endl;
            break;
        }
        case 2: {
            string subject;
            cout << "Enter subject: ";
            cin.ignore();
            getline(cin, subject);

            // Simulate fetching specific subject attendance
            cout << subject << " attendance for Student " << studentID << ": 98%" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Controller::checkFeeVoucherStudent(const string &studentID) {
    cout << "=== FEE VOUCHER ===" << endl;
    // Simulate fetching fee voucher
    cout << "Fee Voucher for Student " << studentID << ":" << endl;
    cout << "Tuition Fee: $800.00" << endl;
    cout << "Lab Fee: $100.00" << endl;
    cout << "Library Fee: $50.00" << endl;
    cout << "Sports Fee: $50.00" << endl;
    cout << "Total: $1000.00" << endl;
    cout << "Due Date: 15-04-2024" << endl;
}

void Controller::applyForApplicationStaff(const string &staffID) {
    cout << "=== STAFF APPLICATION ===" << endl;
    string applicationType, details;

    cout << "Application type (leave/salary issue/resource request/other): ";
    cin.ignore();
    getline(cin, applicationType);
    cout << "Enter application details: ";
    getline(cin, details);

    ofstream file("staff_applications.txt", ios::app);
    file << "Staff " << staffID << " - Type: " << applicationType << " - Date: " << getCurrentDate() << endl;
    file << "Details: " << details << endl;
    file << "----------------------------------------" << endl;
    file.close();

    cout << "Application submitted successfully!" << endl;
}

void Controller::orderCanteenItemsStaff() {
    cout << "=== CANTEEN ORDERING (STAFF) ===" << endl;

    // Display available items
    ifstream file("canteen.txt");
    if (file.is_open()) {
        string line;
        cout << "Available items:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No canteen items available." << endl;
        return;
    }

    string itemId, quantity;
    cout << "Enter item ID to order: ";
    cin >> itemId;
    cout << "Enter quantity: ";
    cin >> quantity;

    string department;
    cout << "Enter department: ";
    cin.ignore();
    getline(cin, department);

    ofstream orderFile("staff_canteen_orders.txt", ios::app);
    orderFile << "Order: " << itemId << " x" << quantity << " - Staff Department: " << department << " - " << getCurrentDate() << endl;
    orderFile.close();

    cout << "Order placed successfully for department " << department << "!" << endl;
}

void Controller::updateCanteenPricesStaff() {
    cout << "=== UPDATE CANTEEN PRICES ===" << endl;
    int itemId;
    double newPrice;

    cout << "Enter item ID to update: ";
    cin >> itemId;
    cout << "Enter new price: $";
    cin >> newPrice;

    // In a real implementation, you would update the price in the database
    // For now, we'll just log the change
    ofstream file("price_updates.txt", ios::app);
    file << "Item " << itemId << " - New Price: $" << newPrice << " - Updated on: " << getCurrentDate() << endl;
    file.close();

    cout << "Price updated successfully for item " << itemId << " to $" << newPrice << endl;
}