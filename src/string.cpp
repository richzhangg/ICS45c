#include "string.hpp"
#include "list.hpp"
#include <string> // Include for std::string
#include <iostream>

// constructs this string from a C string, defaults to empty string
String::String(const char *s) {
    head = list::from_string(s);
}

// construct this string as a copy of string s
String::String(const String &s) {
    head = list::copy(s.head);
}

// construct this string by moving from string s
String::String(String &&s) : head(s.head) {
    s.head = nullptr;
}

// destructor for this string
String::~String() {
    list::free(head);
}

// swap this string with s
void String::swap(String &s) {
    std::swap(head, s.head);
}

// assignment operator from one string, s, to this string
String &String::operator=(const String &s) {
    if (this != &s) {
        list::free(head);
        head = list::copy(s.head);
    }
    return *this;
}

// assign to this string by moving
String &String::operator=(String &&s) {
    if (this != &s) {
        list::free(head);
        head = s.head;
        s.head = nullptr;
    }
    return *this;
}

// check if we can index at position i in this string
bool String::in_bounds(int index) const {
    return index >= 0 && index < list::length(head);
}

// allow const indexing
char String::operator[](int index) const {
   list::Node* node = list::nth(head, index);
    return node ? node->data : '\0';
}

// returns the logical length of this string (# of chars up to '\0')
int String::size() const {
    return list::length(head);
}

// returns a reversal of this string, does not modify this string
String String::reverse() const {
    list::Node* reversedHead = nullptr;
    list::Node* current = head;
    while (current != nullptr) {
        reversedHead = new list::Node{current->data, reversedHead};  // Prepend to create reversed copy
        current = current->next;
    }
    // Use the private constructor to create a String with the reversed list
    return String(reversedHead);
}

// returns index into this string for first occurrence of c
int String::indexOf(char c) const {
    list::Node* node = list::find_char(head, c);
    return list::index(head, node);
}

int String::indexOf(const String &s) const {
    // Special case: searching for an empty string in an empty string
    if (this->size() == 0 && s.size() == 0) {
        return 0; // Indicate that the empty string is found at the start
    }
    
    // Existing logic for indexOf
    list::Node* node = list::find_list(head, s.head);
    return list::index(head, node);
}

// compare this string with another string by equality
bool String::operator==(const String &s) const {
    return list::compare(head, s.head) == 0;
}

// C++20 way of defining all comparisons at once
std::strong_ordering String::operator<=>(const String &s) const {
    return list::compare(head, s.head) <=> 0;
}

// concatenate this and s to form a return string
String String::operator+(const String &s) const {
    return String(list::append(head, s.head));
}

String& String::operator+=(const String &s) {
    if (this == &s) { // Check for self-assignment
        String temp(s); // Make a copy
        *this += temp; // Concatenate the copy
        return *this;
    }

    list::Node* s_copy = list::copy(s.head); // Make a copy of the right-hand side
    if (!head) {
        head = s_copy; // If this string is empty, just use the copy
    } else {
        list::Node* last_node = list::last(head);
        last_node->next = s_copy; // Append the copy
    }
    return *this;
}

// print this string, hint: use operator << to send buf to out
void String::print(std::ostream &out) const {
    list::print(out, head);
}

// read next word into this string
void String::read(std::istream &in) {
    std::string buffer;
    in >> buffer; // Read the next word
    list::free(head); // Free the existing list
    head = list::from_string(buffer.c_str()); // Create a new list from the buffer
}

// Overloaded output operator for String
std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}

// Overloaded input operator for String
std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}

// private constructor that takes ownership of the given list
String::String(list::Node* node_head) : head(node_head) {
    // This constructor is intentionally left empty. Its purpose is to allow
    // internal methods to create a String object that takes ownership of a
    // Node* without copying it, which is used in methods like reverse and operator+.
}

