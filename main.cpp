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
        users[student.getEmail()] = User(student.getEmail(), student.getPassword(), "S");

    }
}

int main() {
    
    DataManager dataManager;
    dataManager.loadAdmins("admins.txt");
    dataManager.loadCourses("courses.txt");
    dataManager.loadStudents("students.txt");

    unordered_map<string, User> users;
    populateUsersFromDataManager(dataManager, users);
    auto students = dataManager.getStudents();
    auto availableCourses = dataManager.getCourses();
    //unordered_map<string, User> users;
    //unordered_map<string, Course> availableCourses;
    //unordered_map<string, Student> students; // Store student objects by username
    Administrator admin("adminUser", "adminPass");
    //users["adminUser"] = User("adminUser", "adminPass");

    ////////////////////////////////////////////////////////////
    

    // Populate users from loaded admins and students
    //populateUsersFromDataManager(dataManager, users);
    cout << "Loaded users:\n";
    for (const auto& u : users) {
        cout << "Username: " << u.first << ", Password: " << u.second.getPassword() << endl;
    }

    // Populate local students map from DataManager students map
    students = dataManager.getStudents();

    // Populate availableCourses from DataManager courses map
    availableCourses = dataManager.getCourses();

    ///////////////////////////////////////////////////////////////////////
    char choice;
    string currentUsername; // Track the current logged-in user

    while (true) {
        cout << "Do you want to sign up (S), sign in (N), or exit (E)? ";
        cin >> choice;

        if (choice == 's' || choice == 'S') {
            User::signUp(users);
        }
        else if (choice == 'n' || choice == 'N') {
            currentUsername = User::signIn(users); // Modified to return username on success
            if (currentUsername.empty()) {
                continue;  // If sign-in fails, return to top of loop
            }


           
            
            string role = users[currentUsername].getRole();


            if (role == "A") {
                char x;
                while (true) {

                    cout << "Do you want to upload course description (u), set prerequisites (s), manage grades (m), or exit (e)? ";
                    cin >> x;

                    if (x == 'u' || x == 'U') {
                        admin.uploadCourse();
                        // Copy the course to availableCourses
                        unordered_map<string, Course> adminCourses = admin.getCourses();
                        for (const auto& pair : adminCourses) {
                            availableCourses[pair.first] = pair.second;
                        }
                    }
                    else if (x == 's' || x == 'S') {
                        admin.setPrerequisites();
                        // Update availableCourses with the updated prerequisites
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
                // Create a new student if this is the first time
                if (students.find(currentUsername) == students.end()) {
                   // students[currentUsername] = Student();
                    //students[currentUsername].setStudentName(currentUsername);
                }

                Student& student = students[currentUsername]; // Reference to the current student

                char option;
                while (true) {
                    cout << "\nDo you want to register a course (r), view grades (v), undo course (u), or exit (e)? ";
                    cin >> option;

                    if (option == 'r' || option == 'R') {
                        string courseID;
                        cout << "Enter Course ID to search and register: ";
                        cin >> courseID;

                        // Debug output to check available courses
                        cout << "Available courses: " << availableCourses.size() << endl;
                        for (const auto& pair : availableCourses) {
                            cout << "ID: " << pair.first << ", Name: " << pair.second.getCourseName() << endl;

                            // Debug output for prerequisites
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

                        // Debug output after registration
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
    // Update DataManager's maps before saving
    dataManager.getStudents() = students;
    dataManager.getCourses() = availableCourses;

    dataManager.saveAdmins("admins.txt");
    dataManager.saveCourses("courses.txt");
    dataManager.saveStudents("students.txt");
    return 0;
}
