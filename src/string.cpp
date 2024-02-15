#include "string.hpp"
#include "list.hpp"
#include <string> 
#include <iostream>


String::String(const char *s) {
    head = list::from_string(s);
}

String::String(const String &s) {
    head = list::copy(s.head);
}

String::String(String &&s) : head(s.head) {
    s.head = nullptr;
}

String::~String() {
    list::free(head);
}

void String::swap(String &s) {
    std::swap(head, s.head);
}

String &String::operator=(const String &s) {
    if (this != &s) {
        list::free(head);
        head = list::copy(s.head);
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
    return index >= 0 && index < list::length(head);
}

char String::operator[](int index) const {
    if (index >= 0 && index < this->size()) {
        list::Node* current = head;
        for (int i = 0; i < index; ++i) { 
            current = current->next;
        }
        return current->data; 
    } else {
        std::cerr << "Index out of range.\n"; 
        return '\0'; 
    }
}




int String::size() const {
    return list::length(head);
}

String String::reverse() const {
    list::Node* reversedHead = nullptr;
    list::Node* current = head;
    while (current != nullptr) {
        reversedHead = new list::Node{current->data, reversedHead};
        current = current->next;
    }
    return String(reversedHead);
}

int String::indexOf(char c) const {
    list::Node* node = list::find_char(head, c);
    return list::index(head, node);
}

int String::indexOf(const String &s) const {
    if (this->size() == 0 && s.size() == 0) {
        return 0; 
    }
    
    list::Node* node = list::find_list(head, s.head);
    return list::index(head, node);
}


bool String::operator==(const String &s) const {
    return list::compare(head, s.head) == 0;
}


std::strong_ordering String::operator<=>(const String &s) const {
    return list::compare(head, s.head) <=> 0;
}


String String::operator+(const String &s) const {
    return String(list::append(head, s.head));
}

String& String::operator+=(const String &s) {
    if (this == &s) { 
        String temp(s); 
        *this += temp; 
        return *this;
    }

    list::Node* s_copy = list::copy(s.head); 
    if (!head) {
        head = s_copy; 
    } else {
        list::Node* last_node = list::last(head);
        last_node->next = s_copy; 
    }
    return *this;
}


void String::print(std::ostream &out) const {
    list::print(out, head);
}


void String::read(std::istream &in) {
    std::string buffer;
    in >> buffer; 
    list::free(head); 
    head = list::from_string(buffer.c_str()); 
}


std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}


std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}


String::String(list::Node* node_head) : head(node_head) {

}

