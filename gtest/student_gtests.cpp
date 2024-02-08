#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strdup) {
    char* duplicated = String::strdup("test");
    EXPECT_STREQ(duplicated, "test");
    delete[] duplicated;
}

TEST(StringFunction, strncpy) {
    char destination[10] = {};
    String::strncpy(destination, "hello", 5);
    EXPECT_STREQ(destination, "hello");
}

TEST(StringFunction, strcat) {
    char str[10] = "Hi";
    String::strcat(str, " there");
    EXPECT_STREQ(str, "Hi there");
}

TEST(StringFunction, strncat) {
    char str[10] = "Hi";
    String::strncat(str, " there", 3);
    EXPECT_STREQ(str, "Hi th");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("test", "test"), 0);
    EXPECT_LT(String::strcmp("aaa", "bbb"), 0);
    EXPECT_GT(String::strcmp("ccc", "bbb"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("Hello", "Hello", 5), 0);
    EXPECT_LT(String::strncmp("Hello", "World", 5), 0);
    EXPECT_GT(String::strncmp("World", "Hello", 5), 0);
    EXPECT_EQ(String::strncmp("Hello", "Helicopter", 3), 0);
    EXPECT_LT(String::strncmp("Hello", "Hello world", 20), 0);
    EXPECT_GT(String::strncmp("Hello world", "Hello", 20), 0);
    EXPECT_EQ(String::strncmp("", "", 5), 0);
    EXPECT_LT(String::strncmp("", "Hello", 5), 0);
    EXPECT_GT(String::strncmp("Hello", "", 5), 0);
}


TEST(StringFunction, reverse_cpy) {
    char reversed[6];
    String::reverse_cpy(reversed, "hello");
    EXPECT_STREQ(reversed, "olleh");
}

TEST(StringFunction, strchr) {
    const char* str = "Hello world";
    EXPECT_EQ(String::strchr(str, 'w'), str + 6);
    EXPECT_EQ(String::strchr(str, 'z'), nullptr);
}

TEST(StringFunction, strstr) {
    const char* haystack = "Hello world";
    EXPECT_EQ(String::strstr(haystack, "Hello"), haystack);
    EXPECT_EQ(String::strstr(haystack, "lo wo"), haystack + 3);
    EXPECT_EQ(String::strstr(haystack, "world"), haystack + 6);
    EXPECT_EQ(String::strstr(haystack, "xyz"), nullptr);
    EXPECT_EQ(String::strstr(haystack, ""), haystack);
    EXPECT_EQ(String::strstr(haystack, "Hello world!"), nullptr);
}


