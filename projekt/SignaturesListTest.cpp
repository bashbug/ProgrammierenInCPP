// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <string>
#include "./SignaturesList.h"

using std::string;

TEST(SignaturesListTest, hexToDec) {
  SignaturesList s = SignaturesList();
  ASSERT_EQ(255, s.hexToDec("ff"));
  ASSERT_EQ(255, s.hexToDec("FF"));
}

TEST(SignaturesListTest, add) {
  SignaturesList s;
  string signature = "74657374";
  string name = "test-add";
  s.add(signature, name);
  ASSERT_TRUE(true);
}

TEST(SignaturesListTest, check) {
  SignaturesList s;
  string testSignature0 = "736368";
  string name0 = "test-0";
  string testSignature1  = "735368";
  string name1 = "test-1";
  string testSignature2  = "734368";
  string name2 = "test-2";
  string testSignature3 = "7363686e757575666669";
  string name3 = "test-3";
  s.add(testSignature0, name0);
  s.add(testSignature1, name1);
  s.add(testSignature2, name2);
  s.add(testSignature3, name3);
  ASSERT_TRUE(s.exists(testSignature0));
  ASSERT_TRUE(s.exists(testSignature3));
}

TEST(SignaturesListTest, SignaturesList) {
  SignaturesList s;
  bool nul = true;
  for (int i = 0; i < s.size(); i++) {
    if (s._root[i] != NULL) {
      nul = false;
      break;
    }
  }
  ASSERT_TRUE(nul);
}
