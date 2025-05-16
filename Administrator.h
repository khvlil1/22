#pragma once
#include <unordered_map>
#include "User.h"
#include "Course.h"
#include "Student.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Instructor {
    string firstName;
    string lastName;
};

struct Semester {
    string studentID;
    string courseID;
    float grade;
};
class Administrator : public User
{
  public:
      Administrator(); /////////////////////////////////////////////////////////////////////////////////
      Administrator(const string& username, const string& password, const string& role);
    //Administrator(string u, string p);
    void uploadCourse();
    void setPrerequisites();
    void manageStudentGrades(unordered_map<string, Student>& students, const unordered_map<string, Course>& availableCourses);
};
