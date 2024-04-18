#include <iostream>
#include "word_count.hpp"
using namespace std;

void to_lowercase(std::string& str) {
	for (char &c : str) {
        c = tolower(c);
    }
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
	set<string> sw;
    string word;
    while (stopwords >> word) {
        to_lowercase(word);
        sw.insert(word);
    }
    return sw;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
	map<string, int> counts;
    string token;
    while (document >> token) {
        to_lowercase(token);
        if (!stopwords.count(token)) {
            counts[token]++;
        }
    }
    return counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
	for (const auto& pair : word_counts) {
        output << pair.first << " " << pair.second << endl;
    }
}
