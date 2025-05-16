#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include "Course.h"
using namespace std;
struct SignupInfo {
    std::string username;
    std::string password;
    std::string role;
};

class User
{
protected:
    string username;
    string password;
    string role;  // "A" or "S"///////////////////////////////////////////////////////////////////////
private:
    unordered_map<string, Course> courses;
public:
    User();
    User(const string& username, const string& password, const string& role);
    unordered_map<string, Course> getCourses() const;
    void setCourses(const unordered_map<string, Course>& newCourses);
    void setUsername(const string& username);
    void setPassword(const string& password);
    string getUsername() const;
    string getPassword() const;
    string getRole() const;//////////////////////////////////////////////////////
    void setRole(string r);///////////////////////////
    static void signUp(unordered_map<string, User>& users);
    static string signIn(const unordered_map<string, User>& users);
    static SignupInfo signUp(const unordered_map<string, User>& users);
};
