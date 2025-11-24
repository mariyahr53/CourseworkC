#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include "Module.h"
#include "Grade.h"
#include "Transcript.h"

int main() {
    std::map<std::string, Module> modules;
    std::ifstream modFile("modules.txt");
    std::string line;
    while (std::getline(modFile, line)) {
        std::istringstream iss(line);
        std::string code, name;
        int credit;
        iss >> code >> credit >> name;
        modules[code] = Module(code, credit, name);
    }

    std::map<std::string, Transcript> transcripts;
    std::ifstream gradeFile("grades.txt");
    while (std::getline(gradeFile, line)) {
        std::istringstream iss(line);
        std::string id, module;
        int term, mark;
        iss >> id >> term >> module >> mark;
        if (transcripts.find(id) == transcripts.end()) {
            transcripts[id] = Transcript(id);
        }
        transcripts[id].addGrade(Grade(id, term, module, mark));
    }

    std::ifstream reqFile("requests.txt");
    while (std::getline(reqFile, line)) {
        std::istringstream iss(line);
        std::string id;
        int term = -1;
        iss >> id;
        if (!(iss >> term)) {
            // No term: full transcript
            std::cout << "Student ID: " << id << "\n";
            if (transcripts.find(id) != transcripts.end()) {
                transcripts[id].printAllTerms(modules);
            }
        } else {
            // Term-specific transcript
            std::cout << "Student ID: " << id << "\n";
            if (transcripts.find(id) != transcripts.end()) {
                transcripts[id].printTerm(term, modules, false);
            }
        }
    }
    return 0;
}
