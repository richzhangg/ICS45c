#include "string.hpp"
#include <iostream>
#include <cstring>

// Constructor: Constructs string from a C string
String::String(const char *s) {
    strncpy(buf, s, MAXLEN - 1);
    buf[MAXLEN - 1] = '\0'; // Ensure null termination
}

// Copy Constructor
String::String(const String &s) {
    strcpy(buf, s.buf);
}

// Assignment Operator
String &String::operator=(const String &s) {
    if (this != &s) {
        strcpy(buf, s.buf);
    }
    return *this;
}

// Destructor
String::~String() {
    std::cout << "String " << buf << " is destructing" << std::endl;
}

// Static Helper Methods

// strlen: Calculate length of string
int String::strlen(const char *s) {
    int length = 0;
    while (s[length] != '\0') {
        ++length;
    }
    return length;
}

// strcpy: Copy string
char *String::strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

// strncpy: Copy characters of one string to another
char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;
    for (; src[i] != '\0' && i < n; i++) {
        dest[i] = src[i];
    }
    if (i < n) {
        dest[i] = '\0';
    }
    return dest;
}

// strcmp: Compare two strings
int String::strcmp(const char *left, const char *right) {
    int i = 0;
    while (left[i] == right[i]) {
        if (left[i] == '\0') {
            return 0;
        }
        i++;
    }
    return left[i] - right[i];
}

// strchr: Locate character in string
const char *String::strchr(const char *str, char c) {
    while (*str != '\0') {
        if (*str == c) {
            return str;
        }
        str++;
    }
    return nullptr;
}

// strstr: Locate substring in string
const char *String::strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return haystack;
    }

    for (; *haystack; ++haystack) {
        if (*haystack == *needle) {
            const char *h = haystack, *n = needle;
            while (*h && *n && *h == *n) {
                ++h;
                ++n;
            }
            if (!*n) {
                return haystack;
            }
        }
    }
    return nullptr;
}

// size: Returns the logical length of this string
int String::size() {
    return strlen(buf);
}

// Relational Operators

bool String::operator==(const String &s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
    return !(*this == s);
}

bool String::operator<(const String &s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator>(const String &s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<=(const String &s) const {
    return !(*this > s);
}

bool String::operator>=(const String &s) const {
    return !(*this < s);
}

// IndexOf Method for char
int String::indexOf(char c) {
    const char *result = strchr(buf, c);
    if (result != nullptr) {
        return result - buf; // Pointer arithmetic to find index
    }
    return -1; // Character not found
}

// IndexOf Method for String
int String::indexOf(const String &s) {
    const char *found = strstr(buf, s.buf);
    if (found) {
        return found - buf;  // Pointer arithmetic
    }
    return -1;  // Not found
}

// Reverse Method
String String::reverse() {
    char temp[MAXLEN];
    int len = strlen(buf);
    for (int i = 0; i < len; ++i) {
        temp[i] = buf[len - 1 - i];
    }
    temp[len] = '\0';
    return String(temp);
}

// Concatenation: operator+
String String::operator+(const String &s) {
    String result;
    strncpy(result.buf, this->buf, MAXLEN - 1);
    strncat(result.buf, s.buf, MAXLEN - strlen(result.buf) - 1);
    return result;
}

// Concatenation: operator+=
String &String::operator+=(const String &s) {
    strncat(this->buf, s.buf, MAXLEN - strlen(this->buf) - 1);
    return *this;
}

// Indexing: operator[]
char &String::operator[](int index) {
    if (!in_bounds(index)) {
        std::cerr << "ERROR: Index Out Of Bounds" << std::endl;
        return buf[0]; // Return first character as a fallback
    }
    return buf[index];
}

// Stream Insertion Operator
std::ostream &operator<<(std::ostream &out, const String &s) {
    out << s.buf;
    return out;
}

// Stream Extraction Operator
std::istream &operator>>(std::istream &in, String &s) {
    char temp[String::MAXLEN];
    in >> temp;
    String::strncpy(s.buf, temp, String::MAXLEN - 1);
    s.buf[String::MAXLEN - 1] = '\0';
    return in;
}

