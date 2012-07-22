// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef  UEBUNGSBLATT_6_STRING_H_
#define  UEBUNGSBLATT_6_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtest/gtest.h>

class String {
 public:
  // Default constructor
  String();
  FRIEND_TEST(StringTest, String);
  // Deconstructor
  ~String();
  // Constructor for an c-String input.
  explicit String(const char* s);
  FRIEND_TEST(StringTest, constructorFromCString);
  // Doubles the input for further operations.
  String(const String& s);
  FRIEND_TEST(StringTest, copyConstructor);
  // Check if two strings are equal.
  String& operator=(const String& s);
  FRIEND_TEST(StringTest, assignmentOperator);

 private:
  // Returns the length of the input string.
  int length() const;
  FRIEND_TEST(StringTest, length);
  // Inserts given string inside of the input string.
  void insert(size_t pos, const char* chars);
  FRIEND_TEST(StringTest, insert);
  // Deletes string at a given position inside of the input string.
  void erase(size_t start, size_t end);
  FRIEND_TEST(StringTest, erase);
  // Finds given string inside of the input string.
  int find(const char* chars, size_t pos);
  FRIEND_TEST(StringTest, find);
  // Finds and Replaces given string inside of the input string.
  void findAndReplace(const char* search, const char* replace);
  FRIEND_TEST(StringTest, findAndReplace);

  // Membervariables
  // The contents of the string, stored with a \0 at the end (C-style).
  char* _contents;
  // The length of the string (without \0).
  size_t _length;
};

#endif  // UEBUNGSBLATT_6_STRING_H_
