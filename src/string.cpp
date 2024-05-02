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
