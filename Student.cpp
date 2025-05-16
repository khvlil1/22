#include "Student.h"
#include<stack>
#include <unordered_map>
#include<vector>
#include <iostream>
#include <string>
using namespace std;

Student::Student() : academicYear(0) {}


Student::Student(const string& username, const string& password, const string& role) : User(username,password,role) {}

void Student::setStudentID(const string& id) {
    StudentId = id;
}

void Student::setStudentName(const string& fname, const string& lname) {
    firstName = fname;
    lastName = lname;
}

void Student::setEmail(const string& e) {
    email = e;
}

void Student::setPassword(const string& pwd) {
    User::setPassword(pwd);
}

void Student::setAcademicYear(int year) {
    academicYear = year;
}

void Student::setMajor(const string& m) {
    major = m;
}

string Student::getStudentID() const {
    return StudentId;
}

string Student::getStudentfName() const {
    return firstName;
 }


string Student::getStudentlName() const {
    return lastName;
}

string Student::getEmail() const {
    return email;
}

string Student::getPassword() const {
    return User::getPassword();
}

int Student::getAcademicYear() const {
    return academicYear;
}

string Student::getMajor() const {
    return major;
}


unordered_map<string, Course> Student::getRegisteredCourses() const
{
    return registeredCourses;
}
unordered_map<string, float> Student::getGrades() const {
    return grades;
}
void Student::setRegisteredCourses(const unordered_map<string, Course>& courses)
{
    registeredCourses = courses;
}
void Student::Search(const string& courseID, const unordered_map<string, Course>& availableCourses) {
    auto it = availableCourses.find(courseID);

    if (it != availableCourses.end()) {
        const Course& course = it->second;
        cout << "\nCourse found:\n";
        cout << "ID: " << course.getCourseID() << "\n";
        cout << "Name: " << course.getCourseName() << "\n";
        cout << "Credit Hours: " << course.getCreditHours() << "\n";
        cout << "Instructor: " << course.getInstructor() << "\n";

        // Check if already registered
        if (registeredCourses.find(courseID) != registeredCourses.end()) {
            cout << "You are already registered for this course.\n";
            return;
        }

        char choice;
        cout << "Do you want to register this course? (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            vector<string> prerequisites = course.getPrerequisites();
            bool allPrereqsMet = true;

            if (!prerequisites.empty()) {
                cout << "Checking prerequisites...\n";

                // Debug: Print all registered courses
                cout << "Your registered courses: " << endl;
                for (const auto& pair : registeredCourses) {
                    cout << "- " << pair.second.getCourseName() << " (ID: " << pair.first << ")" << endl;
                }

                for (const string& prereqID : prerequisites) {
                    cout << "Checking prerequisite: " << prereqID;

                    // Find the name of this prerequisite for better output
                    string prereqName = prereqID;
                    if (availableCourses.find(prereqID) != availableCourses.end()) {
                        prereqName = availableCourses.at(prereqID).getCourseName();
                        cout << " (" << prereqName << ")";
                    }
                    cout << endl;

                    // Check if this prerequisite is in registered courses
                    if (registeredCourses.find(prereqID) == registeredCourses.end()) {
                        cout << "Missing prerequisite course: " << prereqName << " (ID: " << prereqID << ")" << endl;
                        allPrereqsMet = false;
                    }
                    else {
                        cout << "Prerequisite met: " << prereqName << endl;
                    }
                }
            }

            if (!allPrereqsMet) {
                cout << "Cannot register course. Prerequisites not satisfied.\n";
                return;
            }

            registeredCourses[courseID] = course;
            CurrentRegistration.push(courseID);
            cout << "Course registered successfully.\n";

            // Debug: Print updated registered courses
            cout << "Your updated registered courses: " << endl;
            for (const auto& pair : registeredCourses) {
                cout << "- " << pair.second.getCourseName() << " (ID: " << pair.first << ")" << endl;
            }
        }
        else {
            cout << "Course not registered.\n";
        }
    }
    else {
        cout << "Course with ID '" << courseID << "' not found.\n";
        cout << "Available courses are:\n";
        for (const auto& pair : availableCourses) {
            cout << "ID: " << pair.first << ", Name: " << pair.second.getCourseName() << "\n";
        }
    }
}

 void Student::setGrade(const string & courseID, float grade) {
        grades[courseID] = grade;
}
 void Student::ViewStudentGrades() {
     if (grades.empty()) {
         cout << "No grades available for this student.\n";
         return;
     }

     cout << "\nGrades for registered courses:\n";
     for (const auto& pair : grades) {
         cout << "Course ID: " << pair.first << " -> Grade: " << pair.second << "\n";
     }
 }
 bool Student::RemoveRegistration() {
     if (CurrentRegistration.empty()) {
         cout << "No registration to undo.\n";
         return false;
     }

     // Pop the last course ID from the stack
     string lastCourseID = CurrentRegistration.top();
     CurrentRegistration.pop();

     // Find the course in the registered courses map
     auto course = registeredCourses.find(lastCourseID);
     if (course != registeredCourses.end()) {
         string courseName = course->second.getCourseName();

         // Corrected: Erase the course using the key (lastCourseID)
         registeredCourses.erase(lastCourseID);

         cout << "Successfully unregistered from course: " << courseName << " (ID: " << lastCourseID << ")\n";

         // Print updated course list
         cout << "\nYour current registered courses:\n";
         for (const auto& pair : registeredCourses) {
             cout << "- " << pair.second.getCourseName() << " (ID: " << pair.first << ")" << endl;
         }
         return true;
     }
     else {
         cout << "Error: Course " << lastCourseID << " not found in registered courses.\n";
         return false;
     }
 }


   
