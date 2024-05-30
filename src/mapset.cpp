#include "mapset.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <map>
#include <set>
#include <iterator>
#include <iosfwd>

std::string to_lowercase(const std::string& str) {
    std::string lowercase_str = str;
    std::for_each(lowercase_str.begin(), lowercase_str.end(), [](char& c) {
        c = std::tolower(static_cast<unsigned char>(c));
    });
    return lowercase_str;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopword_set;
    std::for_each(std::istream_iterator<std::string>(stopwords), std::istream_iterator<std::string>(), 
                  [&](const std::string& word) { stopword_set.insert(to_lowercase(word)); });
    return stopword_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_count;
    std::istream_iterator<std::string> start(document), end;

    std::for_each(start, end, [&](const std::string& word) {
        std::string lower_word = to_lowercase(word);
        if (stopwords.find(lower_word) == stopwords.end()) {
            ++word_count[lower_word];
        }
    });

    return word_count;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    std::for_each(word_counts.begin(), word_counts.end(), [&output](const std::pair<std::string, int>& word_count) {
        output << word_count.first << " " << word_count.second << std::endl;
    });
}
