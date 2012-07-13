// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include "./AnagramFinder.h"

using std::vector;
using std::string;
using std::ostringstream;

// ____________________________________________________________________________
void AnagramFinder::readDictionary(const char* dictionaryFileName) {
  // read from txt and insert the lines in a vector.
  FILE* inputfile = fopen(dictionaryFileName, "r");
  const size_t MAX_LINE_LENGTH = 1000;
  char line[MAX_LINE_LENGTH + 1];
  string word;
  while (true) {
    fgets(line, MAX_LINE_LENGTH, inputfile);
    if (feof(inputfile)) break;
    word = line;
    // remove \n at the end of every line.
    word.erase(std::remove(word.begin(), word.end(), '\n'), word.end());
    _dictionary.push_back(word);
  }
}

// ____________________________________________________________________________
void AnagramFinder::findAnagrams(string word, vector<string>* anagrams) {
  // make sure, that anagrams vector is empty
  anagrams->clear();

  // iterate dictionary for anagram check.
  string dictionaryWord;
  for (int i = 0; i < _dictionary.size(); i++) {
    dictionaryWord = _dictionary.at(i);

    // check which dictionary words are anagrams of the input string
    if (isAnagram(word, dictionaryWord) == true) {
      anagrams->push_back(dictionaryWord);
    }
  }
}

// ____________________________________________________________________________
bool AnagramFinder::isAnagram(string word1, string word2) {
  string sortedWord1 = word1;
  string sortedWord2 = word2;

  // lowercase, because the search isn't case sensitive.
  for (int i = 0; i < word1.length(); i++) {
    sortedWord1[i] = std::tolower(word1[i]);
  }

  // sort input string with string algorithm sort.
  sort(sortedWord1.begin(), sortedWord1.end());

  // same procedure for word2
  for (int i = 0; i < word2.length(); i++) {
    sortedWord2[i] = std::tolower(word2[i]);
  }

  sort(sortedWord2.begin(), sortedWord2.end());

  // check if dictionary word is an anagram and
  // return false if it is the word itself.
  if (sortedWord1 != sortedWord2 || word1 == word2) {
    return false;
  } else {
    return true;
  }
}
