#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Course
{
private:
    string courseID;
    string courseName;
    string description;
    int creditHours;
    string instructor;
    string syllabus;
    vector<string> prerequisites;


public:
    Course();

    string getCourseID() const;
    string getCourseName() const;
    int getCreditHours() const;
    string getInstructor() const;
    string getSyllabus() const;
    vector<string> getPrerequisites() const;

    void setCourseID(const string& id);
    void setCourseName(const string& name);
    void setCreditHours(int hours);
    void setInstructor(const string& instr);
    void setSyllabus(const string& syl);
    void setPrerequisites(const vector<string>& prereq);
};
