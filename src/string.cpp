#include "string.hpp"
#include <iostream>
#include <cstring>

String::String(const char *s) {
    strncpy(buf, s, MAXLEN - 1);
    buf[MAXLEN - 1] = '\0';
}

String::String(const String &s) {
    strcpy(buf, s.buf);
}

String &String::operator=(const String &s) {
    if (this != &s) {
        strcpy(buf, s.buf);
    }
    return *this;
}

String::~String() {
    std::cout << "String " << buf << " is destructing" << std::endl;
}

int String::strlen(const char *s) {
    int length = 0;
    while (s[length] != '\0') {
        ++length;
    }
    return length;
}

char *String::strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

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

char *String::strncat(char *dest, const char *src, int n) {
    int destLen = strlen(dest);
    int i;
    for (i = 0; src[i] != '\0' && i < n; ++i) {
        dest[destLen + i] = src[i];
    }
    dest[destLen + i] = '\0';
    return dest;
}

char *String::strcat(char *dest, const char *src) {
    int destLen = strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[destLen + i] = src[i];
        i++;
    }
    dest[destLen + i] = '\0';
    return dest;
}

int String::strncmp(const char *left, const char *right, int n) {
    for (int i = 0; i < n; ++i) {
        if (left[i] != right[i] || left[i] == '\0' || right[i] == '\0') {
            return left[i] - right[i];
        }
    }
    return 0;
}

void String::reverse_cpy(char *dest, const char *src) {
    int len = strlen(src);
    for (int i = 0; i < len; ++i) {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = '\0';
}


const char *String::strchr(const char *str, char c) {
    while (*str != '\0') {
        if (*str == c) {
            return str;
        }
        str++;
    }
    return nullptr;
}

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

int String::size() {
    return strlen(buf);
}

void String::print(std::ostream &out) const {
    out << buf;
}

void String::read(std::istream &in) {
    char temp[MAXLEN];
    in >> temp;
    strncpy(buf, temp, MAXLEN - 1);
    buf[MAXLEN - 1] = '\0';
}


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

int String::indexOf(char c) {
    const char *result = strchr(buf, c);
    if (result != nullptr) {
        return result - buf;
    }
    return -1;
}

int String::indexOf(const String &s) {
    const char *found = strstr(buf, s.buf);
    if (found) {
        return found - buf;
    }
    return -1;
}

String String::reverse() {
    char temp[MAXLEN];
    int len = strlen(buf);
    for (int i = 0; i < len; ++i) {
        temp[i] = buf[len - 1 - i];
    }
    temp[len] = '\0';
    return String(temp);
}

String String::operator+(const String &s) {
    String result;
    strncpy(result.buf, this->buf, MAXLEN - 1);
    strncat(result.buf, s.buf, MAXLEN - strlen(result.buf) - 1);
    return result;
}

String &String::operator+=(const String &s) {
    strncat(this->buf, s.buf, MAXLEN - strlen(this->buf) - 1);
    return *this;
}

char &String::operator[](int index) {
    if (!in_bounds(index)) {
        std::cerr << "ERROR: Index Out Of Bounds" << std::endl;
        return buf[0];
    }
    return buf[index];
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
   char temp[MAXLEN];
    in >> temp;
    String tempString(temp);
    s = tempString;
    return in;
}

