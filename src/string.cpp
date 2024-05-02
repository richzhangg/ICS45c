#include "string.hpp"
#include <iostream>
using namespace std;

String::String(const char* s) : buf(strdup(s)) {}

String::String(const String &s) : buf(strdup(s.buf)) {}

String::String(int length) : buf(new char[length]) {
    buf[0] = '\0';
}


String::String(String &&s) {
	buf = s.buf;
	s.buf = nullptr;
}

void String::swap(String &s) {
	char* tempo = buf;
	buf = s.buf;
	s.buf = tempo;
}

String &String::operator=(const String& s) {
	if (this == &s) return *this;
    if (buf) delete[] buf;
    buf = strdup(s.buf);
    return *this;
}

String &String::operator=(String &&s) {
	if (this != &s) {
		delete[] buf;
		buf = s.buf;
		s.buf = nullptr;
	}
	return *this;
}

// come back if needed
char &String::operator[](int index) {
	if (index >= 0 && index < strlen(buf)) {
        return buf[index];
    } else {
        cout << "ERROR" << endl;
        return buf[0];
    }
}

const char &String::operator[](int index) const {
	if (index >= 0 && index < strlen(buf)) {
        return buf[index];
    } else {
        std::cout << "ERROR" << std::endl;
        return buf[0];
    }
}

int String::size() const {
	return strlen(buf);
}

// come back if needed
String String::reverse() const { 
	String rev(strlen(buf)+1);
    reverse_cpy(rev.buf, buf);
    return rev;
}

int String::indexOf(char c) const {
	const char *found = strchr(buf, c);
	if (found == nullptr) {
		return -1;
	}
	return found - buf;
}

int String::indexOf(const String& s) const {
	const char *found = strstr(buf, s.buf);
	if (found == nullptr) {
		return -1;
	}
	return found - buf;
}

bool String::operator==(const String& s) const {
	return (strcmp(buf, s.buf) == 0);
}

bool String::operator!=(const String& s) const {
	return (strcmp(buf, s.buf) != 0);
}

bool String::operator>(const String& s) const {
	return (strcmp(buf, s.buf) > 0);
}

bool String::operator<(const String& s) const {
	return (strcmp(buf, s.buf) < 0);
}

bool String::operator<=(const String& s) const {
	return (strcmp(buf, s.buf) <= 0);
}

bool String::operator>=(const String& s) const {
	return (strcmp(buf, s.buf) >= 0);
}

String String::operator+(const String& s) const {
	int totalLength = strlen(buf) + strlen(s.buf) + 1;
    String result(totalLength);
    result.buf[0] = '\0';
    strcat(result.buf, buf);
    strcat(result.buf, s.buf);
    return result;
}

String &String::operator+=(const String& s) {
	int newLength = strlen(buf) + strlen(s.buf);
    char* newBuf = new char[newLength + 1];
    strcpy(newBuf, buf);
    strcat(newBuf, s.buf);

    delete[] buf;
    buf = newBuf;
    return *this;
}

void String::print(std::ostream &out) const {
	for (int i=0; buf[i] != '\0'; ++i){
		out << buf[i];
	}
}

void String::read(std::istream &in) {
	char temp[1024];
    if (in >> temp) {
        delete[] buf;
        buf = strdup(temp);
    } else {
        cout << "Failed to read input" << endl;
    }
}

String::~String() {
    delete[] buf;
}

int String::strlen(const char *s) {
	int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}

char *String::strcpy(char *dest, const char *src) {
	int pos = 0;
    while (src[pos] != '\0') {
        dest[pos] = src[pos];
        pos++;
    }
    dest[pos] = '\0';
	return dest;
}

char *String::strdup(const char *src) {
	char* newStr = new char[strlen(src) + 1];
    if (newStr) {
        strcpy(newStr, src);
    }
    return newStr;
}

char *String::strncpy(char *dest, const char *src, int n) {
	int srcLength = strlen(src), i = 0;
    for (; i < srcLength && i < n; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char *String::strcat(char *dest, const char *src) {
    int dest_len = strlen(dest);
    int index = 0;
    for (int i = dest_len; src[index] != '\0'; ++i, ++index) {
        dest[i] = src[index];
    }
    dest[dest_len + index] = '\0';
    return dest;
}

// come back
char *String::strncat(char *dest, const char *src, int n) {
	int dest_len = strlen(dest);
    int index = 0;
    for (index = 0; src[index] != '\0' && index < n; ++index) {
        dest[dest_len + index] = src[index];
    }
    dest[dest_len + index] = '\0';
    return dest;
}

int String::strcmp(const char *left, const char *right) {
	for (int i = 0; left[i] != '\0' || right[i] != '\0'; ++i) {
        if (left[i] < right[i]) {
            return -1;
        } else if (left[i] > right[i]) {
            return 1;
        }
    }
    return 0;
}

int String::strncmp(const char *left, const char *right, int n) {
	for (int i = 0; i < n; ++i) {
        if (left[i] == '\0' || right[i] == '\0' || left[i] != right[i]) {
            return left[i] - right[i];
        }
    }
    return 0;
}

void String::reverse_cpy(char *dest, const char *src) {
	int length = strlen(src);
    for (int i = 0; i < length; ++i) {
        dest[i] = src[length - 1 - i];
    }
    dest[length] = '\0';
}

const char *String::strchr(const char *str, char c) {
	for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == c) {
            return &str[i];
        }
    }
    if (c == '\0') {
        return &str[strlen(str)];
    }
    return nullptr;
}

const char *String::strstr(const char *haystack, const char *needle) {
	int needleLen = strlen(needle);
    if (needleLen == 0) {
        return haystack;
    }
    const char* p = haystack;
    while ((p = strchr(p, needle[0])) != nullptr) {
        if (strncmp(p, needle, needleLen) == 0) {
            return p;
        }
        ++p;
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &out, String s) {
	s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
	s.read(in);
    return in;
}
