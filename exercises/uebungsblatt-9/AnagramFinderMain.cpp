// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
#include "./AnagramFinder.h"

using std::vector;
using std::string;

int main(int argc, char** argv) {
  string word;
  AnagramFinder a;
  vector<string> anagrams;
  vector<string>::iterator it;

  a.readDictionary("dictionary.txt");

  printf("Please enter a word. \n"
    "Exit program with '.'\n");
  while (true) {
    std::cin >> word;
    if (word.compare(".") == 0) exit(1);
    a.findAnagrams(word, &anagrams);
    printf("Anagrams:\n");
    if (anagrams.empty() == true) {
      printf("No anagrams are found.\n");
    } else {
      for (it = anagrams.begin(); it < anagrams.end(); it++) {
        std::cout << " " << *it;
        std::cout << std::endl;
      }
    }
  }
}
