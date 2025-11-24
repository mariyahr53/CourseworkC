#include "ModuleCatalog.h"

#include <fstream>
#include <sstream>

ModuleDetail::ModuleDetail() : credit(0), name("") {}

ModuleDetail::ModuleDetail(int credit, const std::string &name) : credit(credit), name(name) {}

int ModuleDetail::getCredit() const {
    return credit;
}

const std::string &ModuleDetail::getName() const {
    return name;
}

bool ModuleCatalog::loadFromFile(const std::string &path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        return false;
    }

    std::string moduleCode;
    int credit;
    std::string moduleName;
    while (input >> moduleCode >> credit >> moduleName) {
        modules[moduleCode] = ModuleDetail(credit, moduleName);
    }
    return true;
}

bool ModuleCatalog::tryGetModuleInfo(const std::string &moduleCode, int &creditOut, std::string &nameOut) const {
    auto it = modules.find(moduleCode);
    if (it == modules.end()) {
        return false;
    }

    creditOut = it->second.getCredit();
    nameOut = it->second.getName();
    return true;
}
