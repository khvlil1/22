#include <unordered_map>
#include <vector>
#include <iostream>
#include "DataManager.h"
#include "Student.h"
#include "Administrator.h"
#include "Course.h"
#include "User.h"
#include "ManageStudents.h"
using namespace std;

void populateUsersFromDataManager(DataManager& dataManager, unordered_map<string, User>& users) {
    for (const auto& adminPair : dataManager.getAdmins()) {
        const Administrator& admin = adminPair.second;
        users[admin.getUsername()] = User(admin.getUsername(), admin.getPassword(), "A");
    }
    for (const auto& studentPair : dataManager.getStudents()) {
        const Student& student = studentPair.second;
        users[student.getUsername()] = User(student.getUsername(), student.getPassword(), "S");
    }
}

int main() {

    DataManager& dataManager = DataManager::getInstance();
    dataManager.loadAdmins("admins.txt");
    dataManager.loadCourses("courses.txt");
    dataManager.loadStudents("students.txt");

    unordered_map<string, User> users;
    populateUsersFromDataManager(dataManager, users);
    // Use references here to avoid copies
    auto& students = dataManager.getStudents();
    auto& availableCourses = dataManager.getCourses();

    Administrator admin("admin", "admin", "A"); // default admin

    cout << "Loaded users:\n";
    for (const auto& u : users) {
        cout << "Username: " << u.first << ", Password: " << u.second.getPassword() << endl;
    }

    char choice;
    string currentUsername;

    while (true) {
        cout << "Do you want to sign up (S), sign in (N), or exit (E)? ";
        cin >> choice;

        if (choice == 's' || choice == 'S') {
            User::signUp(users);
        }
        else if (choice == 'n' || choice == 'N') {
            currentUsername = User::signIn(users);
            if (currentUsername.empty()) {
                continue;
            }

            string role = users[currentUsername].getRole();

            if (role == "A") {
                char x;
                while (true) {
                    cout << "Do you want to upload course description (u), set prerequisites (s), manage grades (m), or exit (e)? ";
                    cin >> x;

                    if (x == 'u' || x == 'U') {
                        admin.uploadCourse();
                        unordered_map<string, Course> adminCourses = admin.getCourses();
                        for (const auto& pair : adminCourses) {
                            availableCourses[pair.first] = pair.second;
                        }
                    }
                    else if (x == 's' || x == 'S') {
                        admin.setPrerequisites();
                        unordered_map<string, Course> adminCourses = admin.getCourses();
                        for (const auto& pair : adminCourses) {
                            availableCourses[pair.first] = pair.second;
                        }

                    }
                    else if (x == 'm' || x == 'M') {
                        admin.manageStudentGrades(students, availableCourses);
                    }
                    else if (x == 'e' || x == 'E') {
                        break;
                    }
                }
            }
            else if (role == "S") {
                if (students.find(currentUsername) == students.end()) {
                    continue;
                }

                Student& student = students[currentUsername];

                char option;
                while (true) {
                    cout << "\nDo you want to register a course (r), view grades (v), undo course (u), or exit (e)? ";
                    cin >> option;

                    if (option == 'r' || option == 'R') {
                        string courseID;
                        cout << "Enter Course ID to search and register: ";
                        cin >> courseID;

                        cout << "Available courses: " << availableCourses.size() << endl;
                        for (const auto& pair : availableCourses) {
                            cout << "ID: " << pair.first << ", Name: " << pair.second.getCourseName() << endl;
                            vector<string> prereqs = pair.second.getPrerequisites();
                            if (!prereqs.empty()) {
                                cout << "  Prerequisites: ";
                                for (const string& p : prereqs) {
                                    cout << p << " ";
                                }
                                cout << endl;
                            }
                        }

                        student.Search(courseID, availableCourses);

                        cout << "After registration, student has these courses: ";
                        for (const auto& pair : student.getRegisteredCourses()) {
                            cout << pair.first << " ";
                        }
                        cout << endl;
                    }
                    else if (option == 'v' || option == 'V') {
                        student.ViewStudentGrades();
                    }
                    else if (option == 'u' || option == 'U') {
                        char undoChoice;
                        cout << "\nDo you want to undo this registration? (Y/N): ";
                        cin >> undoChoice;
                        if (undoChoice == 'Y' || undoChoice == 'y') {
                            if (student.RemoveRegistration()) {
                                cout << "Registration has been undone successfully.\n";
                            }
                            else {
                                cout << "No registration to undo.\n";
                            }
                        }
                    }
                    else if (option == 'e' || option == 'E') {
                        break;
                    }
                }
            }
        }
        else if (choice == 'e' || choice == 'E') {
            break;
        }
    }

    //dataManager->getStudents() = students;
    //dataManager->getCourses() = availableCourses;

    dataManager.saveAdmins("admins.txt");
    dataManager.saveCourses("courses.txt");
    dataManager.saveStudents("students.txt");

    return 0;
}
