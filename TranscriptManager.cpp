#include "TranscriptManager.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

TranscriptManager::TranscriptManager(const ModuleCatalog &catalog) : moduleCatalog(catalog) {}

bool TranscriptManager::loadGrades(const std::string &path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        return false;
    }

    std::string studentId;
    int termCode;
    std::string moduleCode;
    int mark;

    while (input >> studentId >> termCode >> moduleCode >> mark) {
        studentGrades[studentId][termCode].emplace_back(moduleCode, mark);
    }
    return true;
}

double TranscriptManager::calculateTermAverage(const std::string &studentId, int term, int &totalCredits) const {
    double weightedSum = 0.0;
    totalCredits = 0;
    auto studentIt = studentGrades.find(studentId);
    if (studentIt == studentGrades.end()) {
        return 0.0;
    }

    auto termIt = studentIt->second.find(term);
    if (termIt == studentIt->second.end()) {
        return 0.0;
    }

    for (const auto &entry : termIt->second) {
        int credit = 0;
        std::string moduleName;
        if (moduleCatalog.tryGetModuleInfo(entry.getModuleCode(), credit, moduleName)) {
            weightedSum += static_cast<double>(entry.getMark()) * static_cast<double>(credit);
            totalCredits += credit;
        }
    }

    if (totalCredits == 0) {
        return 0.0;
    }
    return weightedSum / static_cast<double>(totalCredits);
}

void TranscriptManager::printTranscript(const std::string &studentId, const std::optional<int> &termFilter) const {
    std::cout << "Student ID: " << studentId << '\n';

    auto studentIt = studentGrades.find(studentId);
    if (studentIt == studentGrades.end()) {
        std::cout << '\n';
        return;
    }

    double overallWeightedSum = 0.0;
    int overallCredits = 0;

    const auto &terms = studentIt->second;

    auto printTerm = [&](int termCode) {
        auto termIt = terms.find(termCode);
        if (termIt == terms.end()) {
            return;
        }

        std::cout << "  Term " << termCode << ":\n";
        for (const auto &entry : termIt->second) {
            int credit = 0;
            std::string moduleName;
            if (!moduleCatalog.tryGetModuleInfo(entry.getModuleCode(), credit, moduleName)) {
                continue;
            }
            std::cout << "    " << entry.getModuleCode() << ' ' << moduleName << " (" << credit << " credits): "
                      << entry.getMark() << '\n';
        }

        int termCredits = 0;
        double termAverage = calculateTermAverage(studentId, termCode, termCredits);
        std::cout << "  Term Average: " << std::fixed << std::setprecision(2) << termAverage << '\n';
        overallWeightedSum += termAverage * termCredits;
        overallCredits += termCredits;
    };

    if (termFilter.has_value()) {
        printTerm(*termFilter);
    } else {
        for (const auto &termPair : terms) {
            printTerm(termPair.first);
        }

        if (overallCredits > 0) {
            double overallAverage = overallWeightedSum / static_cast<double>(overallCredits);
            std::cout << "  Overall Average: " << std::fixed << std::setprecision(2) << overallAverage << '\n';
        }
    }

    std::cout << '\n';
}
