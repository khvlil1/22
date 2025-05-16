#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void DataManager::loadAdmins(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Admins file not found, starting with empty list.\n";
        return;
    }
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string username, password, role;
        if (iss >> username >> password >> role) {
            Administrator admin(username, password);
            admin.setRole(role);  // Assuming Administrator inherits from User and has setRole
            admins[username] = admin;
        }
    }
    fin.close();
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
        // First line: student info
        vector<string> tokens;
        size_t pos = 0, prev = 0;
        while ((pos = line.find('|', prev)) != string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        tokens.push_back(line.substr(prev));
        if (tokens.size() < 8) continue;

        Student s;
        s.setStudentID(tokens[0]);
        s.setStudentName(tokens[1],tokens[2]);
        s.setEmail(tokens[3]);
        s.setPassword(tokens[4]);
        s.setAcademicYear(stoi(tokens[5]));
        s.setMajor(tokens[6]);
        s.setRole(tokens[7]); ////////////////////////////////////

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

        students[s.getEmail()] = s;
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
         const Student& s = pair.second;//email 

        // Student main info
        fout << s.getStudentID() << "|"
             << s.getStudentfName() << "|"
            << s.getStudentlName() << "|"
             << s.getEmail() << "|"
             << s.getPassword() << "|"
             << s.getAcademicYear() << "|"
             << s.getMajor() << "|"
             << s.getRole() << "\n"; // Save role//////////////////////////////////

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






