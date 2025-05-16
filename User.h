#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include "Course.h"
using namespace std;
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
    User(string u, string p, string r = "");
    unordered_map<string, Course> getCourses() const;
    void setCourses(const unordered_map<string, Course>& newCourses);
    string getUsername() const;
    string getPassword() const;
    string getRole() const;//////////////////////////////////////////////////////
    void setRole(string r);///////////////////////////
    static void signUp(unordered_map<string, User>& users);
    static string signIn(const unordered_map<string, User>& users);
};

