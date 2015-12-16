#include "split.hpp"

//---------------------------------------------------------------------------------+
// vector<string> Split (single char delimiter)                                    |
// Split a string by a given delimiter using find and substr                       |
//---------------------------------------------------------------------------------+
std::vector<std::string> Split(std::string haystack, char delimiter) {
    std::vector<std::string> result;
    std::string part;

    int pos = haystack.find(delimiter);
    while (pos != std::string::npos) {
        part = haystack.substr(0, pos);
        haystack = haystack.substr(pos + 1, std::string::npos);
        if (pos != 0 && part.length() != 0) {
            result.push_back(part);
        }
        pos = haystack.find(delimiter);
    }
    if (haystack.length() != 0) {
        result.push_back(haystack);
    }

    return result;
}

//---------------------------------------------------------------------------------+
// vector<string> Split (single const char* delimiter)                             |
// Split a string by a given delimiter using find and substr                       |
//---------------------------------------------------------------------------------+
std::vector<std::string> Split(std::string haystack, const char* delimiter) {
    std::vector<std::string> result;
    std::string part;

    int pos = haystack.find(delimiter);
    while (pos != std::string::npos) {
        part = haystack.substr(0, pos);
        haystack = haystack.substr(pos + strlen(delimiter), std::string::npos);
        if (pos != 0 && part.length() != 0) {
            result.push_back(part);
        }
        pos = haystack.find(delimiter);
    }
    if (haystack.length() != 0) {
        result.push_back(haystack);
    }

    return result;
}
