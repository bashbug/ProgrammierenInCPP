// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#include <vector>
#include "./Node.h"

using std::vector;

// ____________________________________________________________________________
Node::Node() {
  _content = ' ';
  _marker = false;
}

// ____________________________________________________________________________
Node::~Node() {}

// ____________________________________________________________________________
char Node::content() {
  return _content;
}

// ____________________________________________________________________________
void Node::setContent(char c) {
  _content = c;
}

// ____________________________________________________________________________
bool Node::wordMarker() {
  // returns true if the end of a word is reached
  return _marker;
}

// ____________________________________________________________________________
void Node::setWordMarker() {
  // set the end of a word
  _marker = true;
}

// ____________________________________________________________________________
Node* Node::findChild(char c) {
  // compare the c input with each children in the _mChildren vector
  for (size_t i = 0; i < _children.size(); i++) {
    Node* tmp = _children.at(i);
    if ( tmp->content() == c ) {
      // found c as a content, than return the node of c
      return tmp;
    }
  }
  // c is not found as a child, than return NULL
  return NULL;
}

// ____________________________________________________________________________
void Node::appendChild(Node* child) {
  _children.push_back(child);
}

// ____________________________________________________________________________
vector<Node*> Node::children() {
  return _children;
}
