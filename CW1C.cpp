#include "ModuleCatalog.h"
#include "TranscriptManager.h"

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

int main() {
    ModuleCatalog catalog;
    if (!catalog.loadFromFile("modules.txt")) {
        std::cerr << "Failed to open modules.txt" << std::endl;
        return 1;
    }

    TranscriptManager manager(catalog);
    if (!manager.loadGrades("grades.txt")) {
        std::cerr << "Failed to open grades.txt" << std::endl;
        return 1;
    }

    std::ifstream requestsFile("requests.txt");
    if (!requestsFile.is_open()) {
        std::cerr << "Failed to open requests.txt" << std::endl;
        return 1;
    }

    std::string line;
    bool firstOutput = true;
    while (std::getline(requestsFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string studentId;
        int termCode;

        if (!(ss >> studentId)) {
            continue;
        }

        std::optional<int> termFilter;
        if (ss >> termCode) {
            termFilter = termCode;
        }

        if (!firstOutput) {
            std::cout << '\n';
        }
        firstOutput = false;

        manager.printTranscript(studentId, termFilter);
    }

    return 0;
}
