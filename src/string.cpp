#include "string.hpp"
#include "list.hpp"
#include <iostream>
using namespace std;
using list::Node;

String::String(const char *s) {
	head = list::from_string(s);
}

String::String(const String &s) {
	head = list::copy(s.head);
}

String::String(String &&s) {
	head = s.head;
	s.head = nullptr;
}

void String::swap(String &s) {
	Node* t = head;
	head = s.head;
	s.head = t;
	t = nullptr;
}

// come back if needed
String &String::operator=(const String &s) {
	if (this != &s) {
        list::free(head);
        head = nullptr;
        if (s.head) {
            head = list::copy(s.head);
        }
    }
    return *this;
}

String &String::operator=(String &&s) {
	if (this != &s) {
        list::free(head);
        head = s.head;
        s.head = nullptr;
    }
    return *this;
}

bool String::in_bounds(int index) const {
	return index >= 0 && index < size();
}

char String::operator[](int index) const {
	Node* current = list::nth(head, index);
    if (current) {
        return current->data;
    } else {
        cout << "ERROR" << endl;
        return '\0';
    }
}

int String::size() const {
	return list::length(head);
}

// come back if error
String String::reverse() const {
	Node* reversedHead = list::reverse(head);
    return String(reversedHead);
}

// come back if error
int String::indexOf(char c) const {
	if (!head && !c) {
        return 0;
    }
    Node* p = list::find_char(head, c);
    if (p == nullptr) {
        return -1;
    } else {
        return list::index(head, p);
    }
}

// come back if error
int String::indexOf(const String &s) const {
	if (!head && !substring.head) return 0;
    Node* foundNode = list::find_list(head, substring.head);
    int index = foundNode ? list::index(head, foundNode) : -1;
    return index;
}

bool String::operator==(const String &s) const {
	return list::compare(head, s.head) == 0;
}

std::strong_ordering String::operator<=>(const String &s) const {
	return list::compare(head, s.head) <=> 0;
}

String String::operator+(const String &s) const {
	return String{list::append(head, s.head)};
}

// come back if error
String &String::operator+=(const String &s) {
	if (s.head != nullptr) {
        Node* end = list::last(head);
        if (end == nullptr) {
            head = list::copy(s.head);
        } else {
            end->next = list::copy(s.head);
        }
    }
    return *this;
}

void String::print(std::ostream &out) const {
	list::print(out, head);
}

//come back if error
void String::read(std::istream &in) {
	if (head != nullptr) {
        list::free(head);
        head = nullptr;
    }
    char buffer[1024];
    in >> buffer;
    head = list::from_string(buffer);
}

String::~String() {
	list::free(head);
}

std::ostream &String::operator<<(std::ostream &out, const String &s) {
	s.print(out);
	return out;
}

std::istream &String::operator>>(std::istream &in, String &s) {
	s.read(in);
	return in;
}
