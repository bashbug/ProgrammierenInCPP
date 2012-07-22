// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <string.h>
#include <string>
#include "./String.h"

// ______________________________________________________________
String::String() {
  _contents = NULL;
  _length = 0;
}

// ______________________________________________________________
String::String(const char* s) {
  size_t n = strlen(s);
  _length = n;
  _contents = new char[n + 1];
  for (size_t i = 0; i <= n; i++) {
    _contents[i] = s[i];
  }
}

// ______________________________________________________________
String::String(const String& s) {
  _length = s.length();
  _contents = new char[_length];
  for (size_t i = 0; i <= _length; i++) {
    _contents[i] = s._contents[i];
  }
}

// ______________________________________________________________
String& String::operator=(const String& s) {
  _length = s.length();
  _contents = new char[_length];
  for (size_t i = 0; i <= _length; i++) {
    _contents[i] = s._contents[i];
  }
  return *this;
}

String::~String() {
  delete[] _contents;
  _contents = NULL;
}

char* String::getString() {
  return _contents;
}

// ______________________________________________________________
int String::length() const {
  return strlen(_contents);
}

// ______________________________________________________________
void String::insert(size_t pos, const char* s) {
  if (pos >= _length) return;
  size_t n = strlen(s);
  char* newContents = new char[_length + n + 1];
  for (size_t i = 0; i < pos; i++) newContents[i] = _contents[i];
  for (size_t i = 0; i < n; i++) newContents[pos + i] = s[i];
  for (size_t i = pos; i <= _length; i++) newContents[n + i] = _contents[i];
  delete[] _contents;
  _contents = newContents;
  _length += n;
}

// ______________________________________________________________
void String::erase(size_t start, size_t end) {
  if (start > _length || end > _length) return;
  if (start > _length || start < 0) return;
  if (end > _length || end <= start) return;

  size_t n = _length - (end - start);
  char* newContents = new char[n];
  size_t k = 0;

  for (size_t i = 0; i < start; i++) {
    newContents[k++] = _contents[i];
  }

  for (size_t i = end; i <= _length; i++) {
    newContents[k++] = _contents[i];
  }

  delete[] _contents;
  _contents = newContents;
  _length = n;
}

// ______________________________________________________________
int String::find(const char* s, size_t pos) {
  if (pos > _length) return -1;
  size_t k = 0;

  for (size_t i = pos; i <= _length; i++) {
    if (_contents[i] == s[k]) {
      k++;
    } else {
      k = 0;
    }
    if (k == strlen(s)) {
      return i-strlen(s)+1;
    }
  }
  return -1;
}

// ______________________________________________________________
void String::findAndReplace(const char* search, const char* replace) {
  int n;
  // not the most effizient solution, because find() begins always by pos 0
  // but easier to implement ;)
  while ((n = find(search, 0)) > -1) {
    erase(n, n+strlen(search));
    insert(n, replace);
  }
}
