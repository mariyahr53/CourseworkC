#ifndef TRANSCRIPTMANAGER_H
#define TRANSCRIPTMANAGER_H

#include "GradeEntry.h"
#include "ModuleCatalog.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

class TranscriptManager {
private:
    ModuleCatalog moduleCatalog;
    std::map<std::string, std::map<int, std::vector<GradeEntry>>> studentGrades;

    double calculateTermAverage(const std::string &studentId, int term, int &totalCredits) const;

public:
    explicit TranscriptManager(const ModuleCatalog &catalog);

    bool loadGrades(const std::string &path);
    void printTranscript(const std::string &studentId, const std::optional<int> &termFilter) const;
};

#endif
