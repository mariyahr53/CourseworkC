#include "GradeEntry.h"

GradeEntry::GradeEntry(const std::string &moduleCode, int mark)
    : moduleCode(moduleCode), mark(mark) {}

const std::string &GradeEntry::getModuleCode() const {
    return moduleCode;
}

int GradeEntry::getMark() const {
    return mark;
}
