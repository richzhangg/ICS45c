#include <gtest/gtest.h>
#include <sstream>
#include "word_count.hpp"
using namespace std;

TEST(WordCount, ToLowercase) {
    // Your test for to_lowercase
	std::string test_str1 = "HeLLo WoRLd";
    to_lowercase(test_str1);
    EXPECT_EQ(test_str1, "hello world");

    std::string test_str2 = "1234 !@#$";
    to_lowercase(test_str2);
    EXPECT_EQ(test_str2, "1234 !@#$");

    std::string test_str3 = "";
    to_lowercase(test_str3);
    EXPECT_EQ(test_str3, "");
}

TEST(WordCount, LoadStopWords) {
    // Your test for load_stopwords
	std::istringstream test_input1("hello\nworld\n");
    auto stopwords1 = load_stopwords(test_input1);
    EXPECT_TRUE(stopwords1.find("hello") != stopwords1.end());
    EXPECT_TRUE(stopwords1.find("world") != stopwords1.end());
    EXPECT_FALSE(stopwords1.find("test") != stopwords1.end());

    std::istringstream test_input2("");
    auto stopwords2 = load_stopwords(test_input2);
    EXPECT_TRUE(stopwords2.empty());

    std::istringstream test_input3("Hello\nWorld\n");
    auto stopwords3 = load_stopwords(test_input3);
    EXPECT_TRUE(stopwords3.find("hello") != stopwords3.end());
    EXPECT_TRUE(stopwords3.find("world") != stopwords3.end());
}

TEST(WordCount, CountWords) {
    // Your test for count_words
    std::istringstream test_input1("apple apple banana apple cherry banana");
    std::set<std::string> stopwords1 = {"banana"};
    auto word_counts1 = count_words(test_input1, stopwords1);
    EXPECT_EQ(word_counts1["apple"], 3);
    EXPECT_EQ(word_counts1["cherry"], 1);
    EXPECT_EQ(word_counts1.count("banana"), 0);

    std::istringstream test_input2("");
    auto word_counts2 = count_words(test_input2, stopwords1);
    EXPECT_TRUE(word_counts2.empty());

    std::istringstream test_input3("banana banana banana");
    auto word_counts3 = count_words(test_input3, stopwords1);
    EXPECT_TRUE(word_counts3.empty());

    std::istringstream test_input4("apple! cherry? apple;");
    auto word_counts4 = count_words(test_input4, {});
    EXPECT_EQ(word_counts4["apple!"], 2);
    EXPECT_EQ(word_counts4["cherry?"], 1);
}

TEST(WordCount, OutputWordCounts) {
    // Your test for output_word_counts
	std::map<std::string, int> word_counts1 = {{"apple", 3}, {"cherry", 1}};
    std::ostringstream test_output1;
    output_word_counts(word_counts1, test_output1);
    std::string expected_output1 = "apple 3\ncherry 1\n";
    EXPECT_EQ(test_output1.str(), expected_output1);

    std::map<std::string, int> word_counts2;
    std::ostringstream test_output2;
    output_word_counts(word_counts2, test_output2);
    EXPECT_TRUE(test_output2.str().empty());

    std::map<std::string, int> word_counts3 = {{"apple!", 2}, {"cherry?", 1}};
    std::ostringstream test_output3;
    output_word_counts(word_counts3, test_output3);
    std::string expected_output3 = "apple! 2\ncherry? 1\n";
    EXPECT_EQ(test_output3.str(), expected_output3);
}

