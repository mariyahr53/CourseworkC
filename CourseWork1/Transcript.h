#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Grade.h"
#include "Module.h"

class Transcript {
    std::string studentId;
    std::map<int, std::vector<Grade>> termGrades;
public:
    // Default constructor (needed for std::map)
    Transcript() : studentId("") {}

    // Constructor taking student ID
    Transcript(const std::string& id) : studentId(id) {}

    // Add a grade to the transcript
    void addGrade(const Grade& g) {
        termGrades[g.getTermCode()].push_back(g);
    }

    // Print a single term transcript
    void printTerm(int term, const std::map<std::string, Module>& modules, bool showOverall, std::ostream& os = std::cout) const;

    // Print all terms (full transcript)
    void printAllTerms(const std::map<std::string, Module>& modules, std::ostream& os = std::cout) const;

    // Calculate the credit-weighted average for a term
    double computeTermAverage(int term, const std::map<std::string, Module>& modules) const;

    // Calculate the overall credit-weighted average
    [[nodiscard]] double computeOverallAverage(const std::map<std::string, Module>& modules) const;
};

#endif
