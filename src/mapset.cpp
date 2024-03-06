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
    std::set<std::string> stopwords_set(
        (std::istream_iterator<std::string>(stopwords)),
        std::istream_iterator<std::string>());

    std::set<std::string> lower_stopwords;
    std::transform(stopwords_set.begin(), stopwords_set.end(),
                   std::inserter(lower_stopwords, lower_stopwords.end()),
                   to_lowercase);
    return lower_stopwords;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::for_each(std::istream_iterator<std::string>(document), std::istream_iterator<std::string>(),[&word_counts, &stopwords](const std::string& word) {
					  std::string lower_word = to_lowercase(word);
                      lower_word.erase(std::remove_if(lower_word.begin(), lower_word.end(), 
                                                      [](char c) { return !std::isalpha(c); }), lower_word.end());
                      if (stopwords.find(lower_word) == stopwords.end() && !lower_word.empty()) {
                          ++word_counts[lower_word];
                      }
                  });
    return word_counts;
}


void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << '\n';
    }
}

