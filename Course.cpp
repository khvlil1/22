#include "Course.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Course::Course() : creditHours(0) {}


string Course::getCourseID() const {
    return courseID;
}

string Course::getCourseName() const {
    return courseName;
}


int Course::getCreditHours() const {
    return creditHours;
}

string  Course::getInstructor() const {
    return instructor;
}

string Course::getSyllabus() const {
    return syllabus;
}

vector<string> Course::getPrerequisites() const {
    return prerequisites;
}



void Course::setCourseID(const string& id) {
    courseID = id;
}

void  Course::setCourseName(const string& name) {
    courseName = name;
}



void Course::setCreditHours(int hours) {
    creditHours = hours;
}

void  Course::setInstructor(const string& instr) {
    instructor = instr;
}

void  Course::setSyllabus(const string& syl) {
    syllabus = syl;
}

void Course::setPrerequisites(const vector<string>& prereq) {
    prerequisites = prereq;
}
