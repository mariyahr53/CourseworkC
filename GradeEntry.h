#ifndef GRADEENTRY_H
#define GRADEENTRY_H

#include <string>

class GradeEntry {
private:
    std::string moduleCode;
    int mark;

public:
    GradeEntry(const std::string &moduleCode, int mark);

    const std::string &getModuleCode() const;
    int getMark() const;
};

#endif
