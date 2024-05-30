#include "mapset.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

std::string to_lowercase(const std::string& str) {
    std::string lowercase_str = str;
    std::for_each(lowercase_str.begin(), lowercase_str.end(), [](char& c) {
        c = std::tolower(static_cast<unsigned char>(c));
    });
    return lowercase_str;
}


