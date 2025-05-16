#include "User.h"
#include "Course.h"
#include"Student.h"
#include"DataManager.h"
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;
User::User() {

}

User::User(const string& u, const string& p, const string& r) : username(u), password(p), role(r) {}/////////////////////////////////////////

unordered_map<string, Course> User::getCourses() const
{
    return courses;
}

void User::setCourses(const unordered_map<string, Course>& newCourses)
{
    courses = newCourses;
}

void User::setUsername(const string& u) {
    username = u;
}

void User::setPassword(const string& p) {
    password = p;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User::getRole() const { ///////////////////////////////////////////////////////////////////////
    return role;
}

void User::setRole(string r) { ////////////////////////////////////////////////////////////
    role = r;
}
void User::signUp(unordered_map<string, User>& users) {
    string studentID, username, email, password, firstName, lastName;
    int academicYear;
    string major;

    cout << "Sign up as a Student:\n";
    cout << "Enter Student ID: ";
    cin >> studentID;

    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists in users map
    if (users.find(username) != users.end()) {
        cout << "Username already taken. Please try again.\n";
        return;
    }

    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter academic year (number): ";
    cin >> academicYear;
    cout << "Enter major: ";
    cin >> major;

    // Create Student with constructor
    Student newStudent(username, password, "S");
    newStudent.setStudentID(studentID);
    newStudent.setEmail(email);
    newStudent.setStudentName(firstName, lastName);
    newStudent.setAcademicYear(academicYear);
    newStudent.setMajor(major);

    // Add to users map (keyed by username)
    users[username] = User(username, password, "S");

    // Add to DataManager singleton students map (keyed by studentID)
    DataManager& dm = DataManager::getInstance();
    dm.getStudents()[username] = newStudent;

    dm.saveStudents("students.txt");

    cout << "Sign up successful! You can now sign in.\n";
}




string User::signIn(const unordered_map<string, User>& users)
{
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second.getPassword() == password) {
        cout << "Sign in successful! Welcome, " << username << ".\n";
        return username;
    }
    else {
        cout << "Sign in failed. Invalid username or password.\n";
        return "";
    }
}
