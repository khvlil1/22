#include "ManageStudents.h"
#include "Student.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

using namespace std;

unordered_map<string, Student> ManageStudents::getStudents() const {
    return students;
}

void ManageStudents::setStudents(const unordered_map<string, Student>& newStudents) {
    students = newStudents;
}

bool ManageStudents::hasStudent(const string& id) const {
    return students.find(id) != students.end();
}

void ManageStudents::printAllStudents() const {
    for (const auto& pair : students) {
        const Student& s = pair.second;
        cout << "ID: " << pair.first
            << ", First Name: " << s.getStudentfName()
            << ", Last Name: " << s.getStudentlName()
            << ", Year: " << s.getAcademicYear()
            << endl;
    }
}
