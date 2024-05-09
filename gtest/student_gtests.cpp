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

TEST(ListOperations, Concatenation) {
    Node* nodeX = list::from_string("x");
    Node* nodeY = list::from_string("x");
    Node* mergedXY = list::append(nodeX, nodeY);
    Node* doubleX = list::append(nodeX, nodeX);

    EXPECT_EQ(list::compare(mergedXY, doubleX), 0);
    list::free(nodeX);
    list::free(nodeY);
    list::free(mergedXY);
    list::free(doubleX);

    Node* nodeAlpha = list::from_string("alpha");
    Node* nodeBeta = list::from_string("bet");
    Node* concatenatedAlphaBeta = list::append(nodeAlpha, nodeBeta);
    Node* fullWord = list::from_string("alphabet");

    EXPECT_EQ(list::compare(concatenatedAlphaBeta, fullWord), 0);
    list::free(nodeAlpha);
    list::free(nodeBeta);
    list::free(concatenatedAlphaBeta);
    list::free(fullWord);
}

TEST(ListTests, Cloning) {
    Node* const original = list::from_string("areyoustupid");
    Node* const cloned = list::copy(original);
    ASSERT_EQ(list::compare(original, cloned), 0);
    list::free(original);
    list::free(cloned);
}

TEST(ListTests, CharFinding) {
    Node* const a = list::from_string("areyoustupid");
    Node* b = list::find_char(a, 'r');
    Node* c = list::find_char(a, 'y');
    Node* d = list::find_char(a, 'o');
    Node* e = list::find_char(a, 'z');
    EXPECT_EQ(b->data, 'r');
    EXPECT_EQ(c->data, 'y');
    EXPECT_EQ(d->data, 'o');
    EXPECT_EQ(e, nullptr);
    list::free(a);
}

TEST(ListTests, Print) {
    stringstream nonEmptyOutput;
    Node* const nonEmptyList = list::from_string("um ok");
    list::print(nonEmptyOutput, nonEmptyList);
    EXPECT_EQ("um ok", nonEmptyOutput.str());
    list::free(nonEmptyList);
    stringstream emptyOutput;
    Node* const emptyList = list::from_string("");
    list::print(emptyOutput, emptyList);
    EXPECT_EQ("", emptyOutput.str());
    list::free(emptyList);
}

TEST(ListTests, CompareStrings) {
    Node* const head1 = list::from_string("apple");
    Node* const head2 = list::from_string("apple");
    EXPECT_EQ(list::compare(head1, head2), 0);
    list::free(head2);

    Node* const head3 = list::from_string("orange");
    Node* const head4 = list::from_string("oranges");
    EXPECT_LT(list::compare(head3, head4), 0);
    EXPECT_GT(list::compare(head4, head3), 0);
    list::free(head3);
    list::free(head4);

    Node* const head5 = list::from_string("");
    EXPECT_LT(list::compare(head5, head1), 0);
    EXPECT_GT(list::compare(head1, head5), 0);
    list::free(head1);
    list::free(head5);
}

TEST(ListTests, NodeComparison) {
    Node* const firstHead = list::from_string("Good morning");
    Node* const secondHead = list::from_string("Good mo");
    EXPECT_EQ(list::compare(firstHead, secondHead, 7), 0);
    EXPECT_GT(list::compare(firstHead, secondHead, 15), 0);
    EXPECT_LT(list::compare(secondHead, firstHead, 8), 0);
    list::free(secondHead);

    Node* const thirdHead = list::from_string("Good morning");
    EXPECT_EQ(list::compare(firstHead, thirdHead, 11), 0);
    EXPECT_EQ(list::compare(thirdHead, firstHead, 50), 0);
    list::free(thirdHead);

    Node* const fourthHead = list::from_string("");
    EXPECT_LT(list::compare(fourthHead, firstHead, 6), 0);
    EXPECT_GT(list::compare(firstHead, fourthHead, 20), 0);
    EXPECT_EQ(list::compare(firstHead, fourthHead, 0), 0);
    list::free(firstHead);
    list::free(fourthHead);
}

