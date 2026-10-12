#pragma once
#include <string>
#include <vector>

struct Contact {
    int id;
    std::string name;
    std::string email; // YENI: E-posta alani
    
    std::vector<std::string> tags; 

    int totalScore = 0;
    int ratingCount = 0;

    double average() const {
        if (ratingCount == 0) return 0.0;
        return static_cast<double>(totalScore) / ratingCount;
    }
};