// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./String.h"

// _____________________________________________________________________________
TEST(StringTest, String) {
  String s;
  ASSERT_TRUE(s._contents == NULL);
  ASSERT_EQ(0, s._length);
}

// _____________________________________________________________________________
TEST(StringTest, constructorFromCString) {
  String s("doof");
  ASSERT_STREQ("doof", s._contents);
  ASSERT_EQ(4, s._length);
}

// _____________________________________________________________________________
TEST(StringTest, copyConstructor) {
  String s1("doof");
  String s2 = s1;  // Note: this calls the copy constructor, not the = operator!
  ASSERT_STREQ("doof", s1._contents);
  ASSERT_STREQ("doof", s2._contents);
  ASSERT_EQ(4, s1._length);
  ASSERT_EQ(4, s2._length);
  // Test that indeed a deep copy was made, that is, the (identical) contents is
  // stored at two *different* locations in memory.
  ASSERT_NE(s1._contents, s2._contents);
}

// _____________________________________________________________________________
TEST(StringTest, assignmentOperator) {
  String s1("doof");
  String s2;
  s2 = s1;  // Note: this indeed calls the assignment operator.
  ASSERT_STREQ("doof", s1._contents);
  ASSERT_STREQ("doof", s2._contents);
  ASSERT_EQ(4, s1._length);
  ASSERT_EQ(4, s2._length);
  ASSERT_NE(s1._contents, s2._contents);
}

// _____________________________________________________________________________
TEST(StringTest, length) {
  String s("doof");
  ASSERT_EQ(4, s.length());
}

// _____________________________________________________________________________
TEST(StringTest, insert) {
  String s("doof");
  s.insert(0, "sau");
  ASSERT_STREQ("saudoof", s._contents);
  ASSERT_EQ(7, s._length);
}

// _____________________________________________________________________________
TEST(StringTest, erase) {
  String s("saudoof");
  s.erase(0, 3);
  ASSERT_STREQ("doof", s._contents);
  ASSERT_EQ(4, s._length);
  String s1("saudoof");
  s1.erase(3, 6);
  ASSERT_STREQ("sauf", s1._contents);
  ASSERT_EQ(4, s1._length);
  String s2("saudoof");
  s2.erase(0, 8);
  ASSERT_STREQ("saudoof", s2._contents);
  String s3("saudoof");
  s3.erase(-1, 8);
  ASSERT_STREQ("saudoof", s3._contents);
  String s4("saudoof");
  s4.erase(-1, -1);
  ASSERT_STREQ("saudoof", s4._contents);
}

// _____________________________________________________________________________
TEST(StringTest, find) {
  String s("doof, doofer, am doofsten");
  // Note: the first argument of find is the substring to search for. The second
  // argument is the position starting from which to search (where the first
  // position of the string is 0).
  ASSERT_EQ(0, s.find("doof", 0));
  ASSERT_EQ(6, s.find("doof", 1));
  ASSERT_EQ(6, s.find("doof", 6));
  ASSERT_EQ(17, s.find("doof", 7));
  ASSERT_EQ(17, s.find("doof", 17));
  ASSERT_EQ(-1, s.find("doof", 18));
  ASSERT_EQ(-1, s.find("XXX", 25));
  ASSERT_EQ(-1, s.find("XXX", -1));
}

// _____________________________________________________________________________
TEST(StringTest, findAndReplace) {
  String s("doof, doofer, am doofsten");
  s.findAndReplace("doof", "bloed");
  ASSERT_STREQ("bloed, bloeder, am bloedsten", s._contents);
  ASSERT_EQ(28, s._length);
  String s1("doof, doofer, am doofsten");
  s1.findAndReplace("doof, doofer, am doofsten", "");
  ASSERT_STREQ("", s1._contents);
  ASSERT_EQ(28, s._length);
}
