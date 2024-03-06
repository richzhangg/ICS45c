#include "mapset.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <iostream>

std::string to_lowercase(const std::string& str) {
    std::string lower_case_str;
    std::transform(str.begin(), str.end(), std::back_inserter(lower_case_str),
                   [](unsigned char c) { return std::tolower(c); });
    return lower_case_str;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopwords_set;
    std::string word;
    while (stopwords >> word) {
        stopwords_set.insert(to_lowercase(word));
    }
    return stopwords_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;
    while (document >> word) {
        word = to_lowercase(word);
        word.erase(std::remove_if(word.begin(), word.end(), 
                                  [](char c) { return !std::isalpha(c); }), word.end());
        if (stopwords.find(word) == stopwords.end() && !word.empty()) {
            ++word_counts[word];
        }
    }
    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << '\n';
    }
}

