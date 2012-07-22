// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@informatik.uni-freiburg.de>,
// Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef UEBUNGSBLATT_9_ANAGRAMFINDER_H_
#define UEBUNGSBLATT_9_ANAGRAMFINDER_H_

#include <gtest/gtest.h>
#include <string>
#include <vector>

using std::vector;
using std::string;

// Class for reading a list of words from a file and then finding anagrams in
// it.
class AnagramFinder {
 public:
  // Read words from dictionary.
  void readDictionary(const char* dictionaryFileName);
  FRIEND_TEST(AnagramFinderTest, readDictionary);
  // Find all anagrams for the given word in the dictionary read with
  // readDictionary.  The result is returned via the second argument, see
  // Vorlesung 6.
  void findAnagrams(string word, vector<string>* anagrams);
  FRIEND_TEST(AnagramFinderTest, findAnagrams);

 private:
  // Check if two words are anagrams of each other. The easiest way to do this
  // is to sort the letters in the words and then compare for equality. Case
  // should be ignored. For example, "Schaufelrad" and "Dauerschlaf" are both
  // "aacdefhlrsu" after sorting their (lower-cased) letters.
  bool isAnagram(string word1, string word2);
  FRIEND_TEST(AnagramFinderTest, isAnagram);

  // The words from the dictionary.
  vector<string> _dictionary;
};

#endif  // UEBUNGSBLATT_9_ANAGRAMFINDER_H_
