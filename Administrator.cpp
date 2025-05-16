#include "Administrator.h"
#include "User.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;



Administrator::Administrator(string u, string p) : User(u, p) {}





void Administrator::uploadCourse() {
    Course newCourse;
    string courseID, courseName, description, instructorFirstName, instructorLastName, syllabus;
    int creditHours;

    cout << "Enter Course ID: ";
    cin >> courseID;
    newCourse.setCourseID(courseID);

    cout << "Enter Course Name: ";
    cin >> courseName;
    newCourse.setCourseName(courseName);

    cout << "Enter Credit Hours: ";
    cin >> creditHours;
    newCourse.setCreditHours(creditHours);

    cout << "Enter Instructor First Name: ";
    cin >> instructorFirstName;
    cout << "Enter Instructor Last Name: ";
    cin >> instructorLastName;
    newCourse.setInstructor(instructorFirstName + " " + instructorLastName);

    cout << "Enter Syllabus: ";
    cin >> syllabus;
    newCourse.setSyllabus(syllabus);

    unordered_map<string, Course> updatedCourses = getCourses();

    updatedCourses[courseID] = newCourse;
    setCourses(updatedCourses);
    cout << "Course uploaded successfully.\n";
}

void Administrator::setPrerequisites()
{
    string courseName;
    cout << "Enter Course Name to set prerequisites: ";
    cin.ignore(); // Clear input buffer
    getline(cin, courseName);

    unordered_map<string, Course> updatedCourses = getCourses();
    string targetCourseID = "";

    // Find the course ID by name
    for (const auto& pair : updatedCourses) {
        if (pair.second.getCourseName() == courseName) {
            targetCourseID = pair.first;
            break;
        }
    }

    if (!targetCourseID.empty()) {
        Course& currentCourse = updatedCourses[targetCourseID];

        vector<string> prerequisites;
        cout << "Enter prerequisite course names (type 'done' when finished):\n";

        string prereqName;
        while (true) {
            getline(cin, prereqName);
            if (prereqName == "done") break;

            // Find the course ID for this prerequisite name
            string prereqID = "";
            for (const auto& pair : updatedCourses) {
                if (pair.second.getCourseName() == prereqName) {
                    prereqID = pair.first;
                    break;
                }
            }

            if (!prereqID.empty()) {
                prerequisites.push_back(prereqID);
                cout << "Added prerequisite: " << prereqName << " (ID: " << prereqID << ")" << endl;
            }
            else {
                cout << "Warning: Course '" << prereqName << "' not found. Prerequisite not added." << endl;
            }
        }

        currentCourse.setPrerequisites(prerequisites);
        setCourses(updatedCourses);
        cout << "Prerequisites for course '" << courseName << "' set successfully.\n";

        // Debug output
        cout << "Course " << courseName << " (ID: " << targetCourseID << ") now has the following prerequisites: " << endl;
        for (const string& p : prerequisites) {
            for (const auto& pair : updatedCourses) {
                if (pair.first == p) {
                    cout << "- " << pair.second.getCourseName() << " (ID: " << p << ")" << endl;
                    break;
                }
            }
        }
    }
    else {
        cout << "Course with name '" << courseName << "' not found.\n";
    }

}
/////////neama function///////////
void Administrator::manageStudentGrades(unordered_map<string, Student>& students, const unordered_map<string, Course>& availableCourses) {
    string studentID, courseID;
    float grade;

    cout << "Enter Student Username: ";
    cin >> studentID;

    // Check if the student exists
    auto studentIt = students.find(studentID);
    if (studentIt == students.end()) {
        cout << "Error: Student with Username '" << studentID << "' not found.\n";
        return;
    }

    // Check available courses for this student
    Student& student = studentIt->second;
    cout << "Courses registered by student " << studentID << ":\n";
    auto registeredCourses = student.getRegisteredCourses();
    if (registeredCourses.empty()) {
        cout << "No courses registered by this student.\n";
        return;
    }

    // Display registered courses
    for (const auto& pair : registeredCourses) {
        cout << "ID: " << pair.first << ", Name: " << pair.second.getCourseName() << "\n";
    }

    cout << "Enter Course ID: ";
    cin >> courseID;

    // Check if the course exists in available courses
    auto courseIt = availableCourses.find(courseID);
    if (courseIt == availableCourses.end()) {
        cout << "Error: Course with ID '" << courseID << "' not found in available courses.\n";
        return;
    }

    // Check if the student is registered in this course
    if (registeredCourses.find(courseID) == registeredCourses.end()) {
        cout << "Error: Student " << studentID << " is not registered in course " << courseID << ".\n";
        return;
    }

    cout << "Enter Grade (0-100): ";
    cin >> grade;

    if (grade < 0 || grade > 100) {
        cout << "Invalid grade. Grade must be between 0 and 100.\n";
        return;
    }

    // Update the grades map
    student.setGrade(courseID, grade);
    cout << "Grade for student " << studentID << " in course " << courseID << " updated to " << grade << ".\n";
}




Administrator::Administrator() : User("", "") {} ////////////////////////////////////////////////////////////////////////////////////////


