#pragma once
#include <unordered_map>
#include <string>
#include "Student.h"
#include "Administrator.h"
#include "Course.h"

class DataManager {
private:
    std::unordered_map<std::string, Administrator> admins;
    std::unordered_map<std::string, Student> students;
    std::unordered_map<std::string, Course> courses;

public:
    void loadAdmins(const std::string& filename);
    void loadCourses(const std::string& filename);
    void loadStudents(const std::string& filename);

    void saveAdmins(const std::string& filename) const;
    void saveCourses(const std::string& filename) const;
    void saveStudents(const std::string& filename) const;

    std::unordered_map<std::string, Administrator>& getAdmins() { return admins; }
    std::unordered_map<std::string, Student>& getStudents() { return students; }
    std::unordered_map<std::string, Course>& getCourses() { return courses; }

};
