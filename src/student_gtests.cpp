#include <gtest/gtest.h>
#include <sstream>
#include "word_count.hpp"
using namespace std;

TEST(WordCount, ToLowercase) {
    // Your test for to_lowercase
	std::string test_str = "HeLLo WoRLd";
    to_lowercase(test_str);
    EXPECT_EQ(test_str, "hello world");
}

TEST(WordCount, LoadStopWords) {
    // Your test for load_stopwords
	std::istringstream test_input("hello\nworld\n");
    auto stopwords = load_stopwords(test_input);
    EXPECT_TRUE(stopwords.find("hello") != stopwords.end());
    EXPECT_TRUE(stopwords.find("world") != stopwords.end());
    EXPECT_FALSE(stopwords.find("test") != stopwords.end());
}

TEST(WordCount, CountWords) {
    // Your test for count_words
	std::istringstream test_input("apple apple banana apple cherry banana");
    std::set<std::string> stopwords = {"banana"};
    auto word_counts = count_words(test_input, stopwords);

    EXPECT_EQ(word_counts["apple"], 3);
    EXPECT_EQ(word_counts["cherry"], 1);
    EXPECT_EQ(word_counts.count("banana"), 0);
}

TEST(WordCount, OutputWordCounts) {
    // Your test for output_word_counts
	std::map<std::string, int> word_counts = {{"apple", 3}, {"cherry", 1}};
    std::ostringstream test_output;
    output_word_counts(word_counts, test_output);

    std::string expected_output = "apple 3\ncherry 1\n";
    EXPECT_EQ(test_output.str(), expected_output);
}

