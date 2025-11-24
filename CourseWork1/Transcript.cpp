#include "Transcript.h"
#include <iostream>
#include <iomanip>

void Transcript::printTerm(int term, const std::map<std::string, Module>& modules, bool showOverall, std::ostream& os) const {
    auto it = termGrades.find(term);
    if (it == termGrades.end()) return;

    os << "  Term " << term << ":\n";
    double weightedSum = 0.0;
    int totalCredits = 0;
    for (const Grade& g : it->second) {
        auto modIt = modules.find(g.getModuleCode());
        if (modIt != modules.end()) {
            os << "    " << g.getModuleCode() << " "
               << modIt->second.getName() << " ("
               << modIt->second.getCredit() << " credits): "
               << g.getMark() << "\n";
            weightedSum += g.getMark() * modIt->second.getCredit();
            totalCredits += modIt->second.getCredit();
        }
    }
    double avg = totalCredits ? weightedSum / totalCredits : 0.0;
    os << "  Term Average: " << std::fixed << std::setprecision(2) << avg << "\n";
    if (showOverall) {
        double overall = computeOverallAverage(modules);
        os << "  Overall Average: " << std::fixed << std::setprecision(2) << overall << "\n";
    }
}

void Transcript::printAllTerms(const std::map<std::string, Module>& modules, std::ostream& os) const {
    for (const auto& pair : termGrades) {
        printTerm(pair.first, modules, false, os);
    }
    double overall = computeOverallAverage(modules);
    os << "  Overall Average: " << std::fixed << std::setprecision(2) << overall << "\n";
}

double Transcript::computeTermAverage(int term, const std::map<std::string, Module>& modules) const {
    auto it = termGrades.find(term);
    if (it == termGrades.end()) return 0.0;
    double sum = 0;
    int credits = 0;
    for (const Grade& g : it->second) {
        auto mit = modules.find(g.getModuleCode());
        if (mit != modules.end()) {
            sum += g.getMark() * mit->second.getCredit();
            credits += mit->second.getCredit();
        }
    }
    return credits ? sum / credits : 0.0;
}

double Transcript::computeOverallAverage(const std::map<std::string, Module>& modules) const {
    double sum = 0;
    int credits = 0;
    for (const auto& termPair : termGrades) {
        for (const Grade& g : termPair.second) {
            auto mit = modules.find(g.getModuleCode());
            if (mit != modules.end()) {
                sum += g.getMark() * mit->second.getCredit();
                credits += mit->second.getCredit();
            }
        }
    }
    return credits ? sum / credits : 0.0;
}
