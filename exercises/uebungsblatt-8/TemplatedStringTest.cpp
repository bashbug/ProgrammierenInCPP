// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./TemplatedString.h"

// _____________________________________________________________________________
TEST(TemplatedStringTest, StringChar) {
  TemplatedString<char> s;
  ASSERT_EQ(0, s._length);

  s.resize(4, 'o');
  ASSERT_EQ(4, s._length);
  ASSERT_EQ('o', s._contents[0]);
  ASSERT_EQ('o', s._contents[1]);
  ASSERT_EQ('o', s._contents[2]);
  ASSERT_EQ('o', s._contents[3]);

  s.set(0, 'd');
  s.set(3, 'f');
  ASSERT_EQ(4, s._length);
  ASSERT_EQ('d', s._contents[0]);
  ASSERT_EQ('o', s._contents[1]);
  ASSERT_EQ('o', s._contents[2]);
  ASSERT_EQ('f', s._contents[3]);

  s.resize(7, '!');
  ASSERT_EQ(7, s._length);
  ASSERT_EQ('d', s._contents[0]);
  ASSERT_EQ('o', s._contents[1]);
  ASSERT_EQ('o', s._contents[2]);
  ASSERT_EQ('f', s._contents[3]);
  ASSERT_EQ('!', s._contents[4]);
  ASSERT_EQ('!', s._contents[5]);
  ASSERT_EQ('!', s._contents[6]);

  s.resize(5, 'x');
  ASSERT_EQ(5, s._length);
  ASSERT_EQ('d', s._contents[0]);
  ASSERT_EQ('o', s._contents[1]);
  ASSERT_EQ('o', s._contents[2]);
  ASSERT_EQ('f', s._contents[3]);
  ASSERT_EQ('!', s._contents[4]);

  s.resize(0, 'x');
  ASSERT_EQ(0, s._length);
}

// _____________________________________________________________________________
TEST(TemplatedStringTest, StringInt) {
  TemplatedString<int> s;
  ASSERT_EQ(0, s._length);

  s.resize(4, 0);
  ASSERT_EQ(4, s._length);
  ASSERT_EQ(0, s._contents[0]);
  ASSERT_EQ(0, s._contents[1]);
  ASSERT_EQ(0, s._contents[2]);
  ASSERT_EQ(0, s._contents[3]);

  s.set(0, 1);
  s.set(3, 4);
  s.set(1, 2);
  s.set(2, 3);
  ASSERT_EQ(4, s._length);
  ASSERT_EQ(1, s._contents[0]);
  ASSERT_EQ(2, s._contents[1]);
  ASSERT_EQ(3, s._contents[2]);
  ASSERT_EQ(4, s._contents[3]);

  s.resize(7, 5);
  ASSERT_EQ(7, s._length);
  ASSERT_EQ(1, s._contents[0]);
  ASSERT_EQ(2, s._contents[1]);
  ASSERT_EQ(3, s._contents[2]);
  ASSERT_EQ(4, s._contents[3]);
  ASSERT_EQ(5, s._contents[4]);
  ASSERT_EQ(5, s._contents[5]);
  ASSERT_EQ(5, s._contents[6]);

  s.set(5, 6);
  s.set(6, 7);
  ASSERT_EQ(7, s._length);
  ASSERT_EQ(1, s._contents[0]);
  ASSERT_EQ(2, s._contents[1]);
  ASSERT_EQ(3, s._contents[2]);
  ASSERT_EQ(4, s._contents[3]);
  ASSERT_EQ(5, s._contents[4]);
  ASSERT_EQ(6, s._contents[5]);
  ASSERT_EQ(7, s._contents[6]);

  s.resize(3, -1);
  ASSERT_EQ(3, s._length);
  ASSERT_EQ(1, s._contents[0]);
  ASSERT_EQ(2, s._contents[1]);
  ASSERT_EQ(3, s._contents[2]);

  s.resize(0, -1);
  ASSERT_EQ(0, s._length);
}

// _____________________________________________________________________________
TEST(TemplatedStringTest, StringBool) {
  TemplatedString<bool> s;
  ASSERT_EQ(0, s._length);
  ASSERT_EQ(0, s._numBytes);

  s.resize(8, false);
  ASSERT_EQ(8, s._length);
  ASSERT_EQ(1, s._numBytes);
  ASSERT_EQ(0, s._contents[0]);

  s.resize(9, true);
  ASSERT_EQ(9, s._length);
  ASSERT_EQ(2, s._numBytes);
  ASSERT_EQ(0, s._contents[0]);
  ASSERT_EQ(1, s._contents[1]);

  s.resize(12, true);
  ASSERT_EQ(2, s._numBytes);
  s.resize(16, false);
  ASSERT_EQ(16, s._length);
  ASSERT_EQ(2, s._numBytes);
  ASSERT_EQ(0, s._contents[0]);
  ASSERT_EQ(15, s._contents[1]);

  s.resize(8, true);
  ASSERT_EQ(8, s._length);
  ASSERT_EQ(1, s._numBytes);
  ASSERT_EQ(0, s._contents[0]);

  // s.resize(18, true);
  // ASSERT_EQ(18, s._length);
  // ASSERT_EQ(3, s._numBytes);
  // ASSERT_EQ(0, s._contents[0]);
  // ASSERT_EQ(-1, s._contents[1]);
  // ASSERT_EQ(3, s._contents[2]);

  s.resize(0, true);
  ASSERT_EQ(0, s._length);
  ASSERT_EQ(0, s._numBytes);
}
