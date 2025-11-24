#ifndef GRADE_H
#define GRADE_H

#include <string>

class Grade {
    std::string studentId;
    int termCode;
    std::string moduleCode;
    int mark;
public:
    Grade(const std::string& id, int term, const std::string& mod, int m)
        : studentId(id), termCode(term), moduleCode(mod), mark(m) {}

    std::string getStudentId() const { return studentId; }
    int getTermCode() const { return termCode; }
    std::string getModuleCode() const { return moduleCode; }
    int getMark() const { return mark; }
};

#endif
