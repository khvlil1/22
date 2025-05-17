#include "Administrator.h"
#include "User.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;





Administrator::Administrator() : User("", "", "") {}
Administrator::Administrator(const string& username, const string& password, const string& role) : User(username, password, role) {}

void Administrator::assignGradeToStudent(Student& student, const std::string& courseID, float grade) const {
    student.grades[courseID] = grade; // direct access as friend
}




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
    string courseID;
    cout << "Enter Course ID to set prerequisites: ";
    cin.ignore(); // Clear input buffer
    getline(cin, courseID);

    unordered_map<string, Course>& updatedCourses = getCourses();

    // Check if the entered course ID exists
    if (updatedCourses.find(courseID) != updatedCourses.end()) {
        Course& currentCourse = updatedCourses[courseID];

        vector<string> prerequisites;
        cout << "Enter prerequisite course IDs (type 'done' when finished):\n";

        string prereqID;
        while (true) {
            getline(cin, prereqID);
            if (prereqID == "done") break;

            // Check if the prerequisite ID exists in the courses map
            if (updatedCourses.find(prereqID) != updatedCourses.end()) {
                prerequisites.push_back(prereqID);
                cout << "Added prerequisite with ID: " << prereqID << endl;
            }
            else {
                cout << "Warning: Course ID '" << prereqID << "' not found. Prerequisite not added." << endl;
            }
        }

        currentCourse.setPrerequisites(prerequisites);
        setCourses(updatedCourses);
        cout << "Prerequisites for course with ID '" << courseID << "' set successfully.\n";

        // Debug output
        cout << "Course " << courseID << " now has the following prerequisites: " << endl;
        for (const string& p : prerequisites) {
            // Ensure the course ID exists
            if (updatedCourses.find(p) != updatedCourses.end()) {
                cout << "- " << updatedCourses[p].getCourseName() << " (ID: " << p << ")" << endl;
            }
        }
    }
    else {
        cout << "Course with ID '" << courseID << "' not found.\n";
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

    Student& student = studentIt->second;

    // Get student's registered courses
    auto registeredCourses = student.registeredCourses;  // Access directly via friend privilege
    if (registeredCourses.empty()) {
        cout << "No courses registered by this student.\n";
        return;
    }

    cout << "Courses registered by student " << studentID << ":\n";
    for (const auto& pair : registeredCourses) {
        cout << "ID: " << pair.first << ", Name: " << pair.second.getCourseName() << "\n";
    }

    cout << "Enter Course ID: ";
    cin >> courseID;

    if (availableCourses.find(courseID) == availableCourses.end()) {
        cout << "Error: Course with ID '" << courseID << "' not found in available courses.\n";
        return;
    }

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

    //  Directly update the grades map (using friend access)
    student.grades[courseID] = grade;

    cout << "Grade for student " << studentID << " in course " << courseID << " updated to " << grade << ".\n";
}




