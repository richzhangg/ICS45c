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
	if (!in_bounds(index)) {
        cout << "ERROR: Index Out Of Bounds" << endl;
        static char errorChar = '\0';
        return errorChar;
    }
    return buf[index];}

// returns the logical length of this string (# of chars up to '\0')
int String::size() const {
	return strlen(buf);
}

// returns a reversal of this string, does not modify this string
String String::reverse() const {
	String output;
	reverse_cpy(output.buf, buf);
	return output;
}

// returns index into this string for first occurrence of c
int String::indexOf(char c) const {
	const char *found = strchr(buf, c);
	if (found == nullptr) {
		return -1;
	}
	return found - buf;
}

// returns index into this string for first occurrence of s
int String::indexOf(const String &s) const {
	const char *found = strstr(buf, s.buf);
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
String String::operator+(const String &s) const {
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
	String r("");
    int n = (MAXLEN-1)-String::strlen(buf);
	if (n<=0)
        cout << "ERROR" << endl;
    else {
        String::strcat(r.buf, buf);
        String::strncat(r.buf, s.buf, n);
        String::strcpy(buf, r.buf);
    }
    return *this;
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

// These static helper methods would ultimately be private.
// but are made public so that you (and the autograder) can test them.
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

char *String::strncpy(char *dest, const char *src, int n) {
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

char *String::strcat(char *dest, const char *src) {
	int dest_end = strlen(dest);
    int source_index = 0;
    while (src[source_index] != '\0') {
        dest[dest_end + source_index] = src[source_index];
        source_index++;
    }
    dest[dest_end + source_index] = '\0';
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
	int dest_length = strlen(dest);
    int count = 0;
    while (count < n && src[count] != '\0') {
        dest[dest_length + count] = src[count];
        count++;
    }
    dest[dest_length + count] = '\0';
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
	if (n == 0) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (left[i] != right[i]) {
            if (left[i] == '\0' || right[i] == '\0') {
                return (unsigned char)left[i] - (unsigned char)right[i];
            }
            return (left[i] < right[i]) ? -1 : 1;
        }
        if (left[i] == '\0') {
            return 0;
        }
    }
    return 0;
}


void String::reverse_cpy(char *dest, const char *src) {
	int src_length = strlen(src);
    int reverse_index = 0;
    for (int i = src_length - 1; i >= 0; --i) {
        dest[reverse_index++] = src[i];
    }
    dest[reverse_index] = '\0';
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
	int needle_len = strlen(needle);
    if (needle_len == 0) {
        return haystack;
    }

    for (const char *p = haystack; *p != '\0'; p++) {
		if (*p == needle[0]) {
            if (strncmp(p, needle, needle_len) == 0) {
                return p;
            }
        }
    }
    return nullptr;
}

ostream &operator<<(ostream &out, const String &s) {
	s.print(out);
	return out;
}

istream &operator>>(istream &in, String &s) {
	s.read(in);
	return in;
}
