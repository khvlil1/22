#pragma once
#include <iostream>
#include<stack>
#include <unordered_map>
#include <vector>
#include "User.h"
#include "Course.h"
using namespace std;

class Student :public User
{
private:
    string StudentId;
    string firstName;
    string lastName;
    string email;
    string password;
    int academicYear;
    string major;
    unordered_map<string, Course> registeredCourses;
    unordered_map<string, float> grades;
    stack<string> CurrentRegistration;
    friend class Administrator; // to access grades


public:
    Student();
    Student(const string& username, const string& password, const string& role);
    void setStudentID(const string& id);
    void setStudentName(const string& fname, const string& lname);
    void setEmail(const string& email);
    void setPassword(const string& pwd);
    void setAcademicYear(int year);
    void setMajor(const string& major);

    string getStudentID() const;
    string getStudentfName() const;
    string getStudentlName() const;
    string getEmail() const;
    string getPassword() const;
    int getAcademicYear() const;
    string getMajor() const;
    unordered_map<std::string, float> getGrades() const;


    
    void ViewStudentGrades();


    void setRegisteredCourses(const unordered_map<string, Course>& courses);
    unordered_map<string, Course> getRegisteredCourses() const;
    void Search(const string& courseID, const unordered_map<string, Course>& availableCourses);
    bool RemoveRegistration();
    void GenerateReport()const;
};
