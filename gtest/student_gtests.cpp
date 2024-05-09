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

TEST(ListTests, Appending) {
    Node* const a = list::from_string("i");
    Node* const b = list::from_string("i");
    Node* const c = list::append(a, b);
    Node* const d = list::append(a, a);

    EXPECT_EQ(list::compare(c, d), 0);
    list::free(a);
    list::free(b);
    list::free(c);
    list::free(d);

    Node* const e = list::from_string("some");
    Node* const f = list::from_string("thing");
    Node* const g = list::append(e, f);
    Node* const h = list::from_string("something");

    EXPECT_EQ(list::compare(g, h), 0);
    list::free(e);
    list::free(f);
    list::free(g);
    list::free(h);
}
