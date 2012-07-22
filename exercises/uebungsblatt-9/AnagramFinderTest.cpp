// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "./AnagramFinder.h"

// ____________________________________________________________________________
TEST(AnagramFinderTest, readDictionary) {
  // make tmp dictionary file for test
  const char* inputFileName = "Input.TMP.txt";
  FILE* inputFile = fopen(inputFileName, "w");
  fprintf(inputFile, "abc\nampel\nlampe\npalme\nxyz\n");
  fclose(inputFile);

  vector<string> anagrams;
  AnagramFinder a;

  a.readDictionary("Input.TMP.txt");

  ASSERT_STREQ("abc", a._dictionary.at(0).c_str());
  ASSERT_STREQ("ampel", a._dictionary.at(1).c_str());
  ASSERT_STREQ("lampe", a._dictionary.at(2).c_str());
  ASSERT_STREQ("palme", a._dictionary.at(3).c_str());
  ASSERT_STREQ("xyz", a._dictionary.at(4).c_str());
}

// ____________________________________________________________________________
TEST(AnagramFinderTest, isAnagram) {
  AnagramFinder a;

  ASSERT_FALSE(a.isAnagram("Test", "Hase"));
  ASSERT_TRUE(a.isAnagram("Ampel", "Palme"));

  // false for the trivial case, which should not be listed.
  ASSERT_FALSE(a.isAnagram("Lampe", "Lampe"));
}

// ____________________________________________________________________________
TEST(AnagramFinderTest, findAnagrams) {
  const char* inputFileName = "Input.TMP.txt";
  FILE* inputFile = fopen(inputFileName, "w");
  fprintf(inputFile, "abc\nampel\nlampe\npalme\nxyz\n");
  fclose(inputFile);

  vector<string> anagrams;
  AnagramFinder a;

  a.readDictionary("Input.TMP.txt");
  a.findAnagrams("lampe", &anagrams);

  ASSERT_EQ(2, anagrams.size());
  ASSERT_STREQ("ampel", anagrams.at(0).c_str());
  ASSERT_STREQ("palme", anagrams.at(1).c_str());

  // check if anagram vector is empty
  a.findAnagrams("Test", &anagrams);
  ASSERT_EQ(0, anagrams.size());

  remove(inputFileName);
}

