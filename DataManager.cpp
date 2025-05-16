#include "DataManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

DataManager& DataManager::getInstance() {
    static DataManager instance;  // Created once, lives for the lifetime of the program
    return instance;
}
void DataManager::loadAdmins(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cout << "Admin file not found. Creating default admin.\n";
        admins["admin"] = Administrator("admin", "admin", "A");
        return;
    }

    std::string username, password, role;
    while (inFile >> username >> password >> role) {
        if (admins.empty()) { // Allow only one admin
            admins[username] = Administrator(username, password, role);
        }
    }
}



void DataManager::loadCourses(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Courses file not found, starting empty.\n";
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string courseID, courseName, creditHoursStr, instructor, syllabus;

        // Split line by '|'
        size_t pos = 0, prev = 0;
        vector<string> tokens;
        while ((pos = line.find('|', prev)) != string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        tokens.push_back(line.substr(prev));
        if (tokens.size() < 5) continue; // invalid line

        courseID = tokens[0];
        courseName = tokens[1];
        int creditHours = stoi(tokens[2]);
        instructor = tokens[3];
        syllabus = tokens[4];

        Course c;
        c.setCourseID(courseID);
        c.setCourseName(courseName);
        c.setCreditHours(creditHours);
        c.setInstructor(instructor);
        c.setSyllabus(syllabus);

        // Next line: prerequisites
        if (getline(fin, line)) {
            vector<string> prereqs;
            istringstream preiss(line);
            string prereq;
            while (getline(preiss, prereq, ',')) {
                if (!prereq.empty()) prereqs.push_back(prereq);
            }
            c.setPrerequisites(prereqs);
        }
        courses[courseID] = c;
    }
    fin.close();
}

void DataManager::loadStudents(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Students file not found, starting empty.\n";
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // First line: student info (format updated to include username)
        // Format example:
        // studentID|username|firstName|lastName|email|password|academicYear|major|role
        vector<string> tokens;
        size_t pos = 0, prev = 0;
        while ((pos = line.find('|', prev)) != string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        tokens.push_back(line.substr(prev));
        if (tokens.size() < 9) continue;  // expect at least 9 fields now

        Student s;
        s.setStudentID(tokens[0]);
        s.setUsername(tokens[1]);            // New: set username
        s.setStudentName(tokens[2], tokens[3]);
        s.setEmail(tokens[4]);
        s.setPassword(tokens[5]);
        s.setAcademicYear(stoi(tokens[6]));
        s.setMajor(tokens[7]);
        s.setRole(tokens[8]);

        // Registered courses (next line)
        unordered_map<string, Course> regCourses;
        if (getline(fin, line)) {
            istringstream iss(line);
            string courseID;
            while (getline(iss, courseID, ',')) {
                if (!courseID.empty() && courses.find(courseID) != courses.end()) {
                    regCourses[courseID] = courses[courseID];
                }
            }
            s.setRegisteredCourses(regCourses);
        }

        // Grades (next line)
        unordered_map<string, float> grades;
        if (getline(fin, line)) {
            istringstream iss(line);
            string pair;
            while (getline(iss, pair, ',')) {
                size_t colonPos = pair.find(':');
                if (colonPos != string::npos) {
                    string cID = pair.substr(0, colonPos);
                    float grade = stof(pair.substr(colonPos + 1));
                    grades[cID] = grade;
                }
            }
            for (auto& g : grades) {
                s.setGrade(g.first, g.second);
            }
        }

        students[s.getUsername()] = s;  // Key by username now
    }
    fin.close();
}








void DataManager::saveAdmins(const string& filename) const {
    ofstream fout(filename);
    for (const auto& pair : admins) {
        const Administrator& admin = pair.second;
        fout << admin.getUsername() << " "
            << admin.getPassword() << " "
            << admin.getRole() << "\n"; // Save role
    }
    fout.close();
}


void DataManager::saveCourses(const string& filename) const {
    ofstream fout(filename);
    for (const auto& pair : courses) {
        const Course& c = pair.second;
        fout << c.getCourseID() << "|"
            << c.getCourseName() << "|"
            << c.getCreditHours() << "|"
            << c.getInstructor() << "|"
            << c.getSyllabus() << "\n";

        const vector<string>& prereqs = c.getPrerequisites();
        for (size_t i = 0; i < prereqs.size(); ++i) {
            fout << prereqs[i];
            if (i != prereqs.size() - 1) fout << ",";
        }
        fout << "\n";
    }
    fout.close();
}

void DataManager::saveStudents(const string& filename) const {
    ofstream fout(filename);
    for (const auto& pair : students) {
        const Student& s = pair.second;

        // Save all info including username after studentID
        fout << s.getStudentID() << "|"
            << s.getUsername() << "|"
            << s.getStudentfName() << "|"
            << s.getStudentlName() << "|"
            << s.getEmail() << "|"
            << s.getPassword() << "|"
            << s.getAcademicYear() << "|"
            << s.getMajor() << "|"
            << s.getRole() << "\n";

        // Registered courses
        const auto& regCourses = s.getRegisteredCourses();
        for (auto it = regCourses.begin(); it != regCourses.end(); ++it) {
            fout << it->first;
            if (next(it) != regCourses.end()) fout << ",";
        }
        fout << "\n";

        // Grades
        const auto& grades = s.getGrades();
        for (auto it = grades.begin(); it != grades.end(); ++it) {
            fout << it->first << ":" << it->second;
            if (next(it) != grades.end()) fout << ",";
        }
        fout << "\n";
    }
    fout.close();
}

