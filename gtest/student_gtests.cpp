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
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncpy) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strcat) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncat) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strcmp) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncmp) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, reverse_cpy) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strchr) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strstr) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strdup_BasicUsage) {
    const char* original = "Hello, World!";
    char* duplicate = String::strdup(original);

    // Test if the duplicate is not the same memory location as the original
    EXPECT_NE(duplicate, original);
    // Test if the contents are the same
    EXPECT_STREQ(duplicate, original);
    // Clean up
    delete[] duplicate;
}

TEST(StringFunction, strncpy_EdgeCase) {
    char dest[6] = {}; // Ensure it's large enough and initialized to zeros
    const char* src = "Hello";
    String::strncpy(dest, src, 5);
    EXPECT_STREQ(dest, "Hello");

    // Edge case: strncpy with n less than the src length
    char dest2[4] = {};
    String::strncpy(dest2, src, 3);
    EXPECT_STREQ(dest2, "Hel");

    // Ensure dest is null-terminated when src length is greater than n
    char dest3[4] = {};
    String::strncpy(dest3, src, 3);
    EXPECT_EQ(dest3[3], '\0');
}

TEST(StringFunction, strcat_Basic) {
    char dest[11] = "Hello";
    String::strcat(dest, ", World");
    EXPECT_STREQ(dest, "Hello, World");
}

TEST(StringFunction, strncat_Basic) {
    char dest[11] = "Hello";
    String::strncat(dest, ", World", 6);
    // Only ", Wor" should be concatenated due to the length limit
    EXPECT_STREQ(dest, "Hello, Wor");
}

TEST(StringFunction, strcmp_Basic) {
    EXPECT_EQ(String::strcmp("abc", "abc"), 0);
    EXPECT_LT(String::strcmp("abc", "bcd"), 0);
    EXPECT_GT(String::strcmp("bcd", "abc"), 0);
}

TEST(StringFunction, strncmp_Basic) {
    EXPECT_EQ(String::strncmp("abcde", "abcff", 3), 0);
    EXPECT_LT(String::strncmp("abc", "bcd", 2), 0);
    EXPECT_GT(String::strncmp("bcd", "abc", 2), 0);
}

