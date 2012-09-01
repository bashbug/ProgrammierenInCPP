// Copyright 2012, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Anastasia Tondera <tonderaa@informatik.uni-freiburg.de>.

#ifndef PROJEKT_NODE_H_
#define PROJEKT_NODE_H_

#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using std::vector;

class Node {
 public:
  // constructor
  Node();
  // deconstructor
  ~Node();
  // returns the content of a node
  char content();
  // sets the content of a new node
  void setContent(char c);
  //
  bool wordMarker();
  //
  void setWordMarker();
  // search for a given child and returns the node
  Node* findChild(char c);
  // concat a new child
  void appendChild(Node* child);
  // returns vector with the children
  vector<Node*> children();

 private:
  char _content;
  bool _marker;
  vector<Node*> _children;
};

#endif  // PROJEKT_NODE_H_
