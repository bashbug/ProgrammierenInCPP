// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <string>
#include "./Node.h"
#include "./Trie.h"

using std::string;

Trie::Trie() {
  _root = new Node();
}

Trie::~Trie() {}

void Trie::addWord(string s) {
  Node* current = _root;
  // return if the word is empty
  if (s.length() == 0) {
    current->setWordMarker();
    return;
  }
  // check the trie for the given string s
  for (size_t i = 0; i < s.length(); i++) {
    // get the node of every char of the string s
    // root as search begin
    Node* child = current->findChild(s[i]);
    if (child != NULL) {
      // found a child, continue
      current = child;
    } else {
      // found no child, than create a new node an set content
      Node* tmp = new Node();
      tmp->setContent(s[i]);
      // last node, gets the new node as next node
      current->appendChild(tmp);
      // continue with new node
      current = tmp;
    }
    // at the end of addWord set for the current word the marker true
    if (i == s.length() - 1) {
      current->setWordMarker();
    }
  }
}


bool Trie::searchWord(string s) {
  // root as search begin
  Node* current = _root;
  while (current != NULL) {
    for (size_t i = 0; i < s.length(); i++) {
      Node* tmp = current->findChild(s[i]);
      if (tmp == NULL) {
        // found nothing
        return false;
      } else {
        // found a matching child for each char of the string
        current = tmp;
      }
    }
    // is the wordMarker true, at the end of trie, the trie
    // contains the string
    if (current->wordMarker()) {
      return true;
    } else {
      // string not found
      return false;
    }
  }
  // trie has no content
  return false;
}
