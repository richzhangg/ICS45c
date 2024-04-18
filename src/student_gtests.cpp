#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

using namespace std;

TEST(WordCount, ToLowercase) {
    std::string test_str1 = "MixedCase";
    to_lowercase(test_str1);
    EXPECT_EQ(test_str1, "mixedcase");

    std::string test_str2 = "UPPERCASE";
    to_lowercase(test_str2);
    EXPECT_EQ(test_str2, "uppercase");

    std::string test_str3 = "UPPER";
    to_lowercase(test_str3);
    EXPECT_EQ(test_str3, "upper");
}

TEST(WordCount, LoadStopWords) {
    std::istringstream test_input1("a\nan\nthe\n");
    auto stopwords1 = load_stopwords(test_input1);
    EXPECT_EQ(stopwords1.size(), 3);
    EXPECT_NE(stopwords1.find("a"), stopwords1.end());

    std::istringstream test_input2("And\nBut\nOr\n");
    auto stopwords2 = load_stopwords(test_input2);
    EXPECT_EQ(stopwords2.size(), 3);
    EXPECT_NE(stopwords2.find("and"), stopwords2.end());
    EXPECT_EQ(stopwords2.find("however"), stopwords2.end());

    std::istringstream test_input3("and\nAND\nAnD\n");
    auto stopwords3 = load_stopwords(test_input3);
    EXPECT_EQ(stopwords3.size(), 1);
}

TEST(WordCount, CountWords) {
    std::istringstream test_input1("This is a simple test, a simple test this is.");
    std::set<std::string> stopwords1 = {"is", "a", "this"};
    auto word_counts1 = count_words(test_input1, stopwords1);
    EXPECT_EQ(word_counts1["simple"], 2);
    EXPECT_EQ(word_counts1["test"], 2);
    EXPECT_EQ(word_counts1.count("this"), 0);

    std::istringstream test_input2("Word! Word. Word,");
    std::set<std::string> stopwords2;
    auto word_counts2 = count_words(test_input2, stopwords2);
    EXPECT_EQ(word_counts2["word!"], 1);
    EXPECT_EQ(word_counts2["word."], 1);
    EXPECT_EQ(word_counts2["word,"], 1);

    std::istringstream test_input3("1234, 1234! #$%^&*");
    auto word_counts3 = count_words(test_input3, stopwords2);
    EXPECT_EQ(word_counts3["1234,"], 1);
    EXPECT_EQ(word_counts3["1234!"], 1);
    EXPECT_EQ(word_counts3["#$%^&*"], 1);
}

TEST(WordCount, OutputWordCounts) {
    std::map<std::string, int> word_counts1 = {{"test", 2}, {"word", 1}};
    std::ostringstream test_output1;
    output_word_counts(word_counts1, test_output1);
    std::string expected_output1 = "test 2\nword 1\n";
    EXPECT_EQ(test_output1.str(), expected_output1);

    std::map<std::string, int> word_counts2;
    std::ostringstream test_output2;
    output_word_counts(word_counts2, test_output2);
    EXPECT_TRUE(test_output2.str().empty());

	std::map<std::string, int> word_counts3 = {{"!test!", 2}, {"#word#", 1}};
    std::ostringstream test_output3;
    output_word_counts(word_counts3, test_output3);
    std::string expected_output3 = "!test! 2\n#word# 1\n";
    EXPECT_EQ(test_output3.str(), expected_output3);
}

