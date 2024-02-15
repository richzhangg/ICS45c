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

TEST(StringClass, IncorrectLengthAssertion) {
    String s("test");
    
    // Incorrect assertion: The actual size is 4, but we're asserting it to be 5.
    EXPECT_EQ(s.size(), 5) << "Expected size of 'test' to be 5, but it was actually " << s.size();
}

}TEST(ListTests, Reverse) {
    // Create a list from a string
    Node* head = list::from_string("abc");
    
    // Reverse the list
    Node* reversedHead = list::reverse(head);
    
    // Check the reversed list content
    ASSERT_NE(reversedHead, nullptr);
    EXPECT_EQ(reversedHead->data, 'c');
    Node* second = reversedHead->next;
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->data, 'b');
    Node* third = second->next;
    ASSERT_NE(third, nullptr);
    EXPECT_EQ(third->data, 'a');
    
    // Ensure the list ends here
    EXPECT_EQ(third->next, nullptr);
    
    // Free the reversed list
    list::free(reversedHead);
}

