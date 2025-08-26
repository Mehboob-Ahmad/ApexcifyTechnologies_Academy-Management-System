#include "Controller.h"
#include "View.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;



int main() {
    srand(time(0));


    View view;
    Controller controller;

    controller.loadInitialData(); 

    int choice;
    do {
        cout << "==============================================" << endl;
        cout << "           WELCOME TO OUR ACADEMY!" << endl;
        cout << "==============================================" << endl;
        cout << "Please select one option:" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "==============================================" << endl;

        switch(choice) {
            case 1:
                controller.adminLogin();
                break;
            case 2:
                {
                    int loginType;
                    cout << "Select account type:" << endl;
                    cout << "1. Teacher" << endl;
                    cout << "2. Student" << endl;
                    cout << "3. Staff" << endl;
                    cout << "Enter your choice: ";
                    cin >> loginType;

                    switch(loginType) {
                        case 1:
                            controller.teacherLogin();
                            break;
                        case 2:
                            controller.studentLogin();
                            break;
                        case 3:
                            controller.staffLogin();
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                }
                break;
            case 0:
                cout << "==============================================" << endl;
                cout << "           THANK YOU FOR VISITING!" << endl;
                cout << "==============================================" << endl;
                cout << "We hope you had a great experience with our" << endl;
                cout << "Academy Management System." << endl;
                cout << endl;
                cout << "We look forward to serving you again soon!" << endl;
                cout << "Have a wonderful day!" << endl;
                cout << "==============================================" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}