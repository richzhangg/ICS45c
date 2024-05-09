#include "string.hpp"
#include <iostream>


using namespace std;
using list::Node;


String::String(const char* s) {
    head = list::from_string(s);
}

String::String(const String& s) {
    head = list::copy(s.head);
}

String::String(String&& s) {
    head = s.head;
    s.head = nullptr;
}

String::~String() {
    list::free(head);
}

void String::print(std::ostream& out) const {
    list::print(out, head);
}

void String::swap(String &s) {
    Node* temp = head;
    head = s.head;
    s.head = temp;
}

String& String::operator=(const String& s) {
    if (this==&s) return *this;
    list::free(head);
    head = copy(s.head);
    return *this;
}

String& String::operator=(String&& s) {
    if (this==&s) return *this;
    list::free(head);
    head = s.head;
    s.head = nullptr;
    return *this;
}

bool String::in_bounds(int index) const {
    return (list::nth(head, index));
}

char String::operator[](int index) const {
    Node* c = list::nth(head, index);
    if (c!=nullptr)
        return c->data;
    cout << "ERROR" << endl;
    return '\0';
}

int String::size() const {
    return (list::length(head));
}

void String::read(std::istream& in) {
    char tempbuf[1024];
    in >> tempbuf;

    Node* k = list::from_string(tempbuf);
    Node* l = list::last(head);
    if (l!=nullptr) l->next = k;
    else head = k;
}

std::ostream& operator<<(std::ostream& out, const String& s) {
    s.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    s.read(in);
    return in;
}

int String::indexOf(char c) const {
    Node* f = list::find_char(head, c);
    int k = list::index(head, f);
    return k;
}

int String::indexOf(const String& s) const {
    if (s.head==nullptr) return 0;
    Node* f = list::find_list(head, s.head);
    int k = list::index(head, f);
    return k;
}

bool String::operator==(const String& s) const {
    return (list::compare(head, s.head)==0);
}

std::strong_ordering String::operator<=>(const String& s) const {
    return (list::compare(head, s.head) <=> 0);
}

String String::reverse() const {
    Node* r = list::reverse(head);
    String s("");
    s.head = r;
    return s;
}

String String::operator+(const String& s) const {
    String added("");
    added.head = list::append(head, s.head);
    return added;
}

String& String::operator+=(const String& s) {
    Node* l = list::last(head);
    l->next = list::copy(s.head);
    return *this;
}

