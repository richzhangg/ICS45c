#include "string.hpp"

#include <iostream>

using namespace std;

// constructs this string from a C string, defaults to empty string
String::String(const char *s) {
	strncpy(buf, s, MAXLEN-1);
}

// construct this string as a copy iof string s
String::String(const String &s) {
	strcpy(buf, s.buf);
}

// asignment operator from one string, s, to this string
String &String::operator=(const String &s) {
	strcpy(buf, s.buf);
	return *this;
}

// allow indexing this string with notation s[i] 
// COME TO THIS ONE IF NEEDED
char &String::operator[](int index) {
	static char outOfBoundsChar = '\0';
	if (index < 0 || index >= size()) {
		cout << "ERROR: Index Out Of Bounds" << endl;
		return outOfBoundsChar;
	}
	return buf[index];
}

// returns the logical length of this string (# of chars up to '\0')
int String::size() {
	return strlen(buf);
}

// returns a reversal of this string, does not modify this string
String String::reverse() {
	String output;
	reverse_cpy(output.buf, buf);
	return output;
}

// returns index into this string for first occurrence of c
int String::indexOf(char c) {
	char *found = strchr(buf, c);
	if (found == nullptr) {
		return -1;
	}
	return found - buf;
}

// returns index into this string for first occurrence of s
int String::indexOf(const String &s) {
	char *found = strstr(buf, s.buf);
	if (found == nullptr) {
		return -1;
	}
	return found - buf;
}

// relational operators for comparing this strings to another string
bool String::operator==(const String &s) const {
	return (strcmp(buf, s.buf) == 0);
}

bool String::operator!=(const String &s) const{
	return (strcmp(buf, s.buf) != 0);
}

bool String::operator>(const String &s) const {
	return (strcmp(buf, s.buf) > 0);
}

bool String::operator<(const String &s) const {
	return (strcmp(buf, s.buf) < 0);
}

bool String::operator<=(const String &s) const {
	return (strcmp(buf, s.buf) <= 0);
}

bool String::operator>=(const String &s) const {
	return (strcmp(buf, s.buf) >= 0);
}

// concatenate this and s to form a return string
String String::operator+(const String &s) {
    int combined_length = strlen(buf) + strlen(s.buf);
    if (combined_length >= MAXLEN) {
        cout << "ERROR";
        return *this;
    } else {
        String result;
        strcpy(result.buf, this->buf);
        strncat(result.buf, s.buf, MAXLEN - strlen(result.buf) - 1);
        return result;
    }
}

// concatenate s onto the end of this string
String &String::operator+=(const String &s) {
	size_t current_length = strlen(buf);
    size_t additional_length = strlen(s.buf);
    if (current_length + additional_length >= MAXLEN) {
        cout << "ERROR";
        return *this;
    } else {
        strncat(buf, s.buf, MAXLEN - currentLength - 1);
        return *this;
    }
}

// print this string, hint: use operator << to send buf to out
void String::print(std::ostream &out) const {
	for (int i=0; buf[i] != '\0'; ++i){
		out << buf[i];
	}
}

// read next word into this string
// hint: use operator >> to read from in into buf
void String::read(std::istream &in) {
	in >> buf;
}

// destructor for this string
String::~String() {
}

bool String::in_bounds(int i) {
	return i >= 0 && i < strlen(buf);
}

// These static helper methods would ultimately be private.
// but are made public so that you (and the autograder) can test them.
static int strlen(const char *s) {
	int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}

static char *strcpy(char *dest, const char *src) {
	int pos = 0;
    while (src[pos] != '\0') {
        dest[pos] = src[pos];
        pos++;
    }
    dest[pos] = '\0';
	return dest;
}

static char *strncpy(char *dest, const char *src, int n) {
	int index = 0;
    while (index < n && src[index] != '\0') {
        dest[index] = src[index];
        ++index;
    }
    for (; index < n; ++index) {
        dest[index] = '\0';
    }
    return dest;
}

static char *strcat(char *dest, const char *src);
static char *strncat(char *dest, const char *src, int n);
static int strcmp(const char *left, const char *right);
static int strncmp(const char *left, const char *right, int n);
static void reverse_cpy(char *dest, const char *src);
static const char *strchr(const char *str, char c);
static const char *strstr(const char *haystack, const char *needle);

std::ostream &operator<<(std::ostream &out, const String &s);
std::istream &operator>>(std::istream &in, String &s);
