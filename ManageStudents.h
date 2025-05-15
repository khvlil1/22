#pragma once
#include <unordered_map>
#include <string>
#include "Student.h"
#include <iostream>
#include <utility>

class ManageStudents
{
private:
    unordered_map<string, Student> students;
public:
    unordered_map<string, Student> getStudents() const;
    void setStudents(const unordered_map<string, Student>& newStudents);
    bool hasStudent(const string& id) const;
    void printAllStudents() const;
};
