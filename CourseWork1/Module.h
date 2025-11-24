#ifndef MODULE_H
#define MODULE_H

#include <string>

class Module {
    std::string code;
    int credit;
    std::string name;
public:
    Module() : code(""), credit(0), name("") {}
    Module(const std::string& c, int cr, const std::string& n)
        : code(c), credit(cr), name(n) {}

    std::string getCode() const { return code; }
    int getCredit() const { return credit; }
    std::string getName() const { return name; }
};

#endif
