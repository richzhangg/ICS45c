#include "string.hpp"
#include <cstring>
#include <iostream>
#include <utility>

char* String::strdup(const char* src) {
    if (!src) {
        return new char[1]{ '\0' };
    }
    size_t length = std::strlen(src) + 1; 
    char* newStr = new char[length];
    std::strcpy(newStr, src);
    return newStr;
}


String::String(const char* s) : buf(strdup(s)) {}


String::String(const String& s) : buf(strdup(s.buf)) {}

String::String(String&& other) noexcept : buf(other.buf) {
    other.buf = nullptr;
}


String::~String() {
    delete[] buf;
}


void String::swap(String& s) {
    std::swap(buf, s.buf);
}

String& String::operator=(const  String& other) {
    String temp(other);
    swap(temp);
    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        delete[] buf;
        buf = other.buf;
        other.buf = nullptr;
    }
    return *this;
}


char& String::operator[](int index) {
    if (index < 0 || index >= this->size()) {
        std::cerr << "ERROR";
    }
    return buf[index];
}



const char& String::operator[](int index) const {
    return buf[index];
}


int String::size() const {
    return std::strlen(buf);
}


String String::reverse() const {
    int len = size();
    char* reversed = new char[len + 1];
    for (int i = 0; i < len; ++i) {
        reversed[i] = buf[len - i - 1];
    }
    reversed[len] = '\0';
    String result(reversed);
    delete[] reversed;
    return result;
}


int String::indexOf(char c) const {
    const char* found = std::strchr(buf, c);
    if (found) {
        return found - buf;
    }
    return -1;
}


int String::indexOf(String s) const {
    const char* found = std::strstr(buf, s.buf);
    if (found) {
        return found - buf;
    }
    return -1;
}


bool String::operator==(String s) const {
    return std::strcmp(buf, s.buf) == 0;
}

bool String::operator!=(String s) const {
    return !(*this == s);
}

bool String::operator<(String s) const {
    return std::strcmp(buf, s.buf) < 0;
}

bool String::operator>(String s) const {
    return s < *this;
}

bool String::operator<=(String s) const {
    return !(*this > s);
}

bool String::operator>=(String s) const {
    return !(*this < s);
}


String String::operator+(const String& s) const {
    char* concatenated = new char[size() + s.size() + 1];
    std::strcpy(concatenated, buf);
    std::strcat(concatenated, s.buf);
    String result(concatenated);
    delete[] concatenated;
    return result;
}


String& String::operator+=(String s) {
    *this = *this + s;
    return *this;
}

void String::print(std::ostream& out) const {
    out << buf;
}


void String::read(std::istream& in) {
    char buffer[1024];
    in >> buffer;
    delete[] buf;
    buf = strdup(buffer);
}


int String::strlen(const char *s) {
    int length = 0;
    while (s && s[length]) {
        ++length;
    }
    return length;
}


char *String::strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}


char* String::strncpy(char* dest, const char* src, int n) {
    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}



char *String::strcat(char *dest, const char *src) {
    int destLen = strlen(dest);
    int i = 0;
    while (src[i]) {
        dest[destLen + i] = src[i];
        i++;
    }
    dest[destLen + i] = '\0';
    return dest;
}


char *String::strncat(char *dest, const char *src, int n) {
    int destLen = strlen(dest);
    int i = 0;
    for (; src[i] && i < n; ++i) {
        dest[destLen + i] = src[i];
    }
    dest[destLen + i] = '\0';
    return dest;
}


int String::strcmp(const char *left, const char *right) {
    for (; *left && *right && *left == *right; ++left, ++right);
    return *(const unsigned char *)left - *(const unsigned char *)right;
}


int String::strncmp(const char *left, const char *right, int n) {
    for (int i = 0; i < n; ++i) {
        if (*left != *right) {
            return *(const unsigned char *)left - *(const unsigned char *)right;
        } else if (!*left || !*right) {
            return *(const unsigned char *)left - *(const unsigned char *)right;
        }
        ++left;
        ++right;
    }
    return 0;
}


void String::reverse_cpy(char *dest, const char *src) {
    int len = strlen(src);
    for (int i = 0; i < len; ++i) {
        dest[i] = src[len - i - 1];
    }
    dest[len] = '\0';
}


const char *String::strchr(const char *str, char c) {
    do {
        if (*str == c) {
            return str;
        }
    } while (*str++);
    return nullptr;
}



const char *String::strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return haystack;
    }
    for (const char *h = haystack; *h != '\0'; h++) {
        for (const char *n = needle, *h2 = h; ; n++, h2++) {
            if (!*n) {
                return h;
            }
            if (!*h2 || *h2 != *n) {
                break;
            }
        }
    }
    return nullptr;
}



std::ostream& operator<<(std::ostream& out, String s) {
    s.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    s.read(in);
    return in;
}

