#include <gtest/gtest.h>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);
}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>)

TEST(ListTests, Reverse) {
    Node* const head = list::from_string("racecar");
    Node* const expectedReversedHead = list::from_string("racecar");
    Node* const reversedHead = list::reverse(head);
    EXPECT_EQ(list::compare(reversedHead, expectedReversedHead), 0);
    list::free(head);
    list::free(expectedReversedHead);
    list::free(reversedHead);
    Node* const singleElementHead = list::from_string("r");
    Node* const reversedSingleElementHead = list::reverse(singleElementHead);
    EXPECT_EQ(list::compare(reversedSingleElementHead, singleElementHead), 0);
    list::free(reversedSingleElementHead);
    list::free(singleElementHead);
}

TEST(ListChecks, Concatenating) {
    Node* const alpha = list::from_string("dog");
    Node* const beta = list::from_string("dog");
    Node* const gamma = list::append(alpha, beta);
    Node* const delta = list::append(alpha, alpha);
    ASSERT_EQ(list::compare(gamma, delta), 0);
    list::free(alpha);
    list::free(beta);
    list::free(gamma);
    list::free(delta);
    Node* const epsilon = list::from_string("cat");
    Node* const zeta = list::from_string("meow");
    Node* const eta = list::append(epsilon, zeta);
    Node* const theta = list::from_string("meowcat");
    ASSERT_EQ(list::compare(eta, theta), 0);
    list::free(epsilon);
    list::free(zeta);
    list::free(eta);
    list::free(theta);
}


