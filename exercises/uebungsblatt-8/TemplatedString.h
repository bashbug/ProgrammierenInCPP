// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef UEBUNGSBLATT_8_TEMPLATEDSTRING_H_
#define UEBUNGSBLATT_8_TEMPLATEDSTRING_H_

#include <gtest/gtest.h>

// Tamplate for string elements.
template<class T>
class TemplatedString {
 public:
  TemplatedString();
  ~TemplatedString();
  // Extands the given TemplatedString by pos
  // and fills the new fields with x
  void resize(size_t size, T x);
  // Sets the given x
  void set(size_t pos, T x);

 private:
  // The elements of TemplatedString.
  T* _contents;
  // The length of TemplatedString = the number of elements.
  size_t _length;

  FRIEND_TEST(TemplatedStringTest, StringChar);
  FRIEND_TEST(TemplatedStringTest, StringInt);
};

// Specialization for TemplatedString<bool>.
// Read commets above for more information.
template<>
class TemplatedString<bool> {
 public:
  TemplatedString();
  ~TemplatedString();

  void resize(size_t bit, bool x);

 private:
  char* _contents;
  size_t _length;
  // How many bytes are needed.
  size_t _numBytes;
  FRIEND_TEST(TemplatedStringTest, StringBool);
};

#endif  // UEBUNGSBLATT_8_TEMPLATEDSTRING_H_
