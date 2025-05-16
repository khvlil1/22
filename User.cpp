#include "User.h"
#include "Course.h"
#include"Student.h"
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;
User::User() {

}

User::User(string u, string p, string r) : username(u), password(p), role(r) {}/////////////////////////////////////////

unordered_map<string, Course> User::getCourses() const
{
    return courses;
}

void User::setCourses(const unordered_map<string, Course>& newCourses)
{
    courses = newCourses;
}


string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User:: getRole() const { ///////////////////////////////////////////////////////////////////////
    return role; 
}

void User:: setRole(string r) { ////////////////////////////////////////////////////////////
    role = r; 
}
void User::signUp(unordered_map<string, User>& users)
{
    unordered_map<string, Student> students;

    string username, password;
    string firstName, lastName, ID, role;

    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your ID: ";
    cin >> ID;

    while (true) {
        cout << "Create a username: ";
        cin >> username;
        if (users.find(username) != users.end()) {
            cout << "Username already exists. Please try again." << endl;
        }
        else {
            break;
        }
    }

    cout << "Create a password: ";
    cin >> password;

    // Ask for role only during sign-up
    while (true) {
        cout << "Are you signing up as an Administrator (A) or Student (S)? ";
        cin >> role;
        if (role == "A" || role == "a") {
            role = "A";
            User newUser(username, password);
            newUser.setRole(role);
            users[username] = newUser;
            break;
        }
        else if (role == "S" || role == "s") {
            role = "S";
            Student newStudent(username, password,role);
            newStudent.setStudentID(ID);
            students[ID] = newStudent;
            break;
        }
        else {
            cout << "Invalid choice. Please enter A or S." << endl;
        }
    }
    // el t7t dol kano sh8alen before adding el fe S and A w bysave bs only username and Year and Courses registered and grades, bs no ID no Name and password and Major also
    //User newUser(username, password);
    //newUser.setRole(role); // Make sure you have setRole method in User class
    //users[username] = newUser;

    cout << "Account created successfully!" << endl;
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
