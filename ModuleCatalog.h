#ifndef MODULECATALOG_H
#define MODULECATALOG_H

#include <map>
#include <string>

class ModuleDetail {
private:
    int credit;
    std::string name;

public:
    ModuleDetail();
    ModuleDetail(int credit, const std::string &name);

    int getCredit() const;
    const std::string &getName() const;
};

class ModuleCatalog {
private:
    std::map<std::string, ModuleDetail> modules;

public:
    bool loadFromFile(const std::string &path);
    bool tryGetModuleInfo(const std::string &moduleCode, int &creditOut, std::string &nameOut) const;
};

#endif
