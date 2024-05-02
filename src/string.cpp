#include "string.hpp"
#include <iostream>
using namespace std;

String::String(const char* s) : buf(strdup(s)) {}

String::String(const String &s) : buf(strdup(s.buf) {}

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
	int length = String::strlen(buf);
    String rev(length + 1);
    char* dest = rev.buf;
    for (int i = 0; i < length; ++i) {
        dest[i] = buf[length - 1 - i];
    }
    dest[length] = '\0';
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
	int totalLength = strlen(buf) + strlen(s.buf);
    String result(totalLength + 1);
    strcpy(result.buf, buf);
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

static char *strdup(const char *src);
static char *strncpy(char *dest, const char *src, int n);
static char *strcat(char *dest, const char *src);
static char *strncat(char *dest, const char *src, int n);
static int strcmp(const char *left, const char *right);
static int strncmp(const char *left, const char *right, int n);
static void reverse_cpy(char *dest, const char *src);
static const char *strchr(const char *str, char c);
static const char *strstr(const char *haystack, const char *needle);
