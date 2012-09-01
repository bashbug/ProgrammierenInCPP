// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef PROJEKT_TRIE_H_
#define PROJEKT_TRIE_H_

#include <string>
#include "./Node.h"
using std::string;

class Trie {
 public:
  // constructor
  Trie();
  // deconstructor
  ~Trie();
  // adds a new word in the trie
  void addWord(string s);
  // search for a given word in the tree
  bool searchWord(string s);
  // delete a given word in the tree
  void deleteWord(string s);
 private:
  Node* _root;
};

#endif  // PROJEKT_TRIE_H_
