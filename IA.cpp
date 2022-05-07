#include "IA.hpp"
#include <array>
#include <string>
#include <sstream>


IA::IA(const string patternFileName) {
    ifstream file(patternFileName);
    
    if (!file.is_open()) {
        cout << "could not open pattern file";
    }

    string pattern;
    while (getline(file >> ws, pattern, ',')){
        int score;
        if (file >> score) {
            patterns.push_back(pattern);
            patternScores.push_back(score);
        }
    }    
}
