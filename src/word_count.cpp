#include "word_count.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

void to_lowercase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopwords_set;
    std::string word;
    while (stopwords >> word) {
        to_lowercase(word);
        stopwords_set.insert(word);
    }
    return stopwords_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;
    while (document >> word) {
        to_lowercase(word);
        if (!stopwords.count(word)) {
            word_counts[word]++;
        }
    }
    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& pair : word_counts) {
        output << pair.first << " " << pair.second << "\n";
    }
}

